#ifndef QUICKSORTEXTERNO_H
#define QUICKSORTEXTERNO_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include "structs.h"
#include "uteis.h"


void quicksort(int, int);

void QuickSortExterno(FILE **, FILE **,FILE **,int,int,Contadores*);

void Particao(FILE**,FILE**,FILE**,Pivo,int,int,int*,int*,Contadores*);

void leSup(FILE**,Aluno*,int *,short *);

void leInf(FILE**,Aluno*,int *,short *);

void escreveMin(FILE**,Aluno,int *);

void escreveMax(FILE**,Aluno,int *);



void inicializaPivo(Pivo*);

void inserePivo(Pivo*,Aluno,Contadores*);

void retiraMenorPivo(Pivo*,Aluno*);

void retiraMaiorPivo(Pivo*,Aluno*);



#endif 
