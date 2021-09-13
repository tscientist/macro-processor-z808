// Construção das funções declaradas em processador_macros.hpp

#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <stdio.h>
#include "macroProcessor.hpp"

using namespace std;

MacroProcessor::MacroProcessor() { }

bool MacroProcessor::readFile(ifstream *file){ 
    char each_character;
    string retorno;
    if (file) { 
        while (file->get(each_character)) {

            if (each_character == '\n' || each_character == ' ' || each_character == ',') { 
                if (retorno != "") {
                    if (each_character == ','){
                        push(retorno);
                        push(",");
                    } else {
                        push(retorno);
                    }
                }         
                retorno = ""; 
            } else {
                retorno += each_character; 
            }
        }
        return true;
    } else {
        return false;
    }
}

void MacroProcessor::push(string value) { 
    input.push_back(value);
}

void MacroProcessor::createOutputFile(string fileName){
    int j = 0;

    outFile.open("  " + fileName);
    /*for (int i = 0; i < output.size(); i++){
        if (output[i] == ","){
            output[i-1].erase();
            while(output[i] != "Inicio"){
                output[i++].erase();
            }
        }
    }*/

    for (int i = 0; i < output.size(); i++) {
        if (output[i] != " " && output[i] != "" ) {
            outFile << output[i] << " ";
        }
    }
}

void MacroProcessor::passOne() {
    int t = 0;
    for (int i = 0; i < input.size(); i++) {
        if (input[i] == "MACRO"){
            t = i + 1;
            variableNames.push_back(input[i - 1]);

            while (input[t] != ";;") { 
                if (input[t] != ",") {
                    variableNames.push_back(input[t]);
                }
                t++;
            }
            /*int k = 0;
            while (variableNames[k].size() != 0) {
                cout << "variableNames " + variableNames[k] << endl;
                k++;
            }*/
            macro.push_back(input[i - 1]);
            input[i - 1].erase();
            int flag = 0;
            for (int j = i; input[j] != "ENDM"; j++) {
                if (input[j] != "MACRO") {
                    macro.push_back(input[j]);
                    input[j].erase();
                    t = j;
                } else {
                    flag = j;
                }
            }

            input[t + 1].erase();
            input[flag].erase();
        }   
    }
    for (int i = 0; i < input.size(); i++) {
        if (input[i] != " ") {
            if (input[i] != "MACRO") {
                output.push_back(input[i]);
            }
        }
    }
    //ESTA SALVANDO O MACRO
    /*int k = 0;
    while (k < output.size()) {
        cout << "output " + output[k] << endl;
        k++;
    }
    k = 0;
    while (k < input.size()) {
        cout << "input " + input[k] << endl;
        k++;
    }
    k = 0;
    while (k < macro.size()) {
        cout << "macro " + macro[k] << endl;
        k++;
    }
    k = 0;
    while (k < variableNames.size()) {
        cout << "variableNames " + variableNames[k] << endl;
        k++;
    }*/
}

void MacroProcessor::passTwo() {
    for (int i = 0; i < output.size(); i++) {
        for (int j = 0; j < variableNames.size(); j++) {
            //J é a posição do nome da variavel 
            //I é a posição onde é chamado a macro
            if (output[i] == variableNames[j]) {
                //printf("variaveis %s   ", variableNames[j].c_str());
                //printf("output %s\n", output[i].c_str());
                //printf("num i %d   ", i+1);
                //printf("num j %d\n", j+1);
                
                troca(i + 1, j + 1);
            }
        }
    } 
}

void MacroProcessor::troca(int i, int j){
    for (int k = j; k < variableNames.size(); k++){
        for (int t = 0; t < macro.size(); t++) {
            if (macro[t] == variableNames[k] && macro[t] != "") {
                macro[t] = output[i];        
            }    
        }
        if (i < output.size()-1) {
            if (output[i + 1] == ",") {
                i += 2;
            } else {
                i++;
            }
        }
    }
}

void MacroProcessor::fileEnding() {
    int position = 0, k = 0;
    vector<string> output_copy;
    int var_inicio = 0, var_final = 0;
    int var_size = 0;
    while (k < output.size()) {
        output_copy.push_back(output[k]);
        //cout << "output_copy " + output_copy[k] << endl;

        k++;
    }

    for (int i = 0; i < output.size(); i++){
        for (int j = 0; j < variableNames.size(); j++) {
            if (output[i] == variableNames[j]){
                //printf("output i %s   ", output[i].c_str());
                //printf("output 2 %s   ", output[i + 1].c_str());

                printf("variableNames %s \n", variableNames[j].c_str());
                var_inicio = i;

                while (var_size < variableNames.size()) {
                    printf("OUTPUT %s   ", output[i].c_str());

                    output[i].erase();
                    i++;
                    var_size++;

                    if (output[i] == ",") {
                        var_size--;
                    }
                    printf("output %s\n", output[i].c_str());

                }
                                   
        
                var_final = i ;

                while (var_final < output_copy.size()) {
                    output[var_inicio] = output_copy[var_final];
                    //output_copy.push_back(output[k]);
                    //cout << "output[var_inicio] " + output[var_inicio] << endl;
                    //cout << "output_copy[var_final] " + output_copy[var_final] << endl;

                    var_final++;
                    var_inicio++;
                }
                /*for (int k = 5; k < macro.size(); k++) { //Adiciona macros no final do código
                    output.push_back(macro[k]);
                }*/
                //return;
            }
        } 
    }
   /* k = 0;
    while (k < output.size()) {
        cout << "output " + output[k] << endl;
        k++;
    }*/
}