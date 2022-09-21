#ifndef UTEIS_H
#define UTEIS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "structs.h"
#include "sortInterno.h"
#include "selecSub.h"
#include "intercalacao2F.h"

#define TRUE 1
#define FALSE 0

typedef struct{
    long mat;
    float nota;
    char estado[3];
    char cidade[51];
    char curso[31];
}Item;
int GerarArq();

void criaArquivo();
int abrirFitas(int situacao, FILE **vetorFitas);
FILE *abrirArquivo(int situacao);

#endif 
