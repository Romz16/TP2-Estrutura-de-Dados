#ifndef STRUCTS_H
#define STRUCTS_H

#define TRUE 1
#define FALSE 0

#define MAXINTERNO 5
#define MAXFITAS 40

typedef struct{
    long int nInscricao;
    double nota;
    char estado[2];
    char cidade[50];
    char curso[30];
}aluno;

typedef struct{
    long mat;
    float nota;
    char estado[3];
    char cidade[51];
    char curso[31];
}Item;

typedef struct{
    aluno campoAluno;
    int marcado;
}selecSub;

typedef struct TipoBloco{	
	aluno v[10];
	int n;
	int pertence[10];
}TipoBloco;

#endif
