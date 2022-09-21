#ifndef BLOC_H
#define BLOC_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "structs.h"

typedef struct TipoBloco
{	
	aluno v[10];
	int n;
	int pertence[10];
}TipoBloco;

void ordenar_blocos(FILE*,FILE**,int);
void Insertion(TipoBloco*,int);
void intercalar_blocos(FILE**,int);


#endif 
