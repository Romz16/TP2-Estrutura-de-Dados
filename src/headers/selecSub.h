#ifndef SUB_H
#define SUB_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "structs.h"

int driverSelecSub(int metodo, int quantidade, int situacao);
void swap(selecSub *a, selecSub *b);
void heapify(selecSub alunos[], int size, int i);
void insert(selecSub alunos[], selecSub alunoTmp);
void deleteRoot(selecSub alunos[], selecSub alunoTmp);

#endif 
