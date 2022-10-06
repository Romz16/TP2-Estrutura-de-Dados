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

    FILE *provao = fopen("data/PROVAO.TXT","r");
    if(provao==NULL){
        printf("Nao foi possivel abrir o arquivo texto!\n");
        return;
    }
    
    FILE *ascendente = fopen("data/arquivosBin/Ascendente.dat","w+b");
    FILE *descendente = fopen("data/arquivosBin/Descendente.dat","w+b");
    FILE *aleatorio = fopen("data/arquivosBin/Aleatorio.dat","w+b");

    Aluno aluno;

    char tmp[100];
    
    printf("Gerando arquivo aleatorio...\n");
   
    int i = 0;
    while(i < MAX_TAM ){

        fscanf(provao, "%ld %lf", &aluno.nInscricao, &aluno.nota);
        
        //Le espaco
        fgets(tmp, 2, provao);
        //le estado
        fgets(aluno.estado, 3, provao);
        //Le espaco
        fgets(tmp, 2, provao);
        //le cidade
        fgets(aluno.cidade, 50, provao);
        //Le espaco
        fgets(tmp, 3, provao);
        //le curso
        fgets(aluno.curso, 30, provao);
        //le quebra de linha
        fgets(tmp, 3, provao);

        fwrite(&aluno,sizeof(Aluno),1,aleatorio);
        //fwrite(&aluno,sizeof(Aluno),1,descendente); 

        i++;
    }

    fclose(aleatorio);

    printf("Gerando arquivo Descendente...\n\n");
          
    quicksort(MAX_TAM, 3);
    FILE *txtOrdenadoDecendente = fopen("data/resultado.txt","r");
    for (int i = 0; i < MAX_TAM; i++){
        fscanf(txtOrdenadoDecendente, "%ld %lf", &aluno.nInscricao, &aluno.nota);
        //printf("-%ld-%lf-", aluno.nInscricao, aluno.nota);
        
        //Le espaco
        fgets(tmp, 2, txtOrdenadoDecendente);
        //le estado
        fgets(aluno.estado, 3, txtOrdenadoDecendente);
        //printf("%s-", aluno.estado);
        //Le espaco
        fgets(tmp, 2, txtOrdenadoDecendente);
        //le cidade
        fgets(aluno.cidade, 50, txtOrdenadoDecendente);
        //printf("%s-", aluno.cidade);
        //Le espaco
        fgets(tmp, 2, txtOrdenadoDecendente);
        //le curso
        fgets(aluno.curso, 30, txtOrdenadoDecendente);
        //printf("%s-\n", aluno.curso);
        //le quebra de linha
        fgets(tmp, 3, txtOrdenadoDecendente);

        fwrite(&aluno,sizeof(Aluno),1,descendente); 

    }
        
    printf("\nGerando arquivo Ascendente...\n");
   
    fseek(descendente,0,SEEK_SET);
  
    for(int i=0;i<MAX_TAM;i++){
        fread(&aluno,sizeof(Aluno),1,descendente);

        fseek(ascendente,(MAX_TAM-i-1)*sizeof(Aluno),SEEK_SET); 
        fwrite(&aluno,sizeof(Aluno),1,ascendente);
    }
    
    printf("Arquivos gerados com sucesso!\n");
    
    fclose(ascendente); fclose(descendente); fclose(provao);
}

void imprimeContadores(Contadores conts){
    // printf("Numero Tranferencia: %li\n", ContadoresAcumulados.transferencias);
    // printf("Numero Comparacoes: %li\n", ContadoresAcumulados.comparacoes);
    // printf("Tempo decorrido: %lf\n\n", ContadoresAcumulados.tempo);

    printf("Numero Tranferencia: %li\n", conts.transferencias);
    printf("Numero Comparacoes: %li\n", conts.comparacoes);
    printf("Tempo decorrido: %lf\n\n", conts.tempo);
}

int abrirFitas(FILE **fp){
    char nomeArquivo[50] = "";
    size_t idx = 0;

    for (size_t i = 0; i < MAXFITAS; i++) {
        sprintf (nomeArquivo, "data/fitas/fita%li.dat", i);
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
        sprintf (nomeArquivo, "data/fitas/fita%li.dat", i);
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
    int idx = 0;
   
    if(modo == -1){
        remove("data/Aleatorio.dat");
        remove("data/Ascendente.dat");
        remove("data/Descendente.dat");
        return;
    }

    if(modo == 0){
        
        for (int i = 0; i < MAXFITAS; i++) {
            sprintf (nomeArquivo, "data/fitas/fita%i.dat", i);
            remove(nomeArquivo);
        }

        for (int i = 0; i < MAXFITAS; i++) {
            sprintf (nomeArquivo, "data/fitas/fita%i.dat", i);
            fitas[idx] = fopen (nomeArquivo, "a");
            if (!fitas[idx]){ 
                printf("Erro ao Abrir arquivo Fita: %s\n", nomeArquivo);
                continue;
            }
            idx++;
        }
        
        for (int i = 0; i < MAXFITAS; i++)
            fclose(fitas[i]);
    }
    if(modo == 1){
        for (int i = 0; i < MAXFITAS/2; i++) {
            sprintf (nomeArquivo, "data/fitas/fita%i.dat", i);
            remove(nomeArquivo);
        }

        for (int i = 0; i < MAXFITAS/2; i++) {
            sprintf (nomeArquivo, "data/fitas/fita%i.dat", i);
            fitas[idx] = fopen (nomeArquivo, "a");
            if (!fitas[idx]){ 
                printf("Erro ao Abrir arquivo Fita: %s\n", nomeArquivo);
                continue;
            }
            idx++;
        }
        
        for (int i = 0; i < MAXFITAS/2; i++)
            fclose(fitas[i]);
    }
    if(modo == 2){
        idx = MAXFITAS/2;
        for (int i = MAXFITAS/2; i < MAXFITAS; i++) {
            sprintf (nomeArquivo, "data/fitas/fita%i.dat", i);
            remove(nomeArquivo);
        }

        for (int i = MAXFITAS/2; i < MAXFITAS; i++) {
            sprintf (nomeArquivo, "data/fitas/fita%i.dat", i);
            fitas[idx] = fopen (nomeArquivo, "a");
            if (!fitas[idx]){ 
                printf("Erro ao Abrir arquivo Fita: %s\n", nomeArquivo);
                continue;
            }
            idx++;
        }
        
        for (int i = MAXFITAS/2; i < MAXFITAS; i++)
            fclose(fitas[i]);
    }
}

void geraArquivoTexto(char nomeArquivo[50]){
    FILE *arquivo = fopen(nomeArquivo, "rb");
    FILE *arquivoTxt = fopen("data/resultado.txt", "w");
    Aluno AlunoTmp;

    while (fread(&AlunoTmp, sizeof(Aluno), 1, arquivo) == 1){
        if(AlunoTmp.nInscricao < 1000 && AlunoTmp.nota != -1)
            fprintf(arquivoTxt, "%li\t\t%.2lf\t%s\t%s\t%s\n", AlunoTmp.nInscricao, AlunoTmp.nota, AlunoTmp.estado, AlunoTmp.cidade, AlunoTmp.curso);
        else if(AlunoTmp.nInscricao > 1000 && AlunoTmp.nota != -1)
            fprintf(arquivoTxt, "%li\t%.2lf\t%s\t%s\t%s\n", AlunoTmp.nInscricao, AlunoTmp.nota, AlunoTmp.estado, AlunoTmp.cidade, AlunoTmp.curso);
    }
    printf("Arquivo de Resultado Gerado: \"resultado.txt\" \n");
    
    fclose(arquivo);
}

FILE *abrirArquivo(int situacao){
    FILE *arquivo;

    char nomeArquivo[50] = "data/arquivosBin/";

    if(situacao == 1)
        strcat(nomeArquivo, "Ascendente.dat");
    else if(situacao == 2)
        strcat(nomeArquivo, "Descendente.dat");
    else if(situacao == 3)
        strcat(nomeArquivo, "Aleatorio.dat");

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
        if(AlunoTmp.nInscricao < 1000)
            printf("%li\t\t%.2lf\t%s\t%s\t%s\n", AlunoTmp.nInscricao, AlunoTmp.nota, AlunoTmp.estado, AlunoTmp.cidade, AlunoTmp.curso);
        else 
            printf("%li\t%.2lf\t%s\t%s\t%s\n", AlunoTmp.nInscricao, AlunoTmp.nota, AlunoTmp.estado, AlunoTmp.cidade, AlunoTmp.curso);
    }
    fclose(arquivo);
}

void gerenciaContadores(int op){
    if(op == 1){
        ContadoresIndividuais.comparacoes = 0;
        ContadoresIndividuais.tempo = 0;
        ContadoresIndividuais.transferencias = 0;

        ContadoresAcumulados.comparacoes = 0;
        ContadoresAcumulados.tempo = 0;
        ContadoresAcumulados.transferencias = 0;
        return;
    }

    else if(op == 2){
        ContadoresAcumulados.comparacoes += ContadoresIndividuais.comparacoes;
        ContadoresAcumulados.tempo += ContadoresIndividuais.tempo;
        ContadoresAcumulados.transferencias += ContadoresIndividuais.transferencias;

        ContadoresIndividuais.comparacoes = 0;
        ContadoresIndividuais.tempo = 0;
        ContadoresIndividuais.transferencias = 0;
        
        return;
    }

}

void funcaoTestesAutomatizados(){
    int metodo = 1, quantidadeRegistros, situacao, quantidadeTestes;

    gerenciaContadores(1);

    while (metodo != -1){       
        scanf("%i", &metodo);
        if(metodo == -1) break;

        scanf("%i", &quantidadeRegistros);
        scanf("%i", &situacao); 
        scanf("%i", &quantidadeTestes);     

        //printRegistros(situacao, quantidadeRegistros);

        if(metodo == 1){
            printf("METODO: %i \nQUANTIDADE: %i \nSITUACAO: %i\n", metodo, quantidadeRegistros, situacao);
            for (int i = 0; i < quantidadeTestes; i++){
                printf("\n-----------------TESTE: %i/%i-----------------\n\n", i+1, quantidadeTestes);
                gerenciaContadores(2);
                sortInterno(situacao, quantidadeRegistros);
            }
            gerenciaContadores(2);
        }
        else if (metodo == 2){
            printf("METODO: %i \nQUANTIDADE: %i \nSITUACAO: %i\n", metodo, quantidadeRegistros, situacao);
            for (int i = 0; i < quantidadeTestes; i++){
                printf("\n-----------------TESTE: %i/%i-----------------\n\n", i+1, quantidadeTestes);
                gerenciaContadores(2);
                selecSub(situacao, quantidadeRegistros);
            }
            gerenciaContadores(2);
        }
        else if (metodo == 3){
            printf("METODO: %i \nQUANTIDADE: %i \nSITUACAO: %i\n", metodo, quantidadeRegistros, situacao);
            for (int i = 0; i < quantidadeTestes; i++){
                printf("\n-----------------TESTE: %i/%i-----------------\n\n", i+1, quantidadeTestes);
                gerenciaContadores(2);
                quicksort(quantidadeRegistros, situacao);
            }
            gerenciaContadores(2);
        }
        
        printf("\n-------------------MEDIA DOS RESULTADOS-------------------\n\n");

        printf("Numero Tranferencia Media: %.3lf\n", (double)ContadoresAcumulados.transferencias/(double)quantidadeTestes);
        printf("Numero Comparacoes Media: %.3lf\n", (double)ContadoresAcumulados.comparacoes/(double)quantidadeTestes);
        printf("Tempo decorrido Media: %lf\n\n", (double)ContadoresAcumulados.tempo/(double)quantidadeTestes);

        gerenciaContadores(1);

        printf("\n----------------------------------------------------------------------------------------------------------------------------\n\n");
    }
}