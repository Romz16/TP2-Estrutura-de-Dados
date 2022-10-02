#ifndef SORTINT_H
#define SORTINT_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "structs.h"
#include "uteis.h"

void criaBlocos(int quantidade, int situacao);
void sortInterno(int situacao, int quantidade);
void ordenaAlunos(Aluno blocos[]);

#endif
