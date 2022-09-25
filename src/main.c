#include "headers/uteis.h"
/* 
gdb ./ordenacaoDebug.exe
 */
int main(int argc, char const *argv[]) {

    driverSelecSub(100, 3);
    intercalaSelecSub(3, 100);
    return 0;


    printf("\n===== TP1 - Estrutura de Dados II =====\n\n");

    int metodo = -1;      
    int quantidade = -1;  
    int situacao = 1;     
    char opcional[10]; 

    //Validação dos dados.
    if(argc < 3 || argc > 4){
        printf("Quantidade de parametros invalida\n");
        exit(1);
    }  

    metodo = atoi(argv[1]);
    quantidade = atoi(argv[2]);
    situacao = atoi(argv[3]);
    if(argv[4] != NULL){
        strcpy(opcional,argv[4]);
    }

    if(metodo != 1 && metodo !=2 && metodo!=3){
        printf("Metodo invalido!\n");
        exit(1);
    }

    if (argv[4] != NULL) {
        printRegistros(situacao, quantidade);
    }
        
    if(quantidade<0 || quantidade>471705){
        printf("Faixa de falores invalidos!\n");
        exit(1);
    }

    if(situacao != 1 && situacao !=2 && situacao!=3){
        printf("Situacao invalida!\n");
        exit(1);
    }

    //Criando os 3 arquivos binários de teste, caso não existam.
    if(!verificaArquivosBinarios()){
        gerarArquivosBinarios();
    }

    // Menu de acesso às pesquisas
    switch (metodo) {
        case 1:
            break;
            
        case 2:
           
            break;

        case 3:
            quicksort(quantidade, situacao);
            break;

        default:  
            break;
    }
       
    return 0;
}