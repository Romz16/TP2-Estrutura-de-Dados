#include "headers/geradados.h"
#include <string.h>

int main()
{
    int sit = 3;
    int tam = 1000;
    int i;
    Item reg;
    FILE *Arq, *Saida;
	
    Saida = fopen ("teste.bin", "w+b");
    if(Saida == NULL)
    {
        return FALSE;
    }
	

    
    switch(sit)
    {
        case 1:
        {
			Arq = fopen("PROVAO_ORDENADO.txt","r");
			if(Arq == NULL)
			{
				return FALSE;
			}
            for(i=0; i<tam; i++)
			{
				fscanf(Arq,"%ld %f %s ",&reg.mat,&reg.nota,reg.estado);
				fgets(reg.cidade,50,Arq);
				fscanf(Arq," %[A-Z a-z]\n",reg.curso);
				
				fwrite(&reg, sizeof(Item), 1, Saida);
			}
            break;
        }
        case 2:
        {
			Arq = fopen("PROVAO_DECRESCENTE.txt","r");
			if(Arq == NULL)
			{
				return FALSE;
			}
            for(i=0; i<tam; i++)
			{
				fscanf(Arq,"%ld %f %s ",&reg.mat,&reg.nota,reg.estado);
				fgets(reg.cidade,50,Arq);
				fscanf(Arq," %[A-Z a-z]\n",reg.curso);
				
				fwrite(&reg, sizeof(Item), 1, Saida);
			}
            break;
        }
        case 3:
        {
			Arq = fopen("PROVAO.txt","r");
			if(Arq == NULL)
			{
				return FALSE;
			}
			for(i=0; i<tam; i++)
			{
				fscanf(Arq,"%ld %f %s ",&reg.mat,&reg.nota,reg.estado);
				fgets(reg.cidade,50,Arq);
				fscanf(Arq,"  %[A-Z a-z]\n",reg.curso);
				
				fwrite(&reg, sizeof(Item), 1, Saida);
			}
            break;
        }
    }
	
    fclose(Saida);
    fclose(Arq);
    return TRUE;
}