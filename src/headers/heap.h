#ifndef HEAP_H
#define HEAP_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "structs.h"

void swap(aluno* a, aluno* b);
void heapify(aluno arr[], int N, int i);
void heapSort(aluno arr[], int N);
void printArray(aluno arr[], int N);

#endif 
