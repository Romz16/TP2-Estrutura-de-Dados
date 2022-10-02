#ifndef BLOC_H
#define BLOC_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "structs.h"
#include "sortInterno.h"

void intercalacao(int situacao, int quantidade);
void lePrimeiroElemento(TipoBloco *blocos,FILE **vetorFitas);

#endif 
