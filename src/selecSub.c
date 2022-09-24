#include "headers/uteis.h"

#include <stdlib.h>

int driverSelecSub(int quantidade, int situacao){
  FILE *vetorFitas[MAXFITAS/2] = {NULL};
  if(abrirFitas(vetorFitas) != MAXFITAS)  
    return 0;

  FILE *arquivo = abrirArquivo(situacao);

  selecSub alunos[MAXINTERNO];
  selecSub alunoTmp;
  selecSub tmpTroca;

  int countFitas = 0;
  int countFitasUsadas = 0;
  int countMarcados = 0;

  for (int i = 0; i < MAXINTERNO && i < quantidade; i++){
    fread(&alunoTmp.campoAluno, sizeof(aluno), 1, arquivo);
    alunoTmp.marcado = 0;
    alunos[i] = alunoTmp;
  }    

  heapSort(alunos, MAXINTERNO-countMarcados);
  //printArray(alunos, MAXINTERNO-countMarcados);

  for (int i = 0; i < quantidade; i++){
    fwrite(&alunos[0], sizeof(aluno), 1, vetorFitas[countFitas]);
    
    if(i < quantidade-MAXINTERNO){

      fread(&alunoTmp.campoAluno, sizeof(aluno), 1, arquivo);
      //printf("ENTRANDO: %.2lf\n", alunoTmp.campoAluno.nota);

      if(alunoTmp.campoAluno.nota < alunos[0].campoAluno.nota){
        alunoTmp.marcado = 1;
        alunos[0] = alunoTmp;
        countMarcados++;

        tmpTroca = alunos[0];
        alunos[0] = alunos[MAXINTERNO-countMarcados];
        alunos[MAXINTERNO-countMarcados] = tmpTroca;
      }
      else{
        alunoTmp.marcado = 0;  
        alunos[0] = alunoTmp;
      } 
      
      if(countMarcados == MAXINTERNO && countFitas != MAXFITAS/2-1){
        alunoTmp.campoAluno.nota = -1;
        fwrite(&alunoTmp, sizeof(aluno), 1, vetorFitas[countFitas]);

        countFitas++;
        countFitasUsadas++;
        countMarcados = 0;
        for (int i = 0; i < MAXINTERNO; i++)
          alunos[i].marcado = 0; 
      }
      else if(countMarcados == MAXINTERNO && countFitas == MAXFITAS/2-1){
        alunoTmp.campoAluno.nota = -1;
        fwrite(&alunoTmp, sizeof(aluno), 1, vetorFitas[countFitas]);
        
        countFitas = 0;
        countMarcados = 0;
        for (int i = 0; i < MAXINTERNO; i++)
          alunos[i].marcado = 0; 
      }

      heapSort(alunos, MAXINTERNO-countMarcados);
      //printArray(alunos, MAXINTERNO);
          
    }
    else{
      //printf("ULTIMOS 20\n");

      tmpTroca = alunos[0];
      alunos[0] = alunos[MAXINTERNO-1];
      alunos[MAXINTERNO-1] = tmpTroca;

      heapSort(alunos, MAXINTERNO-1);
      //printArray(alunos, MAXINTERNO);

      alunoTmp.campoAluno.nota = -1;
      fwrite(&alunoTmp, sizeof(aluno), 1, vetorFitas[countFitas]);

      if(countFitas != MAXFITAS/2-1){
        countFitas++;
        countFitasUsadas++;
      }
      else if (countFitas == MAXFITAS/2-1){
        countFitas++;
      }

      for (int j = 0; j < MAXINTERNO-1; j++){
        alunos[j].marcado = 0;            
        fwrite(&alunos[j], sizeof(aluno), 1, vetorFitas[countFitas]);
      }    

      alunoTmp.campoAluno.nota = -1;
      fwrite(&alunoTmp, sizeof(aluno), 1, vetorFitas[countFitas]);

      break;
    }
  }   
  
  for (int i = 0; i <= countFitasUsadas; i++){
    fclose(vetorFitas[i]);
  }

  fclose(arquivo);
  printFitas();
  
  return 1;
}
