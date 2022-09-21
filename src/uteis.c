#include "headers/uteis.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// long int nInscricao;
// double nota;
// char estado[2];
// char cidade[50];
// char curso[30];

//00170838 034.8 MT CUIABA                                             ADMINISTRACAO                 
//00111954 027.5 MT CUIABA                                             ADMINISTRACAO                 

//Funcao para criar o arquivo ordenada Acendente e desendentemente em memoria principal
void criaArquivo(){
    FILE *arquivoPadrao = fopen("data/arquivoDesordenado.txt", "r");
    if(arquivoPadrao == NULL){
        printf("---------\n");
        return;
    }

    aluno alunos[100];

    for (int i = 0; i < 100; i++){
        fscanf(arquivoPadrao, "%li %lf %2s %50s %30s", &alunos[i].nInscricao, &alunos[i].nota, alunos[i].estado, alunos[i].cidade, alunos[i].curso);
        printf("-%li-%lf-%s-%s-%s-\n", alunos[i].nInscricao, alunos[i].nota, alunos[i].estado, alunos[i].cidade, alunos[i].curso);
    }

    //Ordena crescente
    //Escreve no arquivo arquivoCrescente.txt

    //Ordena decrescente
    //Escreve no arquivo arquivoDecrescente.txt
    
}

//Funcao que retorna vetor de ponteiroas para todas as fitas
FILE **abrirFitas(int situacao){
    FILE *arquivo[20];

    char nomeArquivo[50];
    char numero[10];

    for (int i = 1; i <= 20; i++){
        strcpy(nomeArquivo, "data/fitas/fita");
        sprintf(numero, "%i", i);
        strcat(numero, ".txt");
        strcat(nomeArquivo, numero);

        printf("%s\n", nomeArquivo);

        //a para criar os arquivos 
        if((arquivo[i] = fopen(nomeArquivo, "r+")) == NULL){
            printf("-----\n");
            return NULL;
        }
    }
    return arquivo;
}

//Funcao para abrir o arquivo 
FILE *abrirArquivo(int situacao){
    FILE *arquivo;

    char nomeArquivo[50] = "data/";

    if(situacao == 1)
        strcat(nomeArquivo, "arquivoCrescente.txt");
    else if(situacao == 2)
        strcat(nomeArquivo, "arquivoDecrescente.txt");
    else if(situacao == 3)
        strcat(nomeArquivo, "arquivoDesordenado.txt");

    arquivo = fopen(nomeArquivo, "r");
    if(arquivo == NULL){
        printf("Erro Ao Abrir Arquivo %s\n", nomeArquivo);
        return NULL;
    }

    return arquivo;
}

//Funcao para os testes