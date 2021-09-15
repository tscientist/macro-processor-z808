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
                    switch (each_character)
                    {
                    case '\n':
                        push(retorno);
                        push("\n");
                    break;
                    case ',':
                        push(retorno);
                        push(",");
                    break;                    
                    default:
                        push(retorno);
                        break;
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
    outFile.open("  " + fileName);

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

            int l = t++;
            while (input[l] != "mov") { 
                input[l].erase();
                l++;
            }

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
            input[flag].erase();//Revisar essa parte
        }   
    }

    for (int i = 0; i < input.size(); i++) {
        if (input[i] != " ") {
            if (input[i] != "MACRO") {
                output.push_back(input[i]);
            }
        }
    }

    for (int i = 0; i < output.size(); i++) {
        for (int j = 0; j < variableNames.size(); j++) {
            //J é a posição do nome da variavel 
            //I é a posição onde é chamado a macro
            if (output[i] == variableNames[j]) {
                troca(i + 1, j + 1);
            }
        }
    } 
}

void MacroProcessor::troca(int i, int j){
    for (int k = j; k < variableNames.size(); k++){
        printf("variavel[%d] %s outupt[%d] %s \n", k, variableNames[k].c_str(), i, output[i].c_str());

        for (int t = 0; t < macro.size(); t++) {
            printf("variavel[%d] %s macro[%d] %s \n", k, variableNames[k].c_str(), i, macro[t].c_str());

            if (macro[t] == variableNames[k] && macro[t] != "") {
                //printf("macro %s variavel %s outupt %s \n", macro[t].c_str(), variableNames[k].c_str(), output[i].c_str());
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
    vector<string> output_copy;
    int var_inicio = 0, var_final = 0, var_size = 0;
    int k = 0;

    while (k < output.size()) {
        output_copy.push_back(output[k]);
        k++;
    }

    for (int i = 0; i < output.size(); i++) {
        if (output[i] == variableNames[0]) {
            var_inicio = i;
            while (var_size < variableNames.size()) {
                output[var_inicio].erase();//Remove descrição dos parametros da macro

                var_inicio++;
                var_size++;

                if (output[var_inicio] == ",") {
                    var_size--;
                }
            }                   
            var_size++;
            var_size += i;

            for (int k = 5; k < macro.size(); k++) { //Adiciona macros no final do código
                output[var_inicio] = macro[k];
                var_inicio++;
            }
        }
        
    }

    for (int k = var_size; k < output_copy.size(); k++) { //Adiciona resto do código
        output.push_back(output_copy[k]);
    }
}
