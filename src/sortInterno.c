#include "headers/uteis.h"


void insertDeBlocos(TipoBloco **blocos){
    int i, j, min_idx;
    for (i = 0; i < MAXFITAS/2-1; i++){
        min_idx = i;
        for (j = i+1; j < MAXFITAS/2; j++)
            if (blocos[j]->campoAluno.nota < blocos[min_idx]->campoAluno.nota)
                min_idx = j;

        if(min_idx != i){
            TipoBloco temp = *blocos[min_idx];
            *blocos[min_idx] = *blocos[i];
            *blocos[i] = temp;
        }
    }
}



void InsertionReg(Aluno **alunoTmp,int Tam){
     int i, j, min_idx;
        for (i = 0; i < Tam-1; i++){
            min_idx = i;
            for (j = i+1; j < Tam; j++)
                if (alunoTmp[j]->nota < alunoTmp[min_idx]->nota)
                    min_idx = j;

            if(min_idx != i){
                Aluno temp = *alunoTmp[min_idx];
                *alunoTmp[min_idx] = *alunoTmp[i];
                *alunoTmp[i] = temp;
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

    Aluno alunoTmp[AREA_MAX];
    Aluno alunoTmp2;

    quantidaBlocos = quantidade / (AREA_MAX);
    blocoFinal = quantidade - (quantidaBlocos * (AREA_MAX));


    for (int k = 0; k < quantidaBlocos; k++){
        fread(alunoTmp, sizeof(Aluno)*(AREA_MAX), 1, arquivo);
        
        //Colocar em uma função separada
        InsertionReg(&alunoTmp,AREA_MAX);

        alunoTmp2.nota = -1;
        fwrite(alunoTmp, sizeof(Aluno)*(AREA_MAX), 1, vetorFitas[countFitas]);
        fwrite(&alunoTmp2, sizeof(Aluno), 1, vetorFitas[countFitas]);
    
        countFitas++;
        if(countFitas == AREA_MAX)
            countFitas = 0;
    }

    fread(alunoTmp, sizeof(Aluno)*blocoFinal, 1, arquivo);
    
    //Colocar em uma função separada
     InsertionReg(&alunoTmp,blocoFinal);


    alunoTmp2.nota = -1;
    fwrite(alunoTmp, sizeof(Aluno)*(blocoFinal), 1, vetorFitas[countFitas]);
    fwrite(&alunoTmp2, sizeof(Aluno), 1, vetorFitas[countFitas]);

    for (int i = 0; i < AREA_MAX; i++){
        fclose(vetorFitas[i]);
    }    
}


void sortInterno(int situacao, int quantidade){
    resetFitas(0);
    criaBlocos(quantidade, situacao);
    intercalacao(situacao, quantidade);
}