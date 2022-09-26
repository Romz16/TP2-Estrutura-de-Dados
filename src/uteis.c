#include "headers/uteis.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


short verificaArquivosBinarios(){
    FILE *ascendente = fopen("data/arquivosBin/Ascendente.dat","rb");
    FILE *descendente = fopen("data/arquivosBin/Descendente.dat","rb");
    FILE *aleatorio = fopen("data/arquivosBin/Aleatorio.dat","rb");

    if(ascendente==NULL || descendente==NULL || aleatorio==NULL){
        fclose(ascendente); fclose(descendente); fclose(aleatorio);
        return FALSE;
    }
    fclose(ascendente); fclose(descendente); fclose(aleatorio);
    return TRUE;
}

void gerarArquivosBinarios(){

    Contadores contCriacao;
    contCriacao.comparacoes = 0;
    contCriacao.transferencias = 0;

    FILE *provao = fopen("data/PROVAO.TXT","r");
    if(provao==NULL){
        printf("Nao foi possivel abrir o arquivo texto!\n");
        return;
    }
    
    FILE *ascendente = fopen("data/arquivosBin/Ascendente.dat","w+b");
    FILE *descendente = fopen("data/arquivosBin/Descendente.dat","w+b");
    FILE *aleatorio = fopen("data/arquivosBin/Aleatorio.dat","w+b");

    Aluno aluno;

    char nInscricao[9];
    char nota[6];
    char estado[3];
    char cidade[50];
    char curso[30];
    

    printf("Gerando arquivo aleatorio...\n");
   
    while(!feof(provao)){

        fscanf(provao,"%s %s %s",nInscricao,nota,estado);
        fgets(cidade,50,provao);
        fgets(curso,30,provao);

        aluno.nInscricao = atol(nInscricao);
        aluno.nota = atof(nota);
        strcpy(aluno.estado,estado);
        strcpy(aluno.cidade,cidade);
        strcpy(aluno.curso,curso);

        fwrite(&aluno,sizeof(Aluno),1,aleatorio);
        fwrite(&aluno,sizeof(Aluno),1,descendente); 
    }

    fclose(aleatorio);
    
    printf("Gerando arquivo Descendente...\n");
          
    //Ordenando o arquivo Descendente. 
    FILE *ArqLi = fopen("data/arquivosBin/Descendente.dat","r+b");
    FILE *ArqEi = fopen("data/arquivosBin/Descendente.dat","r+b");
    FILE *ArqLEs = fopen("data/arquivosBin/Descendente.dat","r+b");
    if(ArqLi==NULL || ArqEi==NULL || ArqLEs==NULL){
        printf("Falha ao abrir arquivos!");
        return;
    }
    QuickSortExterno(&ArqLi,&ArqEi,&ArqLEs,1,MAX_TAM-1,&contCriacao);
    fclose(ArqLi); fclose(ArqEi);fclose(ArqLEs);

    printf("Gerando arquivo Ascendente...\n");
   
    fseek(descendente,0,SEEK_SET);
  
    for(int i=0;i<MAX_TAM;i++){
       fread(&aluno,sizeof(Aluno),1,descendente);
       fseek(ascendente,(MAX_TAM-i)*sizeof(Aluno),SEEK_SET); 
       fwrite(&aluno,sizeof(Aluno),1,ascendente);
    }

    
    printf("Arquivos gerados com sucesso!\n");
    
    fclose(ascendente); fclose(descendente);
    
}

void imprimeContadores(Contadores conts){
    printf("Comparacoes: %li\nTransferencias: %li\nTempo Decorrido: %lf segundos\n",conts.comparacoes,conts.transferencias,conts.tempo);
}

int abrirFitas(FILE **fp){
    char nomeArquivo[50] = "";
    size_t idx = 0;

    for (size_t i = 0; i < MAXFITAS; i++) {
        sprintf (nomeArquivo, "data/fitas/fita%zu.dat", i);
        fp[idx] = fopen (nomeArquivo, "r+b");
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
    Aluno tmp;

    for (size_t i = 0; i < MAXFITAS; i++) {
        sprintf (nomeArquivo, "data/fitas/fita%zu.dat", i);
        fitas[idx] = fopen (nomeArquivo, "r+b");
        if (!fitas[idx]){ 
            printf("Erro ao Abrir arquivo Fita: %s\n", nomeArquivo);
            continue;
        }
        idx++;
    }

    for (int i = 0; i < 40; i++){
        if(fread(&tmp, sizeof(Aluno), 1, fitas[i]) == 1){
            printf("----------FITA: %i----------\n", i);
            printf("%.2lf\n", tmp.nota);
        }
        while (fread(&tmp, sizeof(Aluno), 1, fitas[i]) == 1){
            printf("%.2lf\n", tmp.nota);
        }
    }
    for (int i = 0; i < MAXFITAS; i++){
        fclose(fitas[i]);
    }
}

void resetFitas(int modo){
    FILE *fitas[MAXFITAS];
    char nomeArquivo[50] = "";
    size_t idx = 0;

    for (size_t i = 0; i < MAXFITAS; i++) {
        sprintf (nomeArquivo, "data/fitas/fita%zu.dat", i);
        remove(nomeArquivo);
    }

    for (size_t i = 0; i < MAXFITAS; i++) {
        sprintf (nomeArquivo, "data/fitas/fita%zu.dat", i);
        fitas[idx] = fopen (nomeArquivo, "a");
        if (!fitas[idx]){ 
            printf("Erro ao Abrir arquivo Fita: %s\n", nomeArquivo);
            continue;
        }
        idx++;
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
        strcat(nomeArquivo, "Ascendente.dat");
    else if(situacao == 2)
        strcat(nomeArquivo, "Descendente.dat");
    else if(situacao == 3)
        strcat(nomeArquivo, "Aleatorio.dat");
    else if(situacao == 4){
        arquivo = fopen("data/resultado.txt", "w");
        if(arquivo == NULL){
           printf("Falha ao abrir arquivos %s\n", nomeArquivo);
            return NULL;
        }
        return arquivo;
    }

    arquivo = fopen(nomeArquivo, "rb");
    if(arquivo == NULL){
        printf("Falha ao abrir arquivos %s\n", nomeArquivo);
        return NULL;
    }

    return arquivo;
}

void printRegistros(int situacao, int quantidade){
    FILE *arquivo = abrirArquivo(situacao);
    Aluno AlunoTmp;

    for (int i = 0; i < quantidade; i++){
        fread(&AlunoTmp, sizeof(Aluno), 1, arquivo);
        printf("%li\t%lf\t%s\t%s\t%s\n", AlunoTmp.nInscricao, AlunoTmp.nota, AlunoTmp.estado, AlunoTmp.cidade, AlunoTmp.curso);
    }
    fclose(arquivo);
}

