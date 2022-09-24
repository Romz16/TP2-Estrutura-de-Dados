#ifndef HEAP_H
#define HEAP_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "structs.h"

void printArray(selecSub arr[], int N);
void heapSort(selecSub arr[], int N);
void heapify(selecSub arr[], int N, int i);
void swap(selecSub* a, selecSub* b);





#endif 
