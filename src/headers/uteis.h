#ifndef UTEIS_H
#define UTEIS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "structs.h"
#include "heap.h"

#include "sortInterno.h"
#include "selecSub.h"
#include "intercalacao2F.h"
#include "quickSortExterno.h"


int GerarArq();
void criaArquivo();
int abrirFitas(FILE **fp);
FILE *abrirArquivo(int situacao);
void printFitas();
void printRegistros(int situacao, int quantidade);

short verificaArquivosBinarios();
void gerarArquivosBinarios();
void imprimeContadores(Contadores);
//Carrega um bloco da memoria externa menor que 20 ,ordena em memória interna com selection sort e escreve o bloco ordenado no subarquivo. 
//Usado no quicksort externo quando o tamanho de uma subarquivo é inferior a quantidqade mínima disponível de memória interna.
void selectionSortExterno(int,int,FILE**,FILE**,Contadores*);

#endif 
