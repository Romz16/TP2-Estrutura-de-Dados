#include "headers/uteis.h"
#include "headers/intercalacao2F.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int leItemFita(int i, int j, TipoBloco *blocos, FILE *vetorFitas){
    int retorno = 1;

    ContadoresIndividuais.transferencias++;
    if(fread(&blocos->campoAluno, sizeof(Aluno), 1, vetorFitas) == 1){
            blocos->fimFita = 0;
            blocos->fitaOrigem = j; 

            if(blocos->campoAluno.nota != -1)
                blocos->fimBloco = 0;
            else if(blocos->campoAluno.nota == -1){            
                blocos->fimBloco = 1;
                blocos->campoAluno.nota = INT_MAX;
            }
            retorno = 0;
        }
        else{
            blocos->fimFita = 1;
            blocos->campoAluno.nota = INT_MAX;
        } 

    return retorno;
    
}

void ordenaBloco(TipoBloco blocos[]){
    int i, j, min_idx;
    for (i = 0; i < MAXFITAS/2-1; i++){
        min_idx = i;
        for (j = i+1; j < MAXFITAS/2; j++){
            ContadoresIndividuais.comparacoes++;
            if (blocos[j].campoAluno.nota < blocos[min_idx].campoAluno.nota)
                min_idx = j;
            }

        if(min_idx != i){
            TipoBloco temp = blocos[min_idx];
            blocos[min_idx] = blocos[i];
            blocos[i] = temp;
        }
    }
}

void deletaFitasEntradaAtual(int fitaEscritaAtual, int fita, FILE *vetorFitas[MAXFITAS]){

    int contadorDeletar = fitaEscritaAtual; 
    for (int i = 0; i < MAXFITAS/2 && contadorDeletar < MAXFITAS; i++, contadorDeletar++){
        fclose(vetorFitas[contadorDeletar]);
    }

    resetFitas(fita);

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

void intercalacao(int situacao, int quantidade){

    FILE *vetorFitas[MAXFITAS] = {NULL};
    if(abrirFitas(vetorFitas) != MAXFITAS)  
        return;

    TipoBloco blocos[AREA_MAX];
    //TipoBloco tmp;

    int fitaEscritaAtual = 20;

    for (int i = 0; i < MAXFITAS/2; i++)
        leItemFita(i, i, &blocos[i], vetorFitas[i]);
    
    ordenaBloco(blocos);

    while (1){    

        //Entrar aqui apenas quando 
        if(blocos[0].fimBloco == 1){
            
            //Escreve -1 para determinar o fim de um bloco
            blocos[0].campoAluno.nota = -1;
            ContadoresIndividuais.transferencias++;
            fwrite(&blocos[0], sizeof(Aluno), 1, vetorFitas[fitaEscritaAtual]);
            blocos[0].campoAluno.nota = INT_MAX;
            
            //Verifica se chegou no fim das fitas de leitura atual
            //Funcao Ler primeiros elementos de cada fita
            int intercaladoSet = 1;
            for (int i = 0; i < MAXFITAS/2; i++)
                if(leItemFita(i, i, &blocos[i], vetorFitas[i]) == 0)
                    intercaladoSet = 0;

            //Se chegou no fim das fitas de leitura atual = intercalação dessas fitas esta completa
            if(intercaladoSet == 1){

                //tmp.campoAluno.nota = -1;
                //fwrite(&tmp.campoAluno, sizeof(Aluno), 1, vetorFitas[fitaEscritaAtual]);
                
                //Reseta arquivos fitaEscritaAtual pro comeco dos arquivos
                int fitaComeco = -1;
                if(fitaEscritaAtual > MAXFITAS/2 - 1){
                    fitaComeco = MAXFITAS/2;
                    fitaEscritaAtual = 0;
                    deletaFitasEntradaAtual(fitaEscritaAtual, 1, vetorFitas);
                }
                else{ 
                    fitaComeco = 0;
                    fitaEscritaAtual = MAXFITAS/2;
                    deletaFitasEntradaAtual(fitaEscritaAtual, 2, vetorFitas);
                }
                
                for (int i = 0; i < MAXFITAS/2; i++, fitaComeco++)
                    rewind(vetorFitas[fitaComeco]);
                
                //Verificar se tem apenas um bloco nas fitas de fitaEscritaAtual = Acabou o processo
                //Funcao Ler primeiros elementos de cada fita
                fitaComeco = fitaComeco - MAXFITAS/2;

                int acabou = 0;
                
                for (int i = 0; i < MAXFITAS/2; i++, fitaComeco++)
                    if(leItemFita(i, fitaComeco, &blocos[i], vetorFitas[fitaComeco]) == 0)
                        acabou++;

                if(acabou == 1)
                    break;

            }
            
            //Se não chegou ao fim das fitas de leitura atual = falta bloco para intercalar 
            else{
                //Escreve -1 no fim da fitaEscritaAtual
                //Marca fim do bloco na fita de escrita

                //tmp.campoAluno.nota = -1;
                //fwrite(&tmp.campoAluno, sizeof(Aluno), 1, vetorFitas[fitaEscritaAtual]);

                //Fitas de entrada
                if(fitaEscritaAtual > MAXFITAS/2 - 1){
                    if(fitaEscritaAtual == MAXFITAS-1)
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

        //Escreve na fita de saida = Inicializa com 20 
        if(blocos[0].fimBloco != 1){
            ContadoresIndividuais.transferencias++;
            fwrite(&blocos[0].campoAluno, sizeof(Aluno), 1, vetorFitas[fitaEscritaAtual]);
        }

        //Função leTipoAluno
        leItemFita(0, blocos[0].fitaOrigem, &blocos[0], vetorFitas[blocos[0].fitaOrigem]);
     
        ordenaBloco(blocos);
        
    }
        
    if(fitaEscritaAtual == MAXFITAS/2)
        fitaEscritaAtual = 0;
    else if(fitaEscritaAtual == 0)
        fitaEscritaAtual = MAXFITAS/2;

    Aluno alunoTmp;
    char nome[] = "data/by_intercalacao.dat";
    FILE* arquivoSaida = fopen(nome, "wb");

    while(fread(&alunoTmp, sizeof(Aluno), 1, vetorFitas[fitaEscritaAtual]) == 1){
        fwrite(&alunoTmp, sizeof(Aluno), 1, arquivoSaida);
    }

    fclose(arquivoSaida);

    for (int i = 0; i < MAXFITAS; i++){
        fclose(vetorFitas[i]);
    }    

    geraArquivoTexto(nome);

}
