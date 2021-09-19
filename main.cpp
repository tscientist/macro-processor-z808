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
            printf("Não foi possivel ler o arquivo! \n");
            return 0;
      }

      if (!macro.readFile(&input)){ 
            printf("Não foi possivel ler o arquivo! \n");
            return 0;
      }

      printf("%s aberto.\n", fileName.c_str());

      macro.passOne();
      macro.fileEnding(fileName);

      input.close();

      return 0;
}
