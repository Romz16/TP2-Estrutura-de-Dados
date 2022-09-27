#include "headers/uteis.h"

void quick_sort_int (TipoBloco *a, int n) {
    int i, j,temp;
    double p;
    Aluno t ;
    //printf("aaa1\n");
    if (n < 2)
        return;
    //printf("aaa2\n");
    p = a->v[n / 2].nota;
    for (i = 0, j = n - 1; i++; j--) {
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
     //printf("aaa3\n");
    quick_sort_int(a, i);
    quick_sort_int(a + i, n - i);
}

void ordenar_blocos(FILE *arq, FILE **saida, int cont)
{
	
	int i,cont2=0;
	TipoBloco bloco;
	Aluno reg;
	//printf("af");
//     for (int i = 0; i < 10; i++){
//         fread(&reg, sizeof(Aluno), 1, arq);
//         printf("%li\t%lf\t%s\t%s\t%s\n", reg.nInscricao, reg.nota, reg.estado, reg.cidade, reg.curso);
//     }
//    fclose(arq);

    
	while(fread(&reg, sizeof(Aluno), 1, arq) == 1)  
	{
		// printf("Reg: %.2lf \n",reg.nota);
		bloco.v[cont2] = reg;
		bloco.n = cont2+1;
		//printf("Bloco: %lf \n",bloco.v[cont2].nota);
		cont2++;
		if(cont2==AREA_MAX/2)
		{
			break;
		}
	}
	//printf("ante\n");
	quick_sort_int(&bloco,cont2);
    // printf("Contador: Count2: ----------%i\n", cont2);

	//printf("Dep\n");
	for(i=0; i<cont2; i++)
	{
		reg = bloco.v[i];
		fwrite(bloco.v,sizeof(Aluno)*AREA_MAX/2,1,saida[cont]);
		// fwrite(&reg,sizeof(Aluno),1,saida[cont]);
		// printf("Bloco: %.2lf \n",bloco.v[i].nota);
	}
    Aluno alunoTmp;
    alunoTmp.nota = -1;
    fwrite(&alunoTmp, sizeof(Aluno), 1, saida[cont]);

}

int criaBlocosInterno(int  quantidade,int situacao){
    //Aluno AlunoTmp;
    FILE *arq;
    FILE *fitas[MAXFITAS];
    if(abrirFitas(fitas) != MAXFITAS){  
        return 0;
    }
    
	arq = abrirArquivo(situacao);
        
//     for (int i = 0; i < quantidade; i++){
//         fread(&AlunoTmp, sizeof(Aluno), 1, arq);
//         printf("%li\t%lf\t%s\t%s\t%s\n", AlunoTmp.nInscricao, AlunoTmp.nota, AlunoTmp.estado, AlunoTmp.cidade, AlunoTmp.curso);
//     }
//    fclose(arq);
//     return 0;
	int i,cont=0,resto;
	//char temp2[2];
			
	// for(i=0; i<20; i++){
	//     char temp[20] = "data/fitas/fita";
	//     sprintf(temp2,"%d",i+1);
	//     strcat(temp,temp2);		
	// 	strcat(temp,".dat");
				
	// 	fitas[i] = fopen(temp,"w+b");
	// 	if(fitas[i] == NULL) {
	// 		printf("Arquivo nao pode ser aberto\n");
	// 		return 0;    }
	// 	}
	resto = quantidade %(MAXFITAS/2);
	if(resto!=0)
		resto=1;
	resto += (quantidade/(MAXFITAS/2));

	for(i=0; i<resto; i++)
		{
		ordenar_blocos(arq,fitas,cont);
		cont++;
		if(cont==(MAXFITAS/2))
			cont=0; 
		}
			
	for(i=0; i<(MAXFITAS/2); i++)
		rewind(fitas[i]);
			
	//intercalar_blocos(fitas,resto);
			
	fclose(arq);

    for (int i = 0; i < MAXFITAS/2; i++){
        fclose(fitas[i]);
    }

    return 1;
}