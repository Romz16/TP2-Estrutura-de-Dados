#include "headers/uteis.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


short verificaArquivosBinarios(){
    FILE *ascendente = fopen("data/Ascendente.dat","rb");
    FILE *descendente = fopen("data/Descendente.dat","rb");
    FILE *aleatorio = fopen("data/Aleatorio.dat","rb");

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
    
    FILE *ascendente = fopen("data/Ascendente.dat","w+b");
    FILE *descendente = fopen("data/Descendente.dat","w+b");
    FILE *aleatorio = fopen("data/Aleatorio.dat","w+b");

    Aluno aluno;
    char leitura[100];

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
    FILE *ArqLi = fopen("data/Ascendente.dat","r+b");
    FILE *ArqEi = fopen("data/Ascendente.dat","r+b");
    FILE *ArqLEs = fopen("data/Ascendente.dat","r+b");
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




void criaArquivo(){
    FILE *arquivoTxt = fopen("data/PROVAO.txt", "r");
    FILE *arquivoBinDesordenado = fopen("data/arquivosBin/Desordenado.dat", "wb");
    if(arquivoTxt == NULL){
        return;
    }

    Aluno AlunoTmp;
    Aluno Alunos[200];
    char tmp[100];

    for (int i = 0; i < 471705; i++){
        fscanf(arquivoTxt, "%ld %lf", &AlunoTmp.nInscricao, &AlunoTmp.nota);

        //Le espaco
        fgets(tmp, 2, arquivoTxt);
        //le estado
        fgets(AlunoTmp.estado, 3, arquivoTxt);
        //Le espaco
        fgets(tmp, 2, arquivoTxt);
        //le cidade
        fgets(AlunoTmp.cidade, 50, arquivoTxt);
        //Le espaco
        fgets(tmp, 3, arquivoTxt);
        //le curso
        fgets(AlunoTmp.curso, 30, arquivoTxt);
        //le quebra de linha
        fgets(tmp, 3, arquivoTxt);
        fwrite(&AlunoTmp, sizeof(Aluno), 1, arquivoBinDesordenado);

        if(i < 200)
            Alunos[i] = AlunoTmp;
        
        //printf("%ld-%lf-%s-%s-%s-\n", AlunoTmp.nInscricao, AlunoTmp.nota, AlunoTmp.estado, AlunoTmp.cidade, AlunoTmp.curso);
    }

    //Ordena crescente
    //Escreve no arquivo arquivoCrescente.txt
    int i, j, min_idx;
    for (i = 0; i < 200-1; i++){
        min_idx = i;
        for (j = i+1; j < 200; j++)
          if (Alunos[j].nota < Alunos[min_idx].nota)
            min_idx = j;
 
        if(min_idx != i){
            Aluno temp = Alunos[min_idx];
            Alunos[min_idx] = Alunos[i];
            Alunos[i] = temp;
        }
    }
    FILE *arquivoBinCrescente = fopen("data/arquivosBin/Crescente.dat", "wb");
    fwrite(Alunos, sizeof(Aluno)*200, 1, arquivoBinCrescente);

    //Ordena decrescente
    //Escreve no arquivo arquivoDecrescente.txt
    
    fclose(arquivoBinDesordenado);
    fclose(arquivoBinCrescente);
    fclose(arquivoTxt);    
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
        strcat(nomeArquivo, "Crescente.dat");
    else if(situacao == 2)
        strcat(nomeArquivo, "Decrescente.dat");
    else if(situacao == 3)
        strcat(nomeArquivo, "Desordenado.dat");

    arquivo = fopen(nomeArquivo, "rb");
    if(arquivo == NULL){
        printf("Erro Ao Abrir Arquivo %s\n", nomeArquivo);
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

//Geradore Romulo
int geradados(){
    int sit = 3;
    int tam = 1000;
    int i;
    Aluno reg;
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
				fscanf(Arq,"%ld %lf %s ",&reg.nInscricao,&reg.nota,reg.estado);
				fgets(reg.cidade,50,Arq);
				fscanf(Arq," %[A-Z a-z]\n",reg.curso);
				
				fwrite(&reg, sizeof(Aluno), 1, Saida);
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
				fscanf(Arq,"%ld %lf %s ",&reg.nInscricao,&reg.nota,reg.estado);
				fgets(reg.cidade,50,Arq);
				fscanf(Arq," %[A-Z a-z]\n",reg.curso);
				
				fwrite(&reg, sizeof(Aluno), 1, Saida);
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
				fscanf(Arq,"%ld %lf %s ",&reg.nInscricao,&reg.nota,reg.estado);
				fgets(reg.cidade,50,Arq);
				fscanf(Arq,"  %[A-Z a-z]\n",reg.curso);
				
				fwrite(&reg, sizeof(Aluno), 1, Saida);
			}
            break;
        }
    }
	
    fclose(Saida);
    fclose(Arq);
    return TRUE;
}

//Funcao para os testes