#include <stdio.h>
#include "headers/uteis.h"

void swap(Aluno* a, Aluno* b){
    Aluno temp = *a;
    *a = *b;
    *b = temp;
}
 
void heapify(Aluno arr[], int N, int i){
    int maior = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
 
    if (left < N && (arr[left].nota < arr[maior].nota)){
        maior = left;
	}

    if (right < N && (arr[right].nota < arr[maior].nota)){
        maior = right;
	}

    if (maior != i) {
        swap(&arr[i], &arr[maior]);
        heapify(arr, N, maior);
    }
}

void heapifyMax(Aluno arr[], int N, int i){
    int maior = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
 
    if (left < N && (arr[left].nota > arr[maior].nota)){
        maior = left;
	}

    if (right < N && (arr[right].nota > arr[maior].nota)){
        maior = right;
	}

    if (maior != i) {
        swap(&arr[i], &arr[maior]);
        heapifyMax(arr, N, maior);
    }
}

void mimHeap(Aluno arr[], int N){
 
    for (int i = N / 2 - 1; i >= 0; i--)
        heapify(arr, N, i);
}

void heapSort(Aluno arr[], int N){
 
    for (int i = N / 2 - 1; i >= 0; i--)
        heapifyMax(arr, N, i);
 
    for (int i = N - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);
        heapifyMax(arr, i, 0);
    }
}
 
void printArray(Aluno arr[], int N){
    printf("HEAP\n");
    for (int i = 0; i < N; i++)
        printf("%.2lf\n", arr[i].nota);
    printf("FIM\n");
}
