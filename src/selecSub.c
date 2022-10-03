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

  //Leitura dos 20 (AREA_MAX) primeiros itens do arquivo para a memoria principal
  for (int i = 0; i < AREA_MAX && i < quantidade; i++){
    fread(&alunoTmp, sizeof(Aluno), 1, arquivo);
    alunos[i] = alunoTmp;
  }    

  //Constroi o heap
  mimHeap(alunos, AREA_MAX-countMarcados);

  for (int i = 0; i <= quantidade; i++){
    //Escreve o item 0 do vetor de alunos (menor) para o fita escrita atual (countFitas)
    fwrite(&alunos[0], sizeof(Aluno), 1, vetorFitas[countFitas]);
    
    //Se não chegou nos 20 ultimos
    if(i < quantidade-AREA_MAX){

      //Leitura de mais um item do arquivo
      fread(&alunoTmp, sizeof(Aluno), 1, arquivo);

      //Verifica se ele é menor que o item que acabou de ser escrito 
      if(alunoTmp.nota < alunos[0].nota){
        //Item e marcado
        alunos[0] = alunoTmp;
        countMarcados++;

        //Movido para o fim do heap
        tmpTroca = alunos[0];
        alunos[0] = alunos[AREA_MAX-countMarcados];
        alunos[AREA_MAX-countMarcados] = tmpTroca;
      }
      else{
        alunos[0] = alunoTmp;
      } 

      //Verifica se todos os itens do vetor estão marcados 
      //E se não chegou na ultima fita de entrada (19)       
      if(countMarcados == AREA_MAX && countFitas != MAXFITAS/2-1){
        //Escreve um aluno com nota -1 para diferenciar os blocos
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

      mimHeap(alunos, AREA_MAX-countMarcados);
          
    }
    //Chegou nos últimos 20
    else{
      //Verifica qual o primeiro item da fita atual
      //Item no vetor alunos menores que esse item fica na fita atual 
      //Item no vetor alunos menor que esse item fica na proxima fita 

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
  
  for (int i = 0; i <= countFitasUsadas && i < MAXFITAS/2; i++)
    fclose(vetorFitas[i]);

  fclose(arquivo);
  
  return 1;
}

void selecSub(int situacao, int quantidade){
    resetFitas(0);
    driverSelecSub(quantidade+1, situacao);
    intercalacao(situacao, quantidade+1);
}
