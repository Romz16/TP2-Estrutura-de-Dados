#include "headers/uteis.h"

void criaBlocos(int quantidade, int situacao){
    FILE *vetorFitas[MAXFITAS/2] = {NULL};
    if(abrirFitas(vetorFitas) != MAXFITAS)  
        printf("Erro\n"); //return 0;

    FILE *arquivo = abrirArquivo(situacao);

    Aluno alunoTmp;
    Aluno alunoTmp2;
    Aluno alunos[MAX_TAM];

    int tamanho = 0;
    int retorno = 0;
    int countFitas = 0;


    for (int i = 0; i < quantidade; i++){
        retorno = fread(&alunoTmp, sizeof(Aluno), 1, arquivo);
        rewind(arquivo);

        if(i % (MAXFITAS/2) == 0 && retorno == 1){
            fread(&alunoTmp, sizeof(Aluno), 1, arquivo);
            alunos[i] = alunoTmp;

            int k, j, min_idx;
            for (k = 0; k < tamanho-1; k++){
                min_idx = k;
                for (j = k+1; j < tamanho; j++)
                if (alunos[j].nota < alunos[min_idx].nota)
                    min_idx = j;

                if(min_idx != k){
                   Aluno temp = alunos[min_idx];
                    alunos[min_idx] = alunos[k];
                    alunos[k] = temp;
                }
            }

            alunoTmp2.nota = -1;
            fwrite(alunos, sizeof(Aluno)*tamanho, 1, vetorFitas[countFitas]);
            fwrite(&alunoTmp2, sizeof(Aluno), 1, vetorFitas[countFitas]);

            tamanho = 0;

            countFitas++;

            if(countFitas == MAXFITAS/2)
                countFitas = 0;    

        }
        else if(/* i % 20 != 0 ||  */retorno != 1){
            alunos[i] = alunoTmp;

            int k, j, min_idx;
            for (k = 0; k < tamanho-1; k++){
                min_idx = k;
                for (j = k+1; j < tamanho; j++)
                if (alunos[j].nota < alunos[min_idx].nota)
                    min_idx = j;

                if(min_idx != k){
                   Aluno temp = alunos[min_idx];
                    alunos[min_idx] = alunos[k];
                    alunos[k] = temp;
                }
            }

            alunoTmp2.nota = -1;
            fwrite(alunos, sizeof(Aluno)*tamanho, 1, vetorFitas[countFitas]);
            fwrite(&alunoTmp2, sizeof(Aluno), 1, vetorFitas[countFitas]);

        }

        alunos[i] = alunoTmp;
        tamanho++;
    }

    for (int i = 0; i < MAXFITAS/2; i++){
        fclose(vetorFitas[i]);
    }
    
    


}