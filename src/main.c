#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "headers/uteis.h"

//gdb ./ordenacaoDebug.exe

int main(int argc, char const *argv[]) {

    //criaArquivo();
    //printRegistros(1, 200);
    driverSelecSub(1000, 3);
    return 0;

    printf("\n===== TP1 - Estrutura de Dados II =====\n\n");

    int metodo = -1;      
    int quantidade = -1;  
    int situacao = 1;     

    if (argv[1] != NULL) {
        metodo = atoi(argv[1]);

        if (argv[2] != NULL) {
            quantidade = atoi(argv[2]);

            if (argv[3] != NULL && situacao > 0 && situacao < 4) {
                situacao = atoi(argv[3]);

                if (argv[4] != NULL) {
                    printRegistros(situacao, quantidade);
                }
            }
        }
    }

 
    // Menu de acesso às pesquisas
    switch (metodo) {
        case 1:
            break;
        case 2: driverSelecSub(quantidade, situacao);
            break;
        case 3:
            break;

        default:  // opção inválida
            printf("Opcao invalida!\n");
            break;
    }

    return 0;
}