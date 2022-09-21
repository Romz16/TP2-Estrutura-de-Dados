#include "headers/intercalacao2F.h"
#include "headers/uteis.h"
#include "headers/sortInterno.h"
#include <string.h>

void quick_sort_int (TipoBloco *a, int n) {
    int i, j,temp;
    double p;
    aluno t ;
    if (n < 2)
        return;
    p = a->v[n / 2].nota;
    for (i = 0, j = n - 1;; i++, j--) {
        while (a->v[i].nota < p)
            i++;
        while (p < a->v[j].nota)
            j--;
        if (i >= j)
            break;
        t = a->v[i];
        temp = a->pertence[i];
        a->v[i] = a->v[j];
        a->v[j] = t;
        a->pertence[j] = temp;
    }
    quick_sort_int(a, i);
    quick_sort_int(a + i, n - i);
}

void ordenar_blocos(FILE *arq, FILE **saida, int cont)
{
	
	int i,cont2=0;
	TipoBloco bloco;
	aluno reg;
	//printf("af");
	while(fread(&reg,sizeof(aluno),1,arq))
	{
		
		//printf("Reg: %ld \n",reg.mat);
		bloco.v[cont2] = reg;
		bloco.n = cont2+1;
		//printf("Bloco: %ld \n",bloco.v[cont2].mat);
		cont2++;
		if(cont2==10)
		{
			break;
		}
	}
	printf("ante\n");
	quick_sort_int(&bloco,cont2);

	printf("Dep\n");
	for(i=0; i<cont2; i++)
	{
		reg = bloco.v[i];
		fwrite(&bloco,sizeof(TipoBloco),1,saida[cont]);
		//printf("Bloco: %ld \n",bloco.v[i].mat);
	}
}

int main(){
	int tam =1000;
       
    FILE *arq,*fitas[20];
	arq = fopen("teste.bin","rb");
	if(arq == NULL) 
		{
			printf("Arquivo nao pode ser aberto\n");
			return 0;
		}
	int i,cont=0,resto;
	char temp2[2];
			
	for(i=0; i<20; i++){
	    char temp[11] = "Fita_";
	    sprintf(temp2,"%d",i+1);
	    strcat(temp,temp2);		
		strcat(temp,".bin");
				
		fitas[i] = fopen(temp,"w+b");
		if(fitas[i] == NULL) {
			printf("Arquivo nao pode ser aberto\n");
			return 0;    }
		}
	resto = tam%10;
	if(resto!=0)
		resto=1;
	resto += (tam/10);
			
	for(i=0; i<resto; i++)
		{
		ordenar_blocos(arq,fitas,cont);
		cont++;
		if(cont==10)
			cont=0;
		}
			
	for(i=0; i<10; i++)
		rewind(fitas[i]);
			
	intercalar_blocos(fitas,resto);
			
	fclose(arq);
	close(*fitas);}