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

// void MacroProcessor::createOutputFile(string fileName){
//     outFile.open("  " + fileName);

//     for (int i = 0; i < output.size(); i++) {
//         if (output[i] != " " && output[i] != "" ) {
//             outFile << output[i] << " ";
//         }
//     }
// }

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

void MacroProcessor::fileEnding(string fileName) {
    int i = 0, flag = 1;

    vector<string> output_final;

    while (output[i] != "END")
    {
        if (output[i] == variableNames[0]) {
            while (output[i] != "\n") {
                i++;
            } 

            for (int k = 4; k < macro.size(); k++) { //verifica virgula
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
