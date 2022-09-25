#include "headers/uteis.h"

#include <assert.h>
#include <ctype.h>
#include <locale.h>
#include <math.h>
#include <setjmp.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void intercalaSelecSub(int situacao, int quantidade){

    FILE *vetorFitas[MAXFITAS] = {NULL};
    if(abrirFitas(vetorFitas) != MAXFITAS)  
        return;

    //FILE *arquivo = abrirArquivo(4);

    TipoBloco2 blocos[AREA_MAX];

    //https://stackoverflow.com/questions/18941019/simplest-way-to-toggle-a-integer-variable-between-two-values
    int fitaEscritaAtual = 20;

    //Primeiro Bloco com os primerios elementros de cada fita 
    for (int i = 0; i < MAXFITAS/2; i++){
        if(fread(&blocos[i].campoAluno, sizeof(Aluno), 1, vetorFitas[i]) == 1 && blocos[i].campoAluno.nota != -1){
            blocos[i].fimFita = 0;
            blocos[i].fitaOrigem = i; 

            if(blocos[i].campoAluno.nota != -1)
                blocos[i].fimBloco = 0;
            else{            
                blocos[i].fimBloco = 1;
                blocos[i].campoAluno.nota = INT_MAX;
            }
        }
        else{
            blocos[i].fimFita = 1;
            blocos[i].campoAluno.nota = INT_MAX;
        }            
    }


    for (int i = 0; i < quantidade; i++){
    
        //Ordenacao do vetor 
        int i, j, min_idx;
        for (i = 0; i < MAXFITAS/2-1; i++){
            min_idx = i;
            for (j = i+1; j < MAXFITAS/2; j++)
            if (blocos[j].campoAluno.nota < blocos[min_idx].campoAluno.nota)
                min_idx = j;

            if(min_idx != i){
                TipoBloco2 temp = blocos[min_idx];
                blocos[min_idx] = blocos[i];
                blocos[i] = temp;
            }
        }

        //Print vetor
        for (int i = 0; i < MAXFITAS/2; i++){
            printf("%lf\n", blocos[i].campoAluno.nota);
        }
        
        //Escreve na fita de saida
        fwrite(&blocos[0].campoAluno, sizeof(Aluno), 1, vetorFitas[fitaEscritaAtual]);

        //Le o proximo item 
        int fitaOrigimTmp = blocos[0].fitaOrigem;
        if(fread(&blocos[0].campoAluno, sizeof(Aluno), 1, vetorFitas[fitaOrigimTmp]) == 1 && blocos[i].campoAluno.nota != -1){
            blocos[i].fimFita = 0;

            if(blocos[i].campoAluno.nota != -1)
                blocos[i].fimBloco = 0;
            else{            
                blocos[i].fimBloco = 1;
                blocos[i].campoAluno.nota = INT_MAX;
            }
        }
        else{
            blocos[i].fimFita = 1;
            blocos[i].campoAluno.nota = INT_MAX;
        }

        //Verifica se chegou ao fim de todas as fitas
        //Significa que deve-se alternar o set de fitas (entrada vira sadia e saida vira entrada)
        int fimFitas = 0;
        for (int i = 0; i < MAXFITAS/2; i++){
            if(blocos[i].fimFita == 0){
                fimFitas = 1;
            }
        }
        if(fimFitas == 0)
            break;

        int avancarFita = 0;
        for (int i = 0; i < MAXFITAS/2; i++){
            if(blocos[i].fimBloco == 0){
                avancarFita = 1;
            }
        }
        if(avancarFita == 0){

        }
        
    }
        

    for (int i = 0; /* i < quantiadeFitas && */ i < MAXFITAS; i++){
        fclose(vetorFitas[i]);
    }

    printFitas();

}