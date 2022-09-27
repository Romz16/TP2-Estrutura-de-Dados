#ifndef BLOC_H
#define BLOC_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "structs.h"
#include "sortInterno.h"


typedef struct TipoBloco2{	
	Aluno campoAluno;
	int fitaOrigem;
	int fitaInativa;
	int fimBloco;
	int fimFita;
}TipoBloco2;

void intercalaSelecSub(int situacao, int quantidade);

#endif 
