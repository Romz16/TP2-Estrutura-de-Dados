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
    FILE *arquivoTxt = fopen("data/PROVAO.txt", "r");
    FILE *arquivoBin = fopen("data/arquivosBin/Desordenado.dat", "wb");
    if(arquivoTxt == NULL){
        return;
    }

    aluno alunos;
    char tmp[100];

    for (int i = 0; i < 471705; i++){
        fscanf(arquivoTxt, "%ld %lf", &alunos.nInscricao, &alunos.nota);
        //printf("-%ld-%lf-\n", alunos.nInscricao, alunos.nota);

        fgets(tmp, 5, arquivoTxt);
        //printf("-%s-\n", tmp);
        strcpy(alunos.estado, tmp);

        fgets(tmp, 52, arquivoTxt);
        //printf("-%s-\n", tmp);
        strcpy(alunos.cidade, tmp);
        
        fgets(tmp, 30, arquivoTxt);
        //printf("-%s-\n", tmp);
        strcpy(alunos.curso, tmp);

        fwrite(&alunos, sizeof(aluno), 1, arquivoBin);
        
        //printf("%ld-%lf-%s-%s-%s", alunos.nInscricao, alunos.nota, alunos.estado, alunos.cidade, alunos.curso);
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
        sprintf (nomeArquivo, "data/fitas/fita%zu.dat", i);
        fp[idx] = fopen (nomeArquivo, "wb");
        if (!fp[idx]){ 
            printf("Erro ao Abrir arquivo Fita: %s\n", nomeArquivo);
            continue;
        }
        idx++;
    }

    return (int)idx;
}

void printFitas(){
    FILE *fitas[MAXFITAS];
    char nomeArquivo[50] = "";
    size_t idx = 0;
    aluno tmp;

    for (size_t i = 0; i < MAXFITAS; i++) {
        sprintf (nomeArquivo, "data/fitas/fita%zu.dat", i);
        fitas[idx] = fopen (nomeArquivo, "rb");
        if (!fitas[idx]){ 
            printf("Erro ao Abrir arquivo Fita: %s\n", nomeArquivo);
            continue;
        }
        idx++;
    }

    for (int i = 0; i < 40; i++){
        while (fread(&tmp, sizeof(aluno), 1, fitas[i]) == 1){
            printf("FITA: %i\n", i);
            printf("%li-%lf-%s-%s-%s\n", tmp.nInscricao, tmp.nota, tmp.estado, tmp.cidade, tmp.curso);
        }
    }
    for (int i = 0; i < MAXFITAS; i++){
        fclose(fitas[i]);
    }
}

//Funcao para abrir o arquivo 
FILE *abrirArquivo(int situacao){
    FILE *arquivo;

    char nomeArquivo[50] = "data/arquivosBin/";

    if(situacao == 1)
        strcat(nomeArquivo, "Crescente.txt");
    else if(situacao == 2)
        strcat(nomeArquivo, "Decrescente.txt");
    else if(situacao == 3)
        strcat(nomeArquivo, "Desordenado.txt");

    arquivo = fopen(nomeArquivo, "rb");
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