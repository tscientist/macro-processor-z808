// Construção das funções declaradas em processador_macros.hpp

#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include "macroProcessor.hpp"

using namespace std;

MacroProcessor::MacroProcessor() { }

bool MacroProcessor::readFile(ifstream *file){ 
    if (file){  
        return true;
    } else {
        return false;
    }
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