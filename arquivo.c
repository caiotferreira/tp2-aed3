#include "arquivo.h"

struct Arquivo * CriaArquivo(char * nome) 
{
	struct Arquivo * a = malloc(sizeof(struct Arquivo));
	
	a->arq = fopen(nome, "r+b");
	a->nomeArq = malloc(100*sizeof(char));
	strcpy(a->nomeArq, nome);
	if(a->arq == NULL) 
	{
		a->arq = fopen(nome, "w+b");
		a->numRegistros = 0;
		fwrite(&a->numRegistros, sizeof(int), 1,a->arq);
	} else {
		printf("Arquivo aberto!\n");
	}
	fseek(a->arq, 0, SEEK_SET);
	fread(&a->numRegistros, sizeof(int), 1,a->arq);
	fclose(a->arq);
	return a;
}

int InsereArquivo(struct Arquivo * A, struct Produto * R)
{
	A->arq = fopen(A->nomeArq, "r+b");
	fseek(A->arq, 0, SEEK_END);
	
	fwrite(R, sizeof(struct Produto), 1, A->arq);
	
	fseek(A->arq, 0, SEEK_SET);
	fread(&A->numRegistros, sizeof(int), 1, A->arq); 
	A->numRegistros++;
	fseek(A->arq, 0, SEEK_SET);
	fwrite(&A->numRegistros, sizeof(int), 1, A->arq);
	fclose(A->arq);
	
	return A->numRegistros;
}

int NumRegistros(struct Arquivo * A) 
{
	return A->numRegistros;
}

struct Produto * Le(struct Arquivo *A, int p) 
{
	if(A==NULL) return NULL;
	
	if(p<0) return NULL;

	A->arq = fopen(A->nomeArq, "r+b");
	
	struct Produto * R = malloc(sizeof(struct Produto));
	
	fseek(A->arq, sizeof(int) + p*sizeof(struct Produto), SEEK_SET);
	fread(R, sizeof(struct Produto), 1, A->arq);
	
	fclose(A->arq);	
	return R;
}

void Escreve(struct Arquivo *A, struct Produto * R, int p)
{
	A->arq = fopen(A->nomeArq, "r+b");
	
	if(A->arq==NULL) {
		printf("Deu ruim!\n");
		exit(EXIT_FAILURE);
	}
	
	fseek(A->arq, sizeof(int)+p*sizeof(struct Produto), SEEK_SET);
	fwrite(R, sizeof(struct Produto), 1, A->arq);
	
	fclose(A->arq);			
}
