#include "ArquivoIndexado.h"

arquivoIndexado* CriaArquivoIndexado(char *nome)
{
	arquivoIndexado *A = malloc(sizeof(arquivoIndexado));

	A->arquivo = CriaArquivo(nome);
	A->indice = CriaArvoreB();
	
	int i;
	struct Produto * R = malloc(sizeof(struct Produto));
	for (i=0; i<NumRegistros(A->arquivo); i++)
	{
		R = Le(A->arquivo, i);
		if (getStatus(R) == 1)
			Insere(A->indice, getChave(R), i);
	}
	
	return A;
}

int InserirArquivoIndexado(arquivoIndexado *A, struct Produto *R)
{
	if(Insere(A->indice, getChave(R), NumRegistros(A->arquivo)) == 1)
	{
		InsereArquivo(A->arquivo, R);
		return 1;
	}
	return 0;
}


struct Produto * BuscarArquivoIndexado(arquivoIndexado *A, Chave c)
{
	int p = Busca(A->indice, c);
	p--;
	struct Produto * aux = malloc(sizeof(struct Produto));
	
	aux = Le(A->arquivo, p); 
	
	//ta com erro aqui, não está entrando no if pois o aux está retornando NULL
	if (aux != NULL) 
	{
		return aux;
	}
	return NULL;
}

struct Produto * RemoverArquivoIndexado(arquivoIndexado *A, Chave c)
{
	int p = Remove(A->indice, c);
	
	struct Produto * aux = malloc(sizeof(struct Produto));
	
	aux = Le(A->arquivo, p);
	
	setStatus(aux);
	
	Escreve(A->arquivo, aux, p);
	
	return aux;
}

int AlteraArquivoIndexado(arquivoIndexado *A, Chave c, char nome[100], double preco)
{
	int p = Busca(A->indice, c);
	
	struct Produto * aux = malloc(sizeof(struct Produto));
	
	aux = Le(A->arquivo, p);
	
	setNome(aux, nome);
	setPreco(aux, preco);
	
	Escreve(A->arquivo, aux, p);
	
	if (aux != NULL)
		return 1;
	return 0;
}

