#ifndef STRUCTS_H
#define STRUCTS_H

#define TRUE 1
#define FALSE 0

#define AREA_MAX 20
#define MAX_TAM 20000
#define MAXFITAS 40

typedef struct Aluno{
    long int nInscricao;
    double nota;
    char estado[3];
    char cidade[51];
    char curso[31];
}Aluno;

typedef struct TipoBloco{	
	Aluno v[10];
	int n;
	int pertence[10];
}TipoBloco;

typedef struct Pivo{
    Aluno vetor[AREA_MAX];
    int n;
}Pivo;

typedef struct Contadores{
    long int comparacoes;
    long int transferencias;
    double tempo;
}Contadores;

#endif
