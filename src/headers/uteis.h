#ifndef UTEIS_H
#define UTEIS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "structs.h"
#include "heap.h"

#include "sortInterno.h"
#include "selecSub.h"
#include "intercalacao2F.h"
#include "quickSortExterno.h"

FILE *abrirArquivo(int situacao);
void printRegistros(int situacao, int quantidade);

int abrirFitas(FILE **fp);
void printFitas();
void resetFitas(int modo);

short verificaArquivosBinarios();
void gerarArquivosBinarios();
void imprimeContadores(Contadores);

void geraArquivoTexto(char nomeArquivo[50]);
void funcaoTestesAltomatizados();
void gerenciaContadores(int op);

#endif 
