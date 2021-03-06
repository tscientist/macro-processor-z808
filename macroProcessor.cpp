#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <stdio.h>
#include "macroProcessor.hpp"
#include <string>

using namespace std;

MacroProcessor::MacroProcessor() { }

bool MacroProcessor::readFile(ifstream *file){ 
    char each_character;
    string retorno;
    if (file) { 
        while (file->get(each_character)) { //Percorre todos as letras do arquivo 

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

void MacroProcessor::passOne() {
    int t = 0;
    for (int i = 0; i < input.size(); i++) {
        if (input[i] == "MACRO"){
            int verifica_comentario = 0;
            t = i + 1;
            variableNames.push_back(input[i - 1]); //Adiciona chamada da macro

            while (input[t] != "\n") { //Salva npmes de variaveis
                if (input[t] == ";;") {//Sai do while se existe comentario
                    break;
                }

                if (input[t] != ",") {
                    variableNames.push_back(input[t]);
                }
                t++;
            }

            int l = t;
            while (input[l] != "\n") { 
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

            input[t + 1].erase();//Apaga ENDM
            input[flag].erase(); //Apaga a posi????o da macro
        }   
    }

    for (int i = 0; i < input.size(); i++) { //Preenche output
        if (input[i] != " ") {
            if (input[i] != "MACRO") {
                output.push_back(input[i]);
            }
        }
    }
}

void MacroProcessor::troca(int i, int j, vector<string> variables){
    for (int k = 1; k < variables.size(); k++){
        for (int t = 0; t < macro.size(); t++) {
            if (macro[t] == variables[k] && macro[t] != "") {
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

void MacroProcessor::fileEnding(string fileName) {
    int i = 0, flag = 1, p = 0;
    vector<string> output_final;
    vector<string> new_variables;

    while (output[i] != "END")
    {
        if (output[i] == variableNames[0]) {
            if (flag == 1) { //Primeira chamada de macro
                flag = 0;
                //J ?? a posi????o do nome da variavel 
                //I ?? a posi????o onde ?? chamado a macro
                //troca(i, j, variaveis)
                troca(i + 1, 1, variableNames);  //variabblesNames = [SomaMem, Mem1, Mem2]

                while (output[i] != "\n") {
                    if (output[i] != ",") {
                        new_variables.push_back(output[i]); //new_variables = [SomaMem, Var1, V]           
                    }
                    i++;
                }    
            } else {
                troca(i + 1, 1, new_variables);        
                int o = 0;           

                while (output[i] != "\n") {
                    if (output[i] != ",") {
                        new_variables[o] = output[i];
                        o++;   
                    }
                    i++;
                }   
            }
            int cont_inicio_macro = 0;

            for (int k = 0; k < macro.size(); k++) { //Pega inicio da macro sem parametros
                if (macro[k] == "") {
                    cont_inicio_macro = k;
                    break;
                }
            }
            
            for (int k = cont_inicio_macro; k < macro.size(); k++) { //Alterar valor de k para come??ar no final da linha
                output_final.push_back(macro[k]);
            }
        } else {
            output_final.push_back(output[i]);
            i++;
        }
    }

    output_final.push_back(output[i]);
    output_final.push_back(output[i + 1]);

    outFile.open("  " + fileName);

    for (int i = 0; i < output_final.size(); i++) {
        if (output_final[i] != " " && output_final[i] != "" ) {
            outFile << output_final[i] << " ";
        }
    }
}
