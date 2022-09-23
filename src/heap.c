#include <stdio.h>
#include "headers/uteis.h"

//ADAPTAR = ITEM Marcadao = Maior que todos
int size = 0;
void swap(selecSub *a, selecSub *b){
  selecSub temp = *b;
  *b = *a;
  *a = temp;
}
void heapify(selecSub alunos[], int size, int i){
  if (size == 1){
    printf("Single element in the heap");
  }
  else{
    int menor = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if ((l < size && alunos[l].campoAluno.nota < alunos[menor].campoAluno.nota) && alunos[l].marcado == 0 && alunos[menor].marcado == 0)
      menor = l;
    if ((r < size && alunos[r].campoAluno.nota < alunos[menor].campoAluno.nota) && alunos[r].marcado == 0 && alunos[menor].marcado == 0)
      menor = r;
    if (menor != i){
      swap(&alunos[i], &alunos[menor]);
      heapify(alunos, size, menor);
    }
  }
}
void insert(selecSub alunos[], selecSub alunoTmp){
  if (size == 0){
    alunos[0] = alunoTmp;
    size += 1;
  }
  else{
    alunos[size] = alunoTmp;
    size += 1;
    for (int i = size / 2 - 1; i >= 0; i--){
      heapify(alunos, size, i);
    }
  }
}

void deleteRoot(selecSub alunos[], selecSub alunoTmp){
  int i;
  for (i = 0; i < size; i++)  {
    if (alunoTmp.campoAluno.nota == alunos[i].campoAluno.nota)
      break;
  }

  swap(&alunos[i], &alunos[size - 1]);
  size -= 1;
  for (int i = size / 2 - 1; i >= 0; i--){
    heapify(alunos, size, i);
  }
}
