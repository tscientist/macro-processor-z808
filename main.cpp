#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include "macroProcessor.cpp"

using namespace std;

string fileName = "teste_macro_z808.asm";

int main(){
	MacroProcessor macro; 

	ifstream input;

	input.open(fileName);
 	
    if (!input){
        cout << "Não foi possível abrir o arquivo!" << endl;
        return 0;
  	}

  	if (!macro.readFile(&input)){ 
        cout << "Não foi possivel ler o arquivo! " << endl;
  	}

    cout << fileName + " aberto" << endl;
    
    macro.passOne();

    macro.createOutputFile(fileName);

  	input.close();
    
	return 0;
}
