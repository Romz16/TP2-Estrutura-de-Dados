#ifndef HEAP_H
#define HEAP_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "structs.h"

void swap(selecSub *a, selecSub *b);
void heapify(selecSub alunos[], int size, int i);
void insert(selecSub alunos[], selecSub alunoTmp);
void deleteRoot(selecSub alunos[], selecSub alunoTmp);




#endif 
