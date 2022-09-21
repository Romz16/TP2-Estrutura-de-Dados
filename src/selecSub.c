#include "headers/selecSub.h"
#include "headers/uteis.h"


// Leitura de 10 registro para a memoria interna (estrutura com um registro e um inteiro marcado ou não)
// Vetor auxiliar de 10 posicoes (ler desse vetor e colocar no vetor de heap) (quando ler todos desse vetor ler mais 10 do arquivo)
// Refaz o heep
// Pega o primeiro item e escreve no Fita (farma de saber qual fita esta) = cont++ quando todos os itens do heap estiverem marcados 


int driverSelecSub(int metodo, int quantidade, int situacao){
    FILE *vetorFitas[20] = {NULL};
    abrirFitas(situacao, vetorFitas);

    FILE *arquivo = abrirArquivo(situacao);

    return 1;
}

