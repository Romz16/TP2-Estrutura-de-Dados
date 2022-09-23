#ifndef UTEIS_H
#define UTEIS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "structs.h"
#include "sortInterno.h"
#include "selecSub.h"
#include "intercalacao2F.h"
#include "quickSortExterno.h"

int GerarArq();
void criaArquivo();
int abrirFitas(FILE **fp);
FILE *abrirArquivo(int situacao);
void printFitas();

#endif 
