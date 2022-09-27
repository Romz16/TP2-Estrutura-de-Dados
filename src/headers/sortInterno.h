#ifndef SORTINT_H
#define SORTINT_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "structs.h"
#include "uteis.h"

void quick_sort_int (TipoBloco *a, int n);
void ordenar_blocos(FILE *arq, FILE **saida, int cont);
int criaBlocosInterno(int  quantidade,int situacao);

#endif
