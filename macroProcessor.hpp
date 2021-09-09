#ifndef PROCESSADOR_HPP
#define PROCESSADOR_HPP

#include <iostream>
#include <string.h>
#include <fstream>
#include <list>
#include <stdio.h>
#include <vector>

using namespace std;

class MacroProcessor{
    public:
        MacroProcessor();

        bool readFile(ifstream *arq);

	protected:
		vector<string> saida;
		vector<string> entrada;
		vector<string> macro;
		ofstream outFile;
};
#endif