#ifndef HEAP_H
#define HEAP_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "structs.h"

void swap(Aluno* a, Aluno* b);
void heapify(Aluno arr[], int N, int i);
void mimHeap(Aluno arr[], int N);
void printArray(Aluno arr[], int N);

#endif 
