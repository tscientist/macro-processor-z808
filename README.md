## Processador de Macros Z808
Processador de macros criado para a disciplina de **Programação de Sistemas**, o processador foi desenvolvido em conjunto utilizando a linguagem **C++**.

## Descrição do processador
1. **Descrição do Processador de Macros:** O processamento de macros deve permitir a definição de macros dentro de macros (macros aninhadas), bem como a chamada de macros dentro de macros (chamadas aninhadas), sendo, portanto, implementado em uma só passagem. O programa receberá como entrada um arquivo fonte informado para montagem e gerará como saída outro arquivo fonte com o nome pré-definido. 

		Entrada: "teste_macro_z808.asm"
		Saída: " teste_macro_z808.asm"

2. As macros são definidas através das pseudo-operações conforme a sintaxe descrita no livro.

3. **Conceitos:** Uma macro pode ser definida em qualquer parte do código-fonte sendo que uma macro só pode ser referenciada após ter sido definida). A macro SomaMem possui dois parâmetros formais (argumentos): Mem1 e Mem2. A diretiva ENDM indica o fim da definição da macro.

## Instalação e execução
Será necessária a instalação de um compilador de **C/C++** que pode ser encontrado [aqui](https://www.mingw-w64.org/).

Crie um diretório e baixe o código disponível com o comando `git clone https://github.com/tscientist/macro-processor-z808.git`.

O programa pode ser executado através do **terminal** utilizando o comando `g++ main.cpp -o main`.

E executado com o comando `./main`
