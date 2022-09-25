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
        fwrite(&aluno,sizeof(Aluno),1,ascendente);  
    }

    fclose(aleatorio);
    
    printf("Gerando arquivo ascendente...\n");
          
    //Ordenando o arquivo ascendente. 
    FILE *ArqLi = fopen("data/arquivosBin/Ascendente.dat","r+b");
    FILE *ArqEi = fopen("data/arquivosBin/Ascendente.dat","r+b");
    FILE *ArqLEs = fopen("data/arquivosBin/Ascendente.dat","r+b");
    if(ArqLi==NULL || ArqEi==NULL || ArqLEs==NULL){
        printf("Falha ao abrir arquivos!");
        return;
    }
    QuickSortExterno(&ArqLi,&ArqEi,&ArqLEs,1,MAX_TAM,&contCriacao);
    fclose(ArqLi); fclose(ArqEi);fclose(ArqLEs);

    printf("Gerando arquivo descendente...\n");
   
    fseek(ascendente,0,SEEK_SET);
  
    for(int i=0;i<MAX_TAM;i++){
       fread(&aluno,sizeof(Aluno),1,ascendente);
       fseek(descendente,(MAX_TAM-i)*sizeof(Aluno),SEEK_SET); 
       fwrite(&aluno,sizeof(Aluno),1,descendente);
    }

    
    printf("Arquivos gerados com sucesso!\n");
    
    fclose(ascendente); fclose(descendente);
    
}

void imprimeContadores(Contadores conts){
    printf("Comparacoes: %li\nTransferencias: %li\nTempo Decorrido: %lf segundos\n",conts.comparacoes,conts.transferencias,conts.tempo);
}

void selectionSortExterno(int left,int tam,FILE**leitura,FILE**escrita,Contadores *conts){
    fseek(*leitura,(left*sizeof(Aluno)),SEEK_SET);
    fseek(*escrita,(left*sizeof(Aluno)),SEEK_SET);

    Aluno *vetor = malloc(tam*sizeof(Aluno));
    
    fread(vetor,sizeof(Aluno),tam,*leitura);

    Aluno aux;
    for(int i=0;i<tam;i++){
        int maior = i;
        for(int j=i+1;j<tam;j++){
            conts->comparacoes++;
            if(vetor[j].nota>vetor[maior].nota)
                maior = j;            
        }
        aux = vetor[i];
        vetor[i] = vetor[maior];
        vetor[maior] = aux;
    }

    fwrite(vetor,sizeof(Aluno),tam,*escrita);   

    conts->transferencias = conts->transferencias + 2;
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
    Aluno tmp;

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
        printf("----------FITA: %i----------\n", i);
        while (fread(&tmp, sizeof(Aluno), 1, fitas[i]) == 1){
            printf("%.2lf\n", tmp.nota);
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
        strcat(nomeArquivo, "Aleatorio.dat");
    else if(situacao == 2)
        strcat(nomeArquivo, "Ascendente.dat");
    else if(situacao == 3)
        strcat(nomeArquivo, "Descendente.dat");

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

