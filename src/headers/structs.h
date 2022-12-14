#ifndef STRUCTS_H
#define STRUCTS_H

#define TRUE 1
#define FALSE 0

#define AREA_MAX 20
#define MAX_TAM 471705
#define MAXFITAS 40

typedef struct Aluno{
    long int nInscricao;
    double nota;
    char estado[2];
    char cidade[50];
    char curso[30];
}Aluno;

typedef struct Pivo{
    Aluno vetor[AREA_MAX];
    int n;
}Pivo;

typedef struct Contadores{
    long int comparacoes;
    long int transferencias;
    double tempo;
}Contadores;

typedef struct TipoBloco{	
	Aluno campoAluno;
	int fitaOrigem;
	int fitaInativa;
	int fimBloco;
	int fimFita;
}TipoBloco;

Contadores ContadoresIndividuais;
Contadores ContadoresAcumulados;
int intercaladoSet;
#endif
