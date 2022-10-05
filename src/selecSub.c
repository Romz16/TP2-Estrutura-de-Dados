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

  Aluno alunos[AREA_MAX_SEL];
  Aluno alunoTmp;

  int countFitas = 0;
  int countFitasUsadas = 0;
  int countMarcados = 0;


  //Leitura dos 20 (AREA_MAX_SEL) primeiros itens do arquivo para a memoria principal
  for (int i = 0; i < AREA_MAX_SEL && i < quantidade; i++){
    ContadoresIndividuais.transferencias++;
    fread(&alunoTmp, sizeof(Aluno), 1, arquivo);
    alunos[i] = alunoTmp;
  }    

  //Constroi o heap
  mimHeap(alunos, AREA_MAX_SEL-countMarcados);

  for (int i = 0; i <= quantidade; i++){
    //Escreve o item 0 do vetor de alunos (menor) para o fita escrita atual (countFitas)
    ContadoresIndividuais.transferencias++;
    fwrite(&alunos[0], sizeof(Aluno), 1, vetorFitas[countFitas]);
    
    //Se não chegou nos 20 ultimos
    if(i < quantidade-AREA_MAX_SEL){

      //Leitura de mais um item do arquivo
      ContadoresIndividuais.transferencias++;
      fread(&alunoTmp, sizeof(Aluno), 1, arquivo);

      //Verifica se ele é menor que o item que acabou de ser escrito 
      ContadoresIndividuais.comparacoes++;
      if(alunoTmp.nota < alunos[0].nota){
        //Item e marcado
        alunos[0] = alunoTmp;
        countMarcados++;

        //Movido para o fim do heap
        alunoTmp = alunos[0];
        alunos[0] = alunos[AREA_MAX_SEL-countMarcados];
        alunos[AREA_MAX_SEL-countMarcados] = alunoTmp;
      }
      else{
        alunos[0] = alunoTmp;
      } 

      //Verifica se todos os itens do vetor estão marcados 
      //E se não chegou na ultima fita de entrada (19)       
      if(countMarcados == AREA_MAX_SEL && countFitas != MAXFITAS/2-1){
        //Escreve um aluno com nota -1 para diferenciar os blocos
        alunoTmp.nota = -1;
        ContadoresIndividuais.transferencias++;
        fwrite(&alunoTmp, sizeof(Aluno), 1, vetorFitas[countFitas]);

        countFitas++;
        countFitasUsadas++;
        countMarcados = 0;
      }
      else if(countMarcados == AREA_MAX_SEL && countFitas == MAXFITAS/2-1){
        alunoTmp.nota = -1;
        ContadoresIndividuais.transferencias++;
        fwrite(&alunoTmp, sizeof(Aluno), 1, vetorFitas[countFitas]);
        
        countFitas = 0;
        countMarcados = 0;
      }

      mimHeap(alunos, AREA_MAX_SEL-countMarcados);
          
    }
    //Chegou nos últimos 20
    else{

      //Verifica qual o primeiro item do bloco atual
      
      alunoTmp = alunos[0];
      printf("------%.2lf------\n", alunoTmp.nota);

      alunoTmp = alunos[0];
      alunos[0] = alunos[AREA_MAX_SEL-1];
      alunos[AREA_MAX_SEL-1] = alunoTmp;

      heapSort(alunos, AREA_MAX_SEL-1);

      //Item no vetor alunos maiores que esse item fica na fita atual       
      int index = AREA_MAX_SEL-1;
      for (int i = 0; i < AREA_MAX_SEL-1; i++){
        ContadoresIndividuais.comparacoes++;
        if(alunos[i].nota >= alunoTmp.nota){
          ContadoresIndividuais.transferencias++;
          fwrite(&alunos[i], sizeof(Aluno), 1, vetorFitas[countFitas]);
        }
        else{
          index = i;
          break;
        }  
      }

      alunoTmp.nota = -1;
      ContadoresIndividuais.transferencias++;
      fwrite(&alunoTmp, sizeof(Aluno), 1, vetorFitas[countFitas]);

      if(countFitas != MAXFITAS/2-1){
        countFitas++;
        countFitasUsadas++;
      }
      else if (countFitas == MAXFITAS/2-1){
        countFitas++;
      }

      printf("-------%i-------\n", countFitas);
      //Item no vetor alunos menores que esse item fica na proxima fita 
      for (int j = index /* int j = 0 */; j < AREA_MAX_SEL-1; j++){
        ContadoresIndividuais.transferencias++;
        printf("-------%i-------\n", countFitas);
        fwrite(&alunos[j], sizeof(Aluno), 1, vetorFitas[countFitas]);
      }    

      if(index != AREA_MAX_SEL-1){
        alunoTmp.nota = -1;
        ContadoresIndividuais.transferencias++;
        fwrite(&alunoTmp, sizeof(Aluno), 1, vetorFitas[countFitas]);
      }

      break;
    }
  }   
  
  for (int i = 0; i <= countFitasUsadas && i < MAXFITAS/2; i++)
    fclose(vetorFitas[i]);

  fclose(arquivo);
  
  return 1;
}

void selecSub(int situacao, int quantidade){
    
    clock_t inicio = clock();
    
    resetFitas(0);
    driverSelecSub(quantidade+3, situacao);
    intercalacao(situacao, quantidade+3);

    clock_t fim = clock();
    
    ContadoresIndividuais.tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    imprimeContadores(ContadoresIndividuais);
}
