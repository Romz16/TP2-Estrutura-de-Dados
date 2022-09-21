#ifndef BLOC_H
#define BLOC_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "structs.h"

typedef struct Aluno
{
    long int nInscricao;
    double nota;
    char estado[2];
    char cidade[50];
    char curso[30];
}aluno;

typedef struct{
    aluno aluno1;
    int fita;
}leituraRegistroFita;

typedef struct{
    aluno aluno1;
    int marcada;
}selcSub;


#endif 
