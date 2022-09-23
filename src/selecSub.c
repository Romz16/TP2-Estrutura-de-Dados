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
    alunoTmp.marcado = 0;
    //printf("*%ld-%lf-%s-%s-%s*\n", alunoTmp.campoAluno.nInscricao, alunoTmp.campoAluno.nota, alunoTmp.campoAluno.estado, alunoTmp.campoAluno.cidade, alunoTmp.campoAluno.curso);
    insert(alunos, alunoTmp);

  }    

  printf("HEAP\n");
  for (int i = 0; i < MAXINTERNO; i++){
    printf("%.2lf=%i\n", alunos[i].campoAluno.nota, alunos[i].marcado);
  }
  printf("FIM\n");
  

  //escreve o item na fita atual
  int countFitas = 0;
  int countMarcados = 0;
  for (int i = 0; i < quantidade; i++){
    fwrite(&alunos[0], sizeof(aluno), 1, vetorFitas[countFitas]);
    //printf("*%ld-%lf-%s-%s-%s*\n", alunos[0].campoAluno.nInscricao, alunos[0].campoAluno.nota, alunos[0].campoAluno.estado, alunos[0].campoAluno.cidade, alunos[0].campoAluno.curso);
    
    //nao esta nos ultimos 20
    if(i < quantidade-MAXINTERNO){

      fread(&alunoTmp.campoAluno, sizeof(aluno), 1, arquivo);
      printf("ENTRANDO: %.2lf\n", alunoTmp.campoAluno.nota);

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
        for (int i = 0; i < MAXINTERNO; i++)
          alunos[i].marcado = 0; 
      }
      if(countMarcados == MAXINTERNO && countFitas == MAXFITAS/2-1){
        countFitas = 0;
        countMarcados = 0;
        for (int i = 0; i < MAXINTERNO; i++)
          alunos[i].marcado = 0; 
      }
          
    }
      //esta nos últimos 20
      //Escreve a raiz e deleta o raiz e refaz o heep 
    else{
      for (int i = 0; i < MAXINTERNO; i++)
        alunos[i].marcado = 0;                
      
      deleteRoot(alunos, alunos[0]);
    }

    printf("HEAP\n");
    for (int i = 0; i < MAXINTERNO; i++){
      printf("%.2lf=%i\n", alunos[i].campoAluno.nota, alunos[i].marcado);
    }
    printf("FIM\n");

  }   
  
  // for (int i = 0; i < MAXFITAS; i++){
  //   fclose(vetorFitas[i]);
  // }

  printFitas();
  
  return 1;
}
