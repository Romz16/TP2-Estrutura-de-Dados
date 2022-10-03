#include "headers/uteis.h"

void ordenaAlunos(Aluno blocos[]){
    int i, j, min_idx;
    for (i = 0; i < MAXFITAS/2-1; i++){
        min_idx = i;
        for (j = i+1; j < MAXFITAS/2; j++)
            if (blocos[j].nota < blocos[min_idx].nota)
                min_idx = j;

        if(min_idx != i){
            Aluno temp = blocos[min_idx];
            blocos[min_idx] = blocos[i];
            blocos[i] = temp;
        }
    }
}

void criaBlocos(int quantidade, int situacao){
    FILE *vetorFitas[MAXFITAS/2] = {NULL};
    if(abrirFitas(vetorFitas) != MAXFITAS)  
        printf("Erro\n"); //return 0;

    FILE *arquivo = abrirArquivo(situacao);

    int quantidaBlocos;
    int blocoFinal;
    int countFitas = 0;

    Aluno alunos[AREA_MAX];

    quantidaBlocos = quantidade / (AREA_MAX);
    blocoFinal = quantidade - (quantidaBlocos * (AREA_MAX));


    for (int i = 0; i < quantidaBlocos; i++){
        fread(alunos, sizeof(Aluno)*(AREA_MAX), 1, arquivo);
        
        ordenaAlunos(alunos);

        fwrite(alunos, sizeof(Aluno)*(AREA_MAX), 1, vetorFitas[countFitas]);
        alunos[0].nota = -1;
        fwrite(&alunos[0], sizeof(Aluno), 1, vetorFitas[countFitas]);
    
        countFitas++;
        if(countFitas == AREA_MAX)
            countFitas = 0;
    }

    fread(alunos, sizeof(Aluno)*blocoFinal, 1, arquivo);
    
    ordenaAlunos(alunos);

    fwrite(alunos, sizeof(Aluno)*(blocoFinal), 1, vetorFitas[countFitas]);
    alunos[0].nota = -1;
    fwrite(&alunos[0], sizeof(Aluno), 1, vetorFitas[countFitas]);

    for (int i = 0; i < AREA_MAX; i++){
        fclose(vetorFitas[i]);
    }    
}

void sortInterno(int situacao, int quantidade){
    resetFitas(0);
    criaBlocos(quantidade+1, situacao);
    intercalacao(situacao, quantidade+1);
}