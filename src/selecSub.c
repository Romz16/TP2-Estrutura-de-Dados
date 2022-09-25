#include "headers/uteis.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int driverSelecSub(int quantidade, int situacao){
  FILE *vetorFitas[MAXFITAS/2] = {NULL};
  if(abrirFitas(vetorFitas) != MAXFITAS)  
    return 0;

  FILE *arquivo = abrirArquivo(situacao);

  Aluno alunos[AREA_MAX];
  Aluno alunoTmp;
  Aluno tmpTroca;

  int countFitas = 0;
  int countFitasUsadas = 0;
  int countMarcados = 0;

  for (int i = 0; i < AREA_MAX && i < quantidade; i++){
    fread(&alunoTmp, sizeof(Aluno), 1, arquivo);
    alunos[i] = alunoTmp;
  }    

  heapSort(alunos, AREA_MAX-countMarcados);

  for (int i = 0; i < quantidade; i++){
    fwrite(&alunos[0], sizeof(Aluno), 1, vetorFitas[countFitas]);
    
    if(i < quantidade-AREA_MAX){

      fread(&alunoTmp, sizeof(Aluno), 1, arquivo);

      if(alunoTmp.nota < alunos[0].nota){
        alunos[0] = alunoTmp;
        countMarcados++;

        tmpTroca = alunos[0];
        alunos[0] = alunos[AREA_MAX-countMarcados];
        alunos[AREA_MAX-countMarcados] = tmpTroca;
      }
      else{
        alunos[0] = alunoTmp;
      } 
      
      if(countMarcados == AREA_MAX && countFitas != MAXFITAS/2-1){
        alunoTmp.nota = -1;
        fwrite(&alunoTmp, sizeof(Aluno), 1, vetorFitas[countFitas]);

        countFitas++;
        countFitasUsadas++;
        countMarcados = 0;
      }
      else if(countMarcados == AREA_MAX && countFitas == MAXFITAS/2-1){
        alunoTmp.nota = -1;
        fwrite(&alunoTmp, sizeof(Aluno), 1, vetorFitas[countFitas]);
        
        countFitas = 0;
        countMarcados = 0;
      }

      heapSort(alunos, AREA_MAX-countMarcados);
          
    }
    else{

      tmpTroca = alunos[0];
      alunos[0] = alunos[AREA_MAX-1];
      alunos[AREA_MAX-1] = tmpTroca;

      heapSort(alunos, AREA_MAX-1);

      alunoTmp.nota = -1;
      fwrite(&alunoTmp, sizeof(Aluno), 1, vetorFitas[countFitas]);

      if(countFitas != MAXFITAS/2-1){
        countFitas++;
        countFitasUsadas++;
      }
      else if (countFitas == MAXFITAS/2-1){
        countFitas++;
      }

      for (int j = 0; j < AREA_MAX-1; j++){
        fwrite(&alunos[j], sizeof(Aluno), 1, vetorFitas[countFitas]);
      }    

      alunoTmp.nota = -1;
      fwrite(&alunoTmp, sizeof(Aluno), 1, vetorFitas[countFitas]);

      break;
    }
  }   
  
  for (int i = 0; i <= countFitasUsadas && i < MAXFITAS/2; i++){
    fclose(vetorFitas[i]);
  }

  fclose(arquivo);
  //verificaSaida();
  //printFitas();
  
  return 1;
}

#define QUANTIDADE 1000
void verificaSaida(){

  Aluno vetorAlunosFitas[QUANTIDADE];
  Aluno vetorAlunosArquivo[QUANTIDADE];

  FILE *fitas[MAXFITAS];
  FILE *arquivo = abrirArquivo(3);

  char nomeArquivo[50] = "";
  size_t idx = 0;
  Aluno tmp;
  for (size_t i = 0; i < MAXFITAS; i++) {
    sprintf (nomeArquivo, "data/fitas/fita%zu.dat", i);
    fitas[idx] = fopen (nomeArquivo, "rb");
    if (!fitas[idx]){ 
      printf("Erro ao Abrir arquivo Fita: %s\n", nomeArquivo);
      continue;
    }
    idx++;
  }

  int k = 0;
  for (int i = 0; i < 40; i++){
    while (fread(&tmp, sizeof(Aluno), 1, fitas[i]) == 1){
      if(tmp.nota != -1){
        vetorAlunosFitas[k] = tmp;
        k++;
      }
    }
  }


  for (int i = 0; i < QUANTIDADE; i++){
    fread(&tmp, sizeof(Aluno), 1, arquivo);
    vetorAlunosArquivo[i] = tmp;
  }

  int i, j, min_idx;
  for (i = 0; i < QUANTIDADE-1; i++){
    min_idx = i;
    for (j = i+1; j < QUANTIDADE; j++)
      if (vetorAlunosArquivo[j].nota < vetorAlunosArquivo[min_idx].nota)
        min_idx = j;

    if(min_idx != i){
      Aluno temp = vetorAlunosArquivo[min_idx];
      vetorAlunosArquivo[min_idx] = vetorAlunosArquivo[i];
      vetorAlunosArquivo[i] = temp;
    }
  }
  for (i = 0; i < QUANTIDADE-1; i++){
    min_idx = i;
    for (j = i+1; j < QUANTIDADE; j++)
      if (vetorAlunosFitas[j].nota < vetorAlunosFitas[min_idx].nota)
        min_idx = j;

    if(min_idx != i){
      Aluno temp = vetorAlunosFitas[min_idx];
      vetorAlunosFitas[min_idx] = vetorAlunosFitas[i];
      vetorAlunosFitas[i] = temp;
    }
  }

  for (int i = 0; i < QUANTIDADE; i++){
    if(vetorAlunosArquivo[i].nota != vetorAlunosFitas[i].nota)
      printf("ERRO = ");
    printf("%.2lf / %.2lf\n", vetorAlunosArquivo[i].nota, vetorAlunosFitas[i].nota);
  }
  

  fclose(arquivo);
  for (int i = 0; i < MAXFITAS; i++){
      fclose(fitas[i]);
  }

}
