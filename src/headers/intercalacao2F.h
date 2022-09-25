#ifndef BLOC_H
#define BLOC_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "structs.h"

typedef struct TipoBloco2{	
	Aluno campoAluno;
	int fitaOrigem;
	int fimBloco;
	int fimFita;
}TipoBloco2;

void ordenar_blocos(FILE*,FILE**,int);
void Insertion(TipoBloco*,int);
void intercalar_blocos(FILE**,int);
void intercalaSelecSub(int situacao, int quantidade);

#endif 
