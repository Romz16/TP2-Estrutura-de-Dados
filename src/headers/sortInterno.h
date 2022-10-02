#ifndef SORTINT_H
#define SORTINT_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "structs.h"
#include "uteis.h"

void criaBlocos(int quantidade, int situacao);
void insertDeBlocos(TipoBloco **blocos);
void sortInterno(int situacao, int quantidade);
void InsertionReg(Aluno **alunoTmp,int Tam);
#endif
