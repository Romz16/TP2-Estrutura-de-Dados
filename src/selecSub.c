#include "headers/uteis.h"

#include <stdlib.h>

int driverSelecSub(int metodo, int quantidade, int situacao){
    FILE *vetorFitas[MAXFITAS/2] = {NULL};
    if(abrirFitas(vetorFitas) != MAXFITAS)  
      return 0;
  

    FILE *arquivo = abrirArquivo(situacao);

    selecSub alunos[MAXINTERNO];
    selecSub alunoTmp;

    for (int i = 0; i < MAXINTERNO && i < quantidade; i++){
      fread(&alunoTmp.campoAluno, sizeof(aluno), 1, arquivo);
      //printf("*%ld-%lf-%s-%s-%s*\n", alunoTmp.campoAluno.nInscricao, alunoTmp.campoAluno.nota, alunoTmp.campoAluno.estado, alunoTmp.campoAluno.cidade, alunoTmp.campoAluno.curso);
      insert(alunos, alunoTmp);
    }    

    //escreve o item na fita atual
    int countFitas = 0;
    int countMarcados = 0;
    for (int i = 0; i < quantidade; i++){
      fwrite(&alunos[0], sizeof(aluno), 1, vetorFitas[countFitas]);
      //printf("*%ld-%lf-%s-%s-%s*\n", alunos[0].campoAluno.nInscricao, alunos[0].campoAluno.nota, alunos[0].campoAluno.estado, alunos[0].campoAluno.cidade, alunos[0].campoAluno.curso);
      
      //nao esta nos ultimos 20
      if(i < quantidade-MAXINTERNO){

          fread(&alunoTmp.campoAluno, sizeof(aluno), 1, arquivo);

          if(alunoTmp.campoAluno.nota < alunos[0].campoAluno.nota){
              alunoTmp.marcado = 1;
              countMarcados++;
          }
          else
              alunoTmp.marcado = 0;
          
          deleteRoot(alunos, alunos[0]);
          insert(alunos, alunoTmp);

          if(countMarcados == MAXINTERNO && countFitas != MAXFITAS/2-1){
              countFitas++;
              countMarcados = 0;
          }
          if(countMarcados == MAXINTERNO && countFitas == MAXFITAS/2-1){
              countFitas = 0;
              countMarcados = 0;
          }
            
        }
        //esta nos últimos 20
        //Escreve a raiz e deleta o raiz e refaz o heep 
        else{
          for (int i = 0; i < MAXINTERNO; i++)
            alunos[i].marcado = 0;                
          
          deleteRoot(alunos, alunos[0]);
        }
    }   
    
    // for (int i = 0; i < MAXFITAS; i++){
    //   fclose(vetorFitas[i]);
    // }

    printFitas();
    
    return 1;
}

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
    if ((l < size && alunos[l].campoAluno.nota < alunos[menor].campoAluno.nota) && alunos[l].marcado == 0)
      menor = l;
    if ((r < size && alunos[r].campoAluno.nota < alunos[menor].campoAluno.nota) && alunos[r].marcado == 0)
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
