#ifndef STRUCTS_H
#define STRUCTS_H

#define TRUE 1
#define FALSE 0

#define MAXINTERNO 20
#define MAXFITAS 40

typedef struct{
    long int nInscricao;
    double nota;
    char estado[3];
    char cidade[51];
    char curso[31];
}aluno;

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
