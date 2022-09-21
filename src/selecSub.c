#include "headers/selecSub.h"
#include "headers/uteis.h"


// Leitura de 10 registro para a memoria interna (estrutura com um registro e um inteiro marcado ou não)
// Vetor auxiliar de 10 posicoes (ler desse vetor e colocar no vetor de heap) (quando ler todos desse vetor ler mais 10 do arquivo)
// Refaz o heep
// Pega o primeiro item e escreve no Fita (farma de saber qual fita esta) = cont++ quando todos os itens do heap estiverem marcados 

// long int nInscricao;
// double nota;
// char estado[2];
// char cidade[50];
// char curso[30];

//00170838 034.8 MT CUIABA                                             ADMINISTRACAO                 
//00111954 027.5 MT CUIABA                                             ADMINISTRACAO  

int driverSelecSub(int metodo, int quantidade, int situacao){
    FILE *vetorFitas[20] = {NULL};
    abrirFitas(situacao, vetorFitas);

    FILE *arquivo = abrirArquivo(situacao);

    aluno alunos[100];

    for (int i = 0; i < quantidade; i++){
        fscanf(arquivo, "%ld %lf", &alunos[i].nInscricao, &alunos[i].nota);
        fgets(alunos[i].estado, 2, arquivo);
        fgets(alunos[i].cidade, 50, arquivo);
        fgets(alunos[i].curso, 30, arquivo);
        
        printf("-%li-%lf-%s-%s-%s-\n", alunos[i].nInscricao, alunos[i].nota, alunos[i].estado, alunos[i].cidade, alunos[i].curso);
    }
    

    return 1;
}

