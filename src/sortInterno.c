#include "headers/uteis.h"

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

    clock_t beginI = clock(); //inicio do calculo de clock de inserção
    for (int k = 0; k < quantidaBlocos; k++){
        fread(alunoTmp, sizeof(Aluno)*(AREA_MAX), 1, arquivo);
        
        int i, j, min_idx;
        for (i = 0; i < AREA_MAX-1; i++){
            min_idx = i;
            for (j = i+1; j < AREA_MAX; j++)
            {
                ContadoresIndividuais.comparacoes++;
                if (alunoTmp[j].nota < alunoTmp[min_idx].nota)
                    min_idx = j;
            }
            if(min_idx != i){
                Aluno temp = alunoTmp[min_idx];
                alunoTmp[min_idx] = alunoTmp[i];
                alunoTmp[i] = temp;
            }
        }

        alunoTmp2.nota = -1;
        fwrite(alunoTmp, sizeof(Aluno)*(AREA_MAX), 1, vetorFitas[countFitas]);
        fwrite(&alunoTmp2, sizeof(Aluno), 1, vetorFitas[countFitas]);
    
        countFitas++;
        if(countFitas == AREA_MAX)
            countFitas = 0;
    }

    fread(alunoTmp, sizeof(Aluno)*blocoFinal, 1, arquivo);
    
    int i, j, min_idx;
    for (i = 0; i < blocoFinal-1; i++){
        min_idx = i;
        for (j = i+1; j < blocoFinal; j++)
        {
            ContadoresIndividuais.comparacoes++;
            if (alunoTmp[j].nota < alunoTmp[min_idx].nota)
                min_idx = j;
        }

        if(min_idx != i){
            Aluno temp = alunoTmp[min_idx];
            alunoTmp[min_idx] = alunoTmp[i];
            alunoTmp[i] = temp;
        }
    }

    alunoTmp2.nota = -1;
    fwrite(alunoTmp, sizeof(Aluno)*(blocoFinal), 1, vetorFitas[countFitas]);
    fwrite(&alunoTmp2, sizeof(Aluno), 1, vetorFitas[countFitas]);

    for (int i = 0; i < AREA_MAX; i++){
        fclose(vetorFitas[i]);
    }  
    clock_t endI = clock(); //termino do calculo do clock de inserção
    ContadoresIndividuais.tempo = (double)(endI - beginI) / CLOCKS_PER_SEC;  
}

void sortInterno(int situacao, int quantidade){
    resetFitas(0);
    criaBlocos(quantidade, situacao);
    intercalacao(situacao, quantidade);
}