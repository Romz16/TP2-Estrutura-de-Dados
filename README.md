Instruções makefile
________________________________________________________

• Compilar e Gerar Executável 
	make
	make all
________________________________________________________

• Compilar e Gerar Executável e Executar
	make go
________________________________________________________

• Limpar cmd e arquivos de compilação (.exe e .o)
	make clean
________________________________________________________

<!--
git branch
master
menor

//--------------------------------------------------------------------------------------------------------------------------

COMPILAR
gcc src/arvoreB.c src/arvoreBEstrela.c src/arvoreBinaria.c src/main.c src/sequencialIndexado.c src/uteis.c -o pesquisa.exe -Wall
gcc *.c -o pesquisa.exe -Wall
./pesquisa.exe 

make
./pesquisa.exe 

//--------------------------------------------------------------------------------------------------------------------------

EXEMPLO EXECUÇÃO
./pesquisa.exe criarArquivo
./pesquisa.exe testesAutomatizados < data/input.in > data/output.out
./pesquisa.exe 3 100 1 50

FUNCAO TESTE
./pesquisa.exe testesAutomatizados < data/input.in > data/output.out
metodo | quantidadeDeRegistros(Tamaho do arquivo) | situacao | quantidadeTeste
-1 pra parar

//--------------------------------------------------------------------------------------------------------------------------

DEBUG C
gcc *.c -g 
gdb ./a.out

run
backtrace

int metodo = 3;
int quantidade = 1000;
int situacao = 1;
int chave = 50;
-->