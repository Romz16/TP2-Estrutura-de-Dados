#include "headers/uteis.h"


void intercalaSelecSub(int situacao, int quantidade){

    FILE *vetorFitas[MAXFITAS] = {NULL};
    if(abrirFitas(vetorFitas) != MAXFITAS)  
        return;

    //FILE *arquivo = abrirArquivo(4);

    TipoBloco2 blocos[AREA_MAX];

    //https://stackoverflow.com/questions/18941019/simplest-way-to-toggle-a-integer-variable-between-two-values
    int quantiadeFitas = 0;
    int fitaEscritaAtual = 20;

    // while (1){
        for (int i = 0; i < MAXFITAS/2; i++){
            if(fread(&blocos[i].campoAluno, sizeof(Aluno), 1, vetorFitas[i]) == 1 && blocos[i].campoAluno.nota != -1){
                blocos[i].fimFita = 0;
                blocos[i].fitaOrigem = i; 
                quantiadeFitas++;

                if(blocos[i].campoAluno.nota != -1)
                    blocos[i].fimBloco = 0;
                else            
                    blocos[i].fimBloco = 1;
            }
            else{
                blocos[i].fimFita = 1;
            }            
        }
        //Ordenacao do vetor de 
        int i, j, min_idx;
        for (i = 0; i < quantiadeFitas-1; i++){
            min_idx = i;
            for (j = i+1; j < quantiadeFitas; j++)
            if (blocos[j].campoAluno.nota < blocos[min_idx].campoAluno.nota)
                min_idx = j;

            if(min_idx != i){
            TipoBloco2 temp = blocos[min_idx];
            blocos[min_idx] = blocos[i];
            blocos[i] = temp;
            }
        }

        for (int i = 0; i < quantiadeFitas; i++){
            printf("%lf\n", blocos[i].campoAluno.nota);
        }

        fwrite(&blocos[0].campoAluno, sizeof(Aluno), 1, vetorFitas[fitaEscritaAtual]);

        if(fread(&blocos[0].campoAluno, sizeof(Aluno), 1, vetorFitas[blocos[0].fitaOrigem]) == 1 && blocos[i].campoAluno.nota != -1){
            blocos[i].fimBloco = 1;
            blocos[i].fitaOrigem = i; 
        }
        else{
            blocos[i].fimBloco = 0;
            quantiadeFitas--;
        }

        if(quantiadeFitas == 0)
        //Fim de um bloco

        fitaEscritaAtual++;
        if(fitaEscritaAtual == MAXFITAS){
            fitaEscritaAtual = 0;
        } 

        
    // }

    for (int i = 0; i < quantiadeFitas && i < MAXFITAS; i++){
        fclose(vetorFitas[i]);
    }

    printFitas();

}