#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct{
    long int nInscricao;
    double nota;
    char estado[2];
    char cidade[50];
    char curso[30];
}aluno;

typedef struct TipoBloco{	
	aluno v[10];
	int n;
	int pertence[10];
}TipoBloco;

#endif
