#include <stdio.h>
#include "headers/uteis.h"

// Function to swap the position of two elements
 
void swap(selecSub* a, selecSub* b)
{
 
    selecSub temp = *a;
 
    *a = *b;
 
    *b = temp;
}
 
// To heapify a subtree rooted with node i
// which is an index in arr[].
// n is size of heap
void heapify(selecSub arr[], int N, int i)
{
    // Find maior among root, left child and right child
 
    // Initialize maior as root
    int maior = i;
 
    // left = 2*i + 1
    int left = 2 * i + 1;
 
    // right = 2*i + 2
    int right = 2 * i + 2;
 
    // If left child is larger than root
    if (left < N && (arr[left].campoAluno.nota > arr[maior].campoAluno.nota)){
        maior = left;
	}
 
    // If right child is larger than maior
    // so far
    if (right < N && (arr[right].campoAluno.nota > arr[maior].campoAluno.nota)){
        maior = right;
	}

    // Swap and continue heapifying if root is not maior
    // If maior is not root
    if (maior != i) {
 
        swap(&arr[i], &arr[maior]);
 
        // Recursively heapify the affected
        // sub-tree
        heapify(arr, N, maior);
    }
}
 
// Main function to do heap sort
void heapSort(selecSub arr[], int N)
{
 
    // Build max heap
    for (int i = N / 2 - 1; i >= 0; i--)
 
        heapify(arr, N, i);
 
    // Heap sort
    for (int i = N - 1; i >= 0; i--) {
 
        swap(&arr[0], &arr[i]);
 
        // Heapify root element to get highest element at
        // root again
        heapify(arr, i, 0);
    }
}
 
// A utility function to print array of size n
void printArray(selecSub arr[], int N)
{
    printf("HEAP\n");
    for (int i = 0; i < N; i++)
        printf("%.2lf=%i\n", arr[i].campoAluno.nota, arr[i].marcado);
    printf("FIM\n");
}
