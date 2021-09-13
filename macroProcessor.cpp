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
    for (int i = 0; i < output.size(); i++){
        if (output[i] == ","){
            output[i-1].erase();
            while(output[i] != "Inicio"){
                output[i++].erase();
            }
        }
    }

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

            for (int j = i; input[j] != "ENDM"; j++) {
                macro.push_back(input[j]);
                input[j].erase();
                t = j;
            }

            input[t+1].erase();
        }   
    }
    for (int i = 0; i < input.size(); i++) {
        if (input[i] != " ") {
            output.push_back(input[i]);
        }
    }
    //ESTA SALVANDO O MACRO
    /*int k = 0;
    while (k < output.size()) {
        cout << "output " + output[k] << endl;
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
                
                troca(i+1, j+1);
            }
        }
    } 
}

void MacroProcessor::troca(int i, int j){
    for (int k = j; k < variableNames.size(); k++){
        for (int t = 0; t < macro.size(); t++) {
            if (macro[t] == variableNames[k] && macro[t] != "") {
                macro[t] = output[i];        
                printf("variaveis %s   ", variableNames[k].c_str());
                printf("macro %s\n", macro[t].c_str());
            }
            if (i < output.size()-1){
                i++;
            }       
        }
    }
}

void MacroProcessor::fileEnding(){
    int t = 0;
    for (int i = 0; i < output.size(); i++){
        for (int j = 0; j < variableNames.size(); j++) {
            //cout << "d[k] " + output[i] << endl;

           /* if (output[i] == variableNames[j]){
  
                output[i].erase();
                for (int k = j; k < macro.size(); k++) {

                    if (macro[k] == "ENDM") {
                        t = 0;
                    }
                  if (macro[k] == ",") {
                        t = 0;    
                    }
                    if (t == 1) {
                        output.push_back(macro[k]);
                    }

                    if (macro[k] == ";;") {
                        t = 1;
                    }
                }*/
                //return;
            }
        
    } 
}