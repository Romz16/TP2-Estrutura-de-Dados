#include "headers/uteis.h"
#include "headers/intercalacao2F.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void intercalaSelecSub(int situacao, int quantidade){

    FILE *vetorFitas[MAXFITAS] = {NULL};
    if(abrirFitas(vetorFitas) != MAXFITAS)  
        return;

    //FILE *arquivo = abrirArquivo(4);

    TipoBloco2 blocos[AREA_MAX];
    TipoBloco2 tmp;

    int fitaEscritaAtual = 20;

    //Primeiro Bloco com os primerios elementros de cada fita 
    for (int i = 0; i < MAXFITAS/2; i++){
        if(fread(&blocos[i].campoAluno, sizeof(Aluno), 1, vetorFitas[i]) == 1){
            blocos[i].fimFita = 0;
            blocos[i].fitaOrigem = i; 

            if(blocos[i].campoAluno.nota != -1)
                blocos[i].fimBloco = 0;
            else if(blocos[i].campoAluno.nota == -1){            
                blocos[i].fimBloco = 1;
                blocos[i].campoAluno.nota = INT_MAX;
            }
        }
        else{
            blocos[i].fimFita = 1;
            blocos[i].fitaInativa = 1;
            blocos[i].campoAluno.nota = INT_MAX;
        }            
    }

    //Ordenacao do vetor 
    int i, j, min_idx;
    for (i = 0; i < MAXFITAS/2-1; i++){
        min_idx = i;
        for (j = i+1; j < MAXFITAS/2; j++)
        if (blocos[j].campoAluno.nota < blocos[min_idx].campoAluno.nota)
            min_idx = j;

        if(min_idx != i){
            TipoBloco2 temp = blocos[min_idx];
            blocos[min_idx] = blocos[i];
            blocos[i] = temp;
        }
    }

    int contadorParada=0;
    while (1){    
        contadorParada++;
        if(contadorParada == 2001)
            break;

        //Entrar aqui apenas quando 
        if(blocos[0].fimBloco == 1){
            // printf("0--------------%i\n", contadorParada);
            
            //Verifica se chegou no fim das fitas de leitura atual
            int intercaladoSet = 1;
            for (int i = 0; i < MAXFITAS/2; i++){
                if(fread(&blocos[i].campoAluno, sizeof(Aluno), 1, vetorFitas[i]) == 1){
                    blocos[i].fimFita = 0;
                    blocos[i].fitaOrigem = i; 

                    if(blocos[i].campoAluno.nota != -1)
                        blocos[i].fimBloco = 0;
                    else if(blocos[i].campoAluno.nota == -1){            
                        blocos[i].fimBloco = 1;
                        blocos[i].campoAluno.nota = INT_MAX;
                    }
                    intercaladoSet = 0;
                }
                else{
                    blocos[i].fimFita = 1;
                    blocos[i].fitaInativa = 1;
                    blocos[i].campoAluno.nota = INT_MAX;
                }            
            }
            //Se chegou no fim das fitas de leitura atual = intercalação dessas fitas esta completa
            if(intercaladoSet == 1){
                // printf("1--------------%i\n", contadorParada);
                //reseta as fitas que estavam sendo lidas 

                tmp.campoAluno.nota = -1;
                fwrite(&tmp.campoAluno, sizeof(Aluno), 1, vetorFitas[fitaEscritaAtual]);
                
                //Reseta arquivos fitaEscritaAtual pro comeco dos arquivos
                int fitaComeco = -1;
                if(fitaEscritaAtual > MAXFITAS/2 - 1){
                    // printf("2--------------%i\n", contadorParada);
                    fitaComeco = MAXFITAS/2;
                    fitaEscritaAtual = 0;
                    
                    int contadorDeletar = fitaEscritaAtual; 
                    for (int i = 0; i < MAXFITAS/2 && contadorDeletar < MAXFITAS; i++, contadorDeletar++){
                        fclose(vetorFitas[contadorDeletar]);
                    }

                    resetFitas(1);

                    char nomeArquivo[50] = "";
                    size_t idx = fitaEscritaAtual;

                    for (size_t i = 0; i < MAXFITAS/2 && idx < MAXFITAS; i++) {
                        sprintf (nomeArquivo, "data/fitas/fita%zu.dat", i);
                        vetorFitas[idx] = fopen (nomeArquivo, "r+b");
                        if (!vetorFitas[idx]){ 
                            printf("Erro ao Abrir arquivo Fita: %s\n", nomeArquivo);
                            continue;
                        }
                        idx++;
                    }
                }
                else{ 
                    // printf("3--------------%i\n", contadorParada);
                    fitaComeco = 0;
                    fitaEscritaAtual = MAXFITAS/2;
                    
                    int contadorDeletar = fitaEscritaAtual; 
                    for (int i = 0; i < MAXFITAS/2 && contadorDeletar < MAXFITAS; i++, contadorDeletar++){
                        fclose(vetorFitas[contadorDeletar]);
                    }

                    resetFitas(2);

                    char nomeArquivo[50] = "";
                    size_t idx = fitaEscritaAtual;

                    for (size_t i = 0; i < MAXFITAS/2 && idx < MAXFITAS; i++) {
                        sprintf (nomeArquivo, "data/fitas/fita%zu.dat", i);
                        vetorFitas[idx] = fopen (nomeArquivo, "r+b");
                        if (!vetorFitas[idx]){ 
                            printf("Erro ao Abrir arquivo Fita: %s\n", nomeArquivo);
                            continue;
                        }
                        idx++;
                    }
                }
                
                for (int i = 0; i < MAXFITAS/2; i++, fitaComeco++)
                    rewind(vetorFitas[fitaComeco]);
                
                
                
                //Verificar se tem apenas um bloco nas fitas de fitaEscritaAtual = Acabou o processo
                fitaComeco = fitaComeco - MAXFITAS/2;
                int acabou = 0;
                for (int i = 0; i < MAXFITAS/2; i++, fitaComeco++){
                    if(fread(&blocos[i].campoAluno, sizeof(Aluno), 1, vetorFitas[fitaComeco]) == 1){
                        blocos[i].fimFita = 0;
                        blocos[i].fitaOrigem = fitaComeco; 

                        if(blocos[i].campoAluno.nota != -1)
                            blocos[i].fimBloco = 0;
                        else if(blocos[i].campoAluno.nota == -1){            
                            blocos[i].fimBloco = 1;
                            blocos[i].campoAluno.nota = INT_MAX;
                        }
                        acabou++;
                    }
                    else{
                        blocos[i].fimFita = 1;
                        blocos[i].fitaInativa = 1;
                        blocos[i].campoAluno.nota = INT_MAX;
                    }            
                }
                if(acabou == 1)
                    break;

                // if(contadorParada == 1001){
                //     printf("4--------------%i\n", contadorParada);
                //     printf("-%i-\n", fitaEscritaAtual);
                //     for (int i = 0; i < MAXFITAS/2; i++){
                //         printf("%lf\n", blocos[i].campoAluno.nota);
                //     }
                //     printf("4--------------%i\n", contadorParada);
                // }

                //Se tiver mais de um bloco nas fitas de fitaEscritaAtual
                //fitas fitaEscritaAtual se torna as fitas opostas
                //Continua com o processo 

            }
            //Se não chegou ao fim das fitas de leitura atual = falta bloco para intercalar 
            else{
                //Escreve -1 no fim da fitaEscritaAtual
                tmp.campoAluno.nota = -1;
                fwrite(&tmp.campoAluno, sizeof(Aluno), 1, vetorFitas[fitaEscritaAtual]);

                //Fitas de entrada
                if(fitaEscritaAtual > MAXFITAS/2 - 1){
                    if(fitaEscritaAtual == MAXFITAS)
                        fitaEscritaAtual = MAXFITAS/2;
                    else
                        fitaEscritaAtual++;
                }
                //Fitas de Saida
                else{
                    if(fitaEscritaAtual == MAXFITAS/2 - 1)
                        fitaEscritaAtual = 0;
                    else
                        fitaEscritaAtual++;
                }
            }
        }

        //Escreve na fita de saida
        if(blocos[0].fimBloco != 1)
            fwrite(&blocos[0].campoAluno, sizeof(Aluno), 1, vetorFitas[fitaEscritaAtual]);

        // if(contadorParada >= 1001){
        //     printf("Inicio--------------%i\n", contadorParada);
        //     for (int i = 0; i < MAXFITAS/2; i++){
        //         printf("%.2lf\n", blocos[i].campoAluno.nota);
        //     }
        //     printf("Fim--------------%i\n", contadorParada);
        // }
        

        int fitaOrigimTmp = blocos[0].fitaOrigem;
        if(fread(&blocos[0].campoAluno, sizeof(Aluno), 1, vetorFitas[fitaOrigimTmp]) == 1){
            blocos[0].fimFita = 0;

            if(blocos[0].campoAluno.nota != -1)
                blocos[0].fimBloco = 0;
            else if(blocos[0].campoAluno.nota == -1){            
                blocos[0].fimBloco = 1;
                blocos[0].campoAluno.nota = INT_MAX;
            }
        }
        else{
            blocos[0].fimFita = 1;
            blocos[0].fimBloco = 1;
            blocos[0].campoAluno.nota = INT_MAX;
        }
     
        //Ordenacao do vetor 
        for (i = 0; i < MAXFITAS/2-1; i++){
            min_idx = i;
            for (j = i+1; j < MAXFITAS/2; j++)
            if (blocos[j].campoAluno.nota < blocos[min_idx].campoAluno.nota)
                min_idx = j;

            if(min_idx != i){
                TipoBloco2 temp = blocos[min_idx];
                blocos[min_idx] = blocos[i];
                blocos[i] = temp;
            }
        }
        
    }
        

    for (int i = 0; /* i < quantiadeFitas && */ i < MAXFITAS; i++){
        fclose(vetorFitas[i]);
    }

    printFitas();

}

// void quick_sort_int (TipoBloco *a, int n) {
//     int i, j,temp;
//     double p;
//     Aluno t ;
//     //printf("aaa1\n");
//     if (n < 2)
//         return;
//     //printf("aaa2\n");
//     p = a->v[n / 2].nota;
//     for (i = 0, j = n - 1; i++; j--) {
//         while (a->v[i].nota < p)
//             i++;
//         while (p < a->v[j].nota)
//             j--;
//         if (i >= j)
//             break;
//         t = a->v[i];
//         temp = a->pertence[i];
//         a->v[i] = a->v[j];
//         a->v[j] = t;
//         a->pertence[j] = temp;
//     }
//      //printf("aaa3\n");
//     quick_sort_int(a, i);
//     quick_sort_int(a + i, n - i);
// }

// void ordenar_blocos(FILE *arq, FILE **saida, int cont)
// {
	
// 	int i,cont2=0;
// 	TipoBloco bloco;
// 	Aluno reg;
// 	//printf("af");
// //     for (int i = 0; i < 10; i++){
// //         fread(&reg, sizeof(Aluno), 1, arq);
// //         printf("%li\t%lf\t%s\t%s\t%s\n", reg.nInscricao, reg.nota, reg.estado, reg.cidade, reg.curso);
// //     }
// //    fclose(arq);

    
// 	while(arq != EOF)  
// 	{
// 		fread(&reg, sizeof(Aluno), 1, arq);
// 		//printf("Reg: %lf \n",reg.nota);
// 		bloco.v[cont2] = reg;
// 		bloco.n = cont2+1;
// 		//printf("Bloco: %lf \n",bloco.v[cont2].nota);
// 		cont2++;
// 		if(cont2==10)
// 		{
// 			break;
// 		}
// 	}
// 	//printf("ante\n");
// 	quick_sort_int(&bloco,cont2);

// 	//printf("Dep\n");
// 	for(i=0; i<cont2; i++)
// 	{
// 		reg = bloco.v[i];
// 		fwrite(&bloco,sizeof(TipoBloco),1,saida[cont]);
// 		//printf("Bloco: %ld \n",bloco.v[i].mat);
// 	}
// }


// void intercalar_blocos(FILE **fitas,int tam)
// {
// 	int i;
// 	Aluno reg;
// 	TipoBloco bloco;
//     FILE *result = fopen("resultado.txt","w+");
//     printf("aaaaaaaaaaaa");
// 	for(i=0; i<tam; i++)
// 	{
// 		printf("%d\n",i);
// 		fread(&reg,sizeof(Aluno),1,fitas[i]);
// 		bloco.v[i] = reg;
// 		bloco.pertence[i] = i;
// 		printf("Bloco, Matricula: %ld Nota: %.1f\n",bloco.v[i].nInscricao,bloco.v[i].nota);
// 		printf("Pertence: %d\n",bloco.pertence[i]);
// 	}
// 	quick_sort_int(&bloco, 10);
// 	/*printf("\n\nPertence: %d\n",bloco.pertence[0]);
// 	printf("Pertence: %d\n",bloco.pertence[5]);*/

// 	reg = bloco.v[0];
//     fprintf(result,"ga");
// 	fprintf(result,"%li %lf %s %s %s",reg.nInscricao,reg.nota,reg.estado,reg.cidade,reg.curso);
//     fclose(result);
// 	//fwrite(&reg,sizeof(Aluno),1,fitas[11]);
// }

// int main(){
// 	int tam =1000;
//     Aluno AlunoTmp;
//     FILE *arq,*fitas[20];
// 	arq = fopen("data/arquivosBin/Desordenado.dat","rb");
// 	if(arq == NULL) 
// 		{
// 			printf("Arquivo nao pode ser aberto\n");
// 			return 0;
// 		}
        
// //     for (int i = 0; i < tam; i++){
// //         fread(&AlunoTmp, sizeof(Aluno), 1, arq);
// //         printf("%li\t%lf\t%s\t%s\t%s\n", AlunoTmp.nInscricao, AlunoTmp.nota, AlunoTmp.estado, AlunoTmp.cidade, AlunoTmp.curso);
// //     }
// //    fclose(arq);
//     //return 0;
// 	int i,cont=0,resto;
// 	char temp2[2];
			
// 	for(i=0; i<20; i++){
// 	    char temp[11] = "data/fitas/fita_";
// 	    sprintf(temp2,"%d",i+1);
// 	    strcat(temp,temp2);		
// 		strcat(temp,".bin");
				
// 		fitas[i] = fopen(temp,"w+b");
// 		if(fitas[i] == NULL) {
// 			printf("Arquivo nao pode ser aberto\n");
// 			return 0;    }
// 		}
// 	resto = tam%10;
// 	if(resto!=0)
// 		resto=1;
// 	resto += (tam/10);
			
// 	for(i=0; i<resto; i++)
// 		{
// 		ordenar_blocos(arq,fitas,cont);
// 		cont++;
// 		if(cont==10)
// 			cont=0; 
// 		}
			
// 	for(i=0; i<10; i++)
// 		rewind(fitas[i]);
			
// 	intercalar_blocos(fitas,resto);
			
// 	fclose(arq);
// 	fclose(*fitas);
// }