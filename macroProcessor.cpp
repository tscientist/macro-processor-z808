// Construção das funções declaradas em processador_macros.hpp

#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include "macroProcessor.hpp"

using namespace std;

MacroProcessor::MacroProcessor() { }

bool MacroProcessor::readFile(ifstream *file ){ 
    if (file){  
        return true;
    } else {
        return false;
    }
}
