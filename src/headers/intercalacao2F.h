#ifndef BLOC_H
#define BLOC_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "structs.h"
#include "sortInterno.h"

void intercalacao(int situacao, int quantidade);

int leItemFita(int i, int j, TipoBloco *blocos, FILE *vetorFitas);
void ordenaBloco(TipoBloco blocos[]);
void deletaFitas(int fitaEscritaAtual, int fita, FILE *vetorFitas[MAXFITAS]);

#endif 
