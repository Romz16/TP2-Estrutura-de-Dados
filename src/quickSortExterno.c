#include "headers/quickSortExterno.h"


//invoca o metodo quicksort a partir de uma quantidade e sitaução. 
void quicksort(int quantidade, int situacao){
    
    FILE* copia;
    FILE* arquivo;
    Aluno bloco[15];

    FILE* ArqLEs;
    FILE* ArqLi;
    FILE* ArqEi;

    Contadores conts;
    conts.comparacoes = 0;
    conts.transferencias = 0;

    clock_t inicio,fim;

    char name[50];
    //Dada uma situação, cria-se uma cópia do arquivo a ser ordenado in situ, afim de não alterar o arquivo original. 
    //Abre o arquivo cópia referenciado por ponteiros de leitura e escrita usados pelo quicksort
    switch(situacao){
        case 1:{
            strcpy(name, "data/Ascendente_by_quicksort.dat");

            copia = fopen(name,"wb");
            arquivo = fopen("data/arquivosBin/Ascendente.dat","rb");

            for (int i = 0; i < quantidade; i++){
                fread(bloco,sizeof(Aluno),1,arquivo);
                fwrite(bloco,sizeof(Aluno),1,copia);
            }

            ArqLEs = fopen("data/Ascendente_by_quicksort.dat","r+b");
            ArqLi = fopen("data/Ascendente_by_quicksort.dat","r+b");
            ArqEi = fopen("data/Ascendente_by_quicksort.dat","r+b");
            break;
        }


        case 2:{
            strcpy(name, "data/Descendente_by_quicksort.dat");

            copia = fopen(name,"wb");
            arquivo = fopen("data/arquivosBin/Descendente.dat","rb");

            for (int i = 0; i < quantidade; i++){
                fread(bloco,sizeof(Aluno),1,arquivo);
                fwrite(bloco,sizeof(Aluno),1,copia);
            }

            ArqLEs = fopen("data/Descendente_by_quicksort.dat","r+b");
            ArqLi = fopen("data/Descendente_by_quicksort.dat","r+b");
            ArqEi = fopen("data/Descendente_by_quicksort.dat","r+b");
            break;
        }


        case 3:{
            strcpy(name, "data/Aleatorio_by_quicksort.dat");

            copia = fopen(name,"wb");
            arquivo = fopen("data/arquivosBin/Aleatorio.dat","rb");
            
            for (int i = 0; i < quantidade; i++){
                fread(bloco,sizeof(Aluno),1,arquivo);
                fwrite(bloco,sizeof(Aluno),1,copia);
            }

            ArqLEs = fopen("data/Aleatorio_by_quicksort.dat","r+b");
            ArqLi = fopen("data/Aleatorio_by_quicksort.dat","r+b");
            ArqEi = fopen("data/Aleatorio_by_quicksort.dat","r+b");
            break;
        }
        default:
            break;            
    }

    fclose(copia);
    fclose(arquivo);


    //Verifica se os ponteiros estão referenciando o arquivo a ser ordenado
    if(ArqLi == NULL || ArqEi == NULL || ArqLEs == NULL){
        printf("Nao foi possivel abrir o arquivo copia a ser ordenado!\n");
        return;
    }

    inicio = clock();
    //Invocação da função quicksortExterno iterativo.
    QuickSortExterno(&ArqLi,&ArqEi,&ArqLEs,1,quantidade,&conts);
    fclose(ArqEi);
    fclose(ArqLi);
    fclose(ArqLEs);   
    fim = clock();
    conts.tempo = (double)(fim - inicio)/CLOCKS_PER_SEC;
  
    imprimeContadores(conts);
    geraArquivoTexto(name);
    remove(name);

    ContadoresIndividuais.comparacoes = conts.comparacoes;
    ContadoresIndividuais.transferencias = conts.transferencias;
    ContadoresIndividuais.tempo = conts.tempo;
}

//Inicializa um pivo vazio
void inicializaPivo(Pivo* p){
    p->n = 0;
}

//Insere um item no pivo de forma ordenada. Metodo semelhante ao usado pelo inserction sort. 
void inserePivo(Pivo* pivo,Aluno aluno,Contadores* conts){
    int i = pivo->n;
    while(i>0) {
        conts->comparacoes++;
        if(aluno.nota <= pivo->vetor[i-1].nota)
            break;
        
        pivo->vetor[i] = pivo->vetor[i-1];
        i--;
    }  
    pivo->vetor[i] = aluno;
    pivo->n++;
}

//Retira o menor item do pivo(aluno com menor nota)
void retiraMenorPivo(Pivo* pivo,Aluno* aluno){
    *aluno = pivo->vetor[(pivo->n) - 1];
     pivo->n--;
}

//Retira o maior item do pivo(aluno com maior nota)
void retiraMaiorPivo(Pivo* pivo,Aluno* aluno){
    *aluno = pivo->vetor[0];
     pivo->n--;
     for(int i=0;i<pivo->n;i++)
        pivo->vetor[i] = pivo->vetor[i+1];

}

void QuickSortExterno(FILE **ArqLi, FILE **ArqEi,FILE **ArqLEs,int esq,int dir,Contadores *conts){

    int i,j;
    Pivo pivo;

   if(dir - esq < 1){
        return;
   }
    //Inicializa um pivo vazio;
    inicializaPivo(&pivo);
    //realiza a partição.
    Particao(ArqLi,ArqEi,ArqLEs,pivo,esq,dir,&i,&j,conts);
    //Verifica o menor subarquivo para ordena-lo primeiro
    if(i - esq < dir - j){
        QuickSortExterno(ArqLi,ArqEi,ArqLEs,esq,i,conts);
        QuickSortExterno(ArqLi,ArqEi,ArqLEs,j,dir,conts);
    }
    else{
        QuickSortExterno(ArqLi,ArqEi,ArqLEs,j,dir,conts);
        QuickSortExterno(ArqLi,ArqEi,ArqLEs,esq,i,conts);
    }    
    
}

//Divide um arquivo em dois subarquivos, um de itens menores que o limite inderior do pivo e outro com itens maiores que o limite superior do pivo.
void Particao(FILE**ArqLi,FILE**ArqEi,FILE**ArqLEs,Pivo pivo,int esq,int dir,int*i,int*j,Contadores*conts){
    int Ls = dir,Es = dir,Li = esq,Ei = esq;
    int Linf = INT_MAX,Lsup = INT_MIN;
    
    short OndeLer = TRUE;
    Aluno leitura,escrita;
    //Posicionando os ponteiros de leitura no início e no fim do subarquivo 
    fseek(*ArqLi,(Li-1)*sizeof(Aluno),SEEK_SET);
    fseek(*ArqEi,(Ei-1)*sizeof(Aluno),SEEK_SET);
    //Iniciando os valores de i e j ,respectivamente, na posição anterior e após o subarquivo
    *i = esq-1; *j = dir+1;
    //Realiza leituras alternadas enquanto os ponteiros de leitura apostos não se cruzarem
    while(Ls>=Li){
        //Verifica se há mais de um espaço dentro do pivo 
        if(pivo.n < AREA_MAX - 1){
            //Verifica se o turno de leitura é na direita ou esquerda
            conts->transferencias++;      
            if(OndeLer)
                leSup(ArqLEs,&leitura,&Ls,&OndeLer);
            else
                leInf(ArqLi,&leitura,&Li,&OndeLer);
            //Insere o item no pivo de forma ordenada. 
            inserePivo(&pivo,leitura,conts);
            continue;
        }
        //Se os ponteiros de escrita e leitura estiverem na mesma posição, a alternancia é rompida.
        //Caso não seja, o ulimo item do pivo é inserido normalmente
        conts->transferencias++;      
        if(Ls==Es)
            leSup(ArqLEs,&leitura,&Ls,&OndeLer);
        else if(Li == Ei)
            leInf(ArqLi,&leitura,&Li,&OndeLer);
        else if(OndeLer)
            leSup(ArqLEs,&leitura,&Ls,&OndeLer);
        else
            leInf(ArqLi,&leitura,&Li,&OndeLer);
        
        //Verifica se o ultimo aluno lido tem a nota menor que o limite superior ou maior que o limite inferior, afim de determinar em qual lado o mesmo deve ser escrito
        conts->comparacoes = conts->comparacoes + 2;
        if(leitura.nota < Lsup){
            *j = Es;  
            conts->transferencias++;         
            escreveMax(ArqLEs,leitura,&Es);
            continue;
        }
        if(leitura.nota > Linf){
            *i = Ei;
            conts->transferencias++;      
            escreveMin(ArqEi,leitura,&Ei);
            continue;
        }
        inserePivo(&pivo,leitura,conts);
        //Verifica qual das partições tem um tamanho maior(Teve menos escritas)
        
        //Retira o maior item do pivo(aluno com maior nota)
        if(Ei - esq < dir - Es){
            retiraMaiorPivo(&pivo,&escrita);
            conts->transferencias++;      
            escreveMin(ArqEi,escrita,&Ei);
            Linf = escrita.nota;
        }
        //Retira o menor item do pivo(aluno com menor nota)
        else{
            retiraMenorPivo(&pivo,&escrita);
            conts->transferencias++;      
            escreveMax(ArqLEs,escrita,&Es);
            Lsup = escrita.nota;
        }
    }

    while(Ei<=Es){
        conts->transferencias++;      
        retiraMaiorPivo(&pivo,&escrita);
        escreveMin(ArqEi,escrita,&Ei);
    }
}

//Realiza uma leitura no subarquivo a direita, Retrocedendo o ponteiro  para esquerda.
void leSup(FILE**ArqLEs,Aluno* leitura,int *Ls,short *OndeLer){
    fseek(*ArqLEs,(*Ls-1)*sizeof(Aluno),SEEK_SET);
    fread(leitura,sizeof(Aluno),1,*ArqLEs);
    (*Ls)--;
    *OndeLer = FALSE;
}

//Realiza uma leitura no subarquivo a esquerda. 
void leInf(FILE**ArqLi,Aluno* leitura,int *Li,short *OndeLer){
    fread(leitura,sizeof(Aluno),1,*ArqLi);
    (*Li)++;
    *OndeLer = TRUE;
}

//Realiza uma escrita no subarquivo a esquerda.
void escreveMin(FILE**ArqEi,Aluno escrita,int *Ei){
    fwrite(&escrita,sizeof(Aluno),1,*ArqEi);
    (*Ei)++;
}

//Realiza uma escrita no subarquivo a direita, retrocedendo o ponteiro  para esquerda.
void escreveMax(FILE**ArqLEs,Aluno escrita,int *Es){
    fseek(*ArqLEs,(*Es-1)*sizeof(Aluno),SEEK_SET);
    fwrite(&escrita,sizeof(Aluno),1,*ArqLEs);
    (*Es)--;
}
