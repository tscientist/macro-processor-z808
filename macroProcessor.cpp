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
            if (each_character == '\n' || each_character == ' ') { 
                if (retorno != "") {
                    push(retorno);
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

    for (int i = 0; i < output.size(); i++) {
        if (output[i] != " " && output[i] != "" && output[i] != ";") {
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
                variableNames.push_back(input[t]);
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
            macro.push_back("ENDM");
            input[t+1].erase();
        }   
    }
    for (int i = 0; i < input.size(); i++) {
        if (input[i] != " ") {
            output.push_back(input[i]);
        }
    }
}
