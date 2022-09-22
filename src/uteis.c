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
    FILE *arquivo = fopen("data/arquivoDesordenado.txt", "r");
    if(arquivo == NULL){
        return;
    }

    aluno alunos[100];

    for (int i = 0; i < 100; i++){
        fscanf(arquivo, "%ld %lf", &alunos[i].nInscricao, &alunos[i].nota);
        fgets(alunos[i].estado, 2, arquivo);
        fgets(alunos[i].cidade, 50, arquivo);
        fgets(alunos[i].curso, 30, arquivo);
        
    }

    //Ordena crescente
    //Escreve no arquivo arquivoCrescente.txt

    //Ordena decrescente
    //Escreve no arquivo arquivoDecrescente.txt
    
}

int abrirFitas(FILE **fp){
    char nomeArquivo[50] = "";
    size_t idx = 0;

    for (size_t i = 0; i < MAXFITAS; i++) {
        sprintf (nomeArquivo, "data/fitas/fita%zu.txt", i);
        fp[idx] = fopen (nomeArquivo, "w");
        if (!fp[idx]){ 
            printf("Erro ao Abrir arquivo Fita: %s\n", nomeArquivo);
            continue;
        }
        idx++;
    }

    return (int)idx;
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

//Geradore Romulo
int geradados()
{
    int sit = 3;
    int tam = 1000;
    int i;
    Item reg;
    FILE *Arq, *Saida;
	
    Saida = fopen ("teste.bin", "w+b");
    if(Saida == NULL)
    {
        return FALSE;
    }
	

    
    switch(sit)
    {
        case 1:
        {
			Arq = fopen("PROVAO_ORDENADO.txt","r");
			if(Arq == NULL)
			{
				return FALSE;
			}
            for(i=0; i<tam; i++)
			{
				fscanf(Arq,"%ld %f %s ",&reg.mat,&reg.nota,reg.estado);
				fgets(reg.cidade,50,Arq);
				fscanf(Arq," %[A-Z a-z]\n",reg.curso);
				
				fwrite(&reg, sizeof(Item), 1, Saida);
			}
            break;
        }
        case 2:
        {
			Arq = fopen("PROVAO_DECRESCENTE.txt","r");
			if(Arq == NULL)
			{
				return FALSE;
			}
            for(i=0; i<tam; i++)
			{
				fscanf(Arq,"%ld %f %s ",&reg.mat,&reg.nota,reg.estado);
				fgets(reg.cidade,50,Arq);
				fscanf(Arq," %[A-Z a-z]\n",reg.curso);
				
				fwrite(&reg, sizeof(Item), 1, Saida);
			}
            break;
        }
        case 3:
        {
			Arq = fopen("PROVAO.txt","r");
			if(Arq == NULL)
			{
				return FALSE;
			}
			for(i=0; i<tam; i++)
			{
				fscanf(Arq,"%ld %f %s ",&reg.mat,&reg.nota,reg.estado);
				fgets(reg.cidade,50,Arq);
				fscanf(Arq,"  %[A-Z a-z]\n",reg.curso);
				
				fwrite(&reg, sizeof(Item), 1, Saida);
			}
            break;
        }
    }
	
    fclose(Saida);
    fclose(Arq);
    return TRUE;
}

//Funcao para os testes