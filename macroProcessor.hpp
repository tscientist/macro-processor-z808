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

        bool readFile(ifstream *file);

		void push(string value); 

        void passOne();

		void passTwo();		

		void troca(int i, int j);

		void fileEnding();		

		void createOutputFile(string fileName);

	protected:
		vector<string> output;
		vector<string> input;
		vector<string> macro;
		vector<string> variableNames;
		ofstream outFile;
};
#endif