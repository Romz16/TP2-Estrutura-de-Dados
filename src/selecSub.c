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
      ContadoresIndividuais.comparacoes++;
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
    // else{
      
      // if(countMarcados != 0){
      //   //Se tiver marcados escreve os não marcados para a fita atual e os marcados para a proxima

      //   //Escreve os itens não marcados na fita atual  
      //   heapSort(alunos, AREA_MAX-1);
      //   for (int j = 0; j < (AREA_MAX-1)-countMarcados; j++){
      //     fwrite(&alunos[j], sizeof(Aluno), 1, vetorFitas[countFitas]);
      //     heapSort(alunos, AREA_MAX-1);
      //   }

      //   //Atualizacaoes 
      //   tmpTroca = alunos[0];
      //   alunos[0] = alunos[AREA_MAX-1];
      //   alunos[AREA_MAX-1] = tmpTroca;

      //   heapSort(alunos, AREA_MAX-1);

      //   alunoTmp.nota = -1;
      //   fwrite(&alunoTmp, sizeof(Aluno), 1, vetorFitas[countFitas]);

      //   if(countFitas != MAXFITAS/2-1){
      //     countFitas++;
      //     countFitasUsadas++;
      //   }
      //   else if (countFitas == MAXFITAS/2-1){
      //     countFitas++;
      //   }
        
      //   //Escreve os marcados para a proxima fita
      //   for (int j = 0; j < AREA_MAX-1; j++){
      //     fwrite(&alunos[j], sizeof(Aluno), 1, vetorFitas[countFitas]);
      //   }    

      //   alunoTmp.nota = -1;
      //   fwrite(&alunoTmp, sizeof(Aluno), 1, vetorFitas[countFitas]);

      //   break;

      // }
      
      // else if(countMarcados == 0){
      //   //Se não tiver nenhum marcado so escreve os itens na fita atual  
      //   for (int j = 0; j < AREA_MAX-1; j++){
      //     fwrite(&alunos[j], sizeof(Aluno), 1, vetorFitas[countFitas]);
      //   }    

      //   alunoTmp.nota = -1;
      //   fwrite(&alunoTmp, sizeof(Aluno), 1, vetorFitas[countFitas]);

      //   break;
      // }
    // }
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
  
  return 1;
}

void selecSub(int situacao, int quantidade){
    clock_t beginI = clock(); //inicio do calculo de clock de inserção
    resetFitas(0);
    driverSelecSub(quantidade, situacao);
    intercalacao(situacao, quantidade);
    clock_t endI = clock(); //termino do calculo do clock de inserção
    ContadoresIndividuais.tempo = (double)(endI - beginI) / CLOCKS_PER_SEC;  
}