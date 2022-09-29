#include "headers/uteis.h"
#include "headers/intercalacao2F.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void intercalacao(int situacao, int quantidade){

    FILE *vetorFitas[MAXFITAS] = {NULL};
    if(abrirFitas(vetorFitas) != MAXFITAS)  
        return;

    TipoBloco blocos[AREA_MAX];
    TipoBloco tmp;
    Contadores conts;

    int fitaEscritaAtual = 20;

    //Primeiro Bloco com os primerios elementros de cada fita 
    for (int i = 0; i < MAXFITAS/2; i++){
        if(fread(&blocos[i].campoAluno, sizeof(Aluno), 1, vetorFitas[i]) == 1){
            blocos[i].fimFita = 0;
            blocos[i].fitaOrigem = i; 

            if(blocos[i].campoAluno.nota != -1)
                blocos[i].fimBloco = 0;
            else if(blocos[i].campoAluno.nota == -1){            
                blocos[i].fimBloco = 1;
                blocos[i].campoAluno.nota = INT_MAX;
            }
        }
        else{
            blocos[i].fimFita = 1;
            blocos[i].fitaInativa = 1;
            blocos[i].campoAluno.nota = INT_MAX;
        }            
    }

    //Ordenacao do vetor 
    int i, j, min_idx;
    for (i = 0; i < MAXFITAS/2-1; i++){
        min_idx = i;
        for (j = i+1; j < MAXFITAS/2; j++)
            if (blocos[j].campoAluno.nota < blocos[min_idx].campoAluno.nota)
                min_idx = j;

        if(min_idx != i){
            TipoBloco temp = blocos[min_idx];
            blocos[min_idx] = blocos[i];
            blocos[i] = temp;
        }
    }

    while (1){    

        //Entrar aqui apenas quando 
        if(blocos[0].fimBloco == 1){
            
            //Verifica se chegou no fim das fitas de leitura atual
            int intercaladoSet = 1;
            for (int i = 0; i < MAXFITAS/2; i++){
                if(fread(&blocos[i].campoAluno, sizeof(Aluno), 1, vetorFitas[i]) == 1){
                    blocos[i].fimFita = 0;
                    blocos[i].fitaOrigem = i; 

                    if(blocos[i].campoAluno.nota != -1)
                        blocos[i].fimBloco = 0;
                    else if(blocos[i].campoAluno.nota == -1){            
                        blocos[i].fimBloco = 1;
                        blocos[i].campoAluno.nota = INT_MAX;
                    }
                    intercaladoSet = 0;
                }
                else{
                    blocos[i].fimFita = 1;
                    blocos[i].fitaInativa = 1;
                    blocos[i].campoAluno.nota = INT_MAX;
                }            
            }
            //Se chegou no fim das fitas de leitura atual = intercalação dessas fitas esta completa
            if(intercaladoSet == 1){
                //reseta as fitas que estavam sendo lidas 

                tmp.campoAluno.nota = -1;
                fwrite(&tmp.campoAluno, sizeof(Aluno), 1, vetorFitas[fitaEscritaAtual]);
                
                //Reseta arquivos fitaEscritaAtual pro comeco dos arquivos
                int fitaComeco = -1;
                if(fitaEscritaAtual > MAXFITAS/2 - 1){
                    fitaComeco = MAXFITAS/2;
                    fitaEscritaAtual = 0;
                    
                    int contadorDeletar = fitaEscritaAtual; 
                    for (int i = 0; i < MAXFITAS/2 && contadorDeletar < MAXFITAS; i++, contadorDeletar++){
                        fclose(vetorFitas[contadorDeletar]);
                    }

                    resetFitas(1);

                    char nomeArquivo[50] = "";
                    size_t idx = fitaEscritaAtual;

                    for (size_t i = 0; i < MAXFITAS/2 && idx < MAXFITAS; i++) {
                        sprintf (nomeArquivo, "data/fitas/fita%li.dat", i);
                        vetorFitas[idx] = fopen (nomeArquivo, "r+b");
                        if (!vetorFitas[idx]){ 
                            printf("Erro ao Abrir arquivo Fita: %s\n", nomeArquivo);
                            continue;
                        }
                        idx++;
                    }
                }
                else{ 
                    fitaComeco = 0;
                    fitaEscritaAtual = MAXFITAS/2;
                    
                    int contadorDeletar = fitaEscritaAtual; 
                    for (int i = 0; i < MAXFITAS/2 && contadorDeletar < MAXFITAS; i++, contadorDeletar++){
                        fclose(vetorFitas[contadorDeletar]);
                    }

                    resetFitas(2);

                    char nomeArquivo[50] = "";
                    size_t idx = fitaEscritaAtual;

                    for (size_t i = 0; i < MAXFITAS/2 && idx < MAXFITAS; i++) {
                        sprintf (nomeArquivo, "data/fitas/fita%li.dat", i);
                        vetorFitas[idx] = fopen (nomeArquivo, "r+b");
                        if (!vetorFitas[idx]){ 
                            printf("Erro ao Abrir arquivo Fita: %s\n", nomeArquivo);
                            continue;
                        }
                        idx++;
                    }
                }
                
                for (int i = 0; i < MAXFITAS/2; i++, fitaComeco++)
                    rewind(vetorFitas[fitaComeco]);
                
                
                
                //Verificar se tem apenas um bloco nas fitas de fitaEscritaAtual = Acabou o processo
                fitaComeco = fitaComeco - MAXFITAS/2;
                int acabou = 0;
                for (int i = 0; i < MAXFITAS/2; i++, fitaComeco++){
                    if(fread(&blocos[i].campoAluno, sizeof(Aluno), 1, vetorFitas[fitaComeco]) == 1){
                        blocos[i].fimFita = 0;
                        blocos[i].fitaOrigem = fitaComeco; 

                        if(blocos[i].campoAluno.nota != -1)
                            blocos[i].fimBloco = 0;
                        else if(blocos[i].campoAluno.nota == -1){            
                            blocos[i].fimBloco = 1;
                            blocos[i].campoAluno.nota = INT_MAX;
                        }
                        acabou++;
                    }
                    else{
                        blocos[i].fimFita = 1;
                        blocos[i].fitaInativa = 1;
                        blocos[i].campoAluno.nota = INT_MAX;
                    }            
                }
                if(acabou == 1)
                    break;

            }
            //Se não chegou ao fim das fitas de leitura atual = falta bloco para intercalar 
            else{
                //Escreve -1 no fim da fitaEscritaAtual
                tmp.campoAluno.nota = -1;
                fwrite(&tmp.campoAluno, sizeof(Aluno), 1, vetorFitas[fitaEscritaAtual]);

                //Fitas de entrada
                if(fitaEscritaAtual > MAXFITAS/2 - 1){
                    if(fitaEscritaAtual == MAXFITAS)
                        fitaEscritaAtual = MAXFITAS/2;
                    else
                        fitaEscritaAtual++;
                }
                //Fitas de Saida
                else{
                    if(fitaEscritaAtual == MAXFITAS/2 - 1)
                        fitaEscritaAtual = 0;
                    else
                        fitaEscritaAtual++;
                }
            }
        }

        //Escreve na fita de saida
        if(blocos[0].fimBloco != 1)
            fwrite(&blocos[0].campoAluno, sizeof(Aluno), 1, vetorFitas[fitaEscritaAtual]);
        

        int fitaOrigimTmp = blocos[0].fitaOrigem;
        if(fread(&blocos[0].campoAluno, sizeof(Aluno), 1, vetorFitas[fitaOrigimTmp]) == 1){
            blocos[0].fimFita = 0;

            if(blocos[0].campoAluno.nota != -1)
                blocos[0].fimBloco = 0;
            else if(blocos[0].campoAluno.nota == -1){            
                blocos[0].fimBloco = 1;
                blocos[0].campoAluno.nota = INT_MAX;
            }
        }
        else{
            blocos[0].fimFita = 1;
            blocos[0].fimBloco = 1;
            blocos[0].campoAluno.nota = INT_MAX;
        }
     
        //Ordenacao do vetor 
        for (i = 0; i < MAXFITAS/2-1; i++){
            min_idx = i;
            for (j = i+1; j < MAXFITAS/2; j++)
                if (blocos[j].campoAluno.nota < blocos[min_idx].campoAluno.nota)
                    min_idx = j;

            if(min_idx != i){
                TipoBloco temp = blocos[min_idx];
                blocos[min_idx] = blocos[i];
                blocos[i] = temp;
            }
        }
        
    }
        
    if(fitaEscritaAtual == MAXFITAS/2)
        fitaEscritaAtual = 0;
    else if(fitaEscritaAtual == 0)
        fitaEscritaAtual = MAXFITAS/2;

    Aluno alunoTmp;
    char nome[] = "data/by_intercalacao.dat";
    FILE* arquivoSaida = fopen(nome, "wb");

    while(fread(&alunoTmp, sizeof(Aluno), 1, vetorFitas[fitaEscritaAtual]) == 1){
        printf("%.2lf\n", alunoTmp.nota);
        fwrite(&alunoTmp, sizeof(Aluno), 1, arquivoSaida);
    }

    fclose(arquivoSaida);

    for (int i = 0; i < MAXFITAS; i++){
        fclose(vetorFitas[i]);
    }    

    geraArquivoTexto(nome);
    imprimeContadores(conts);

}
