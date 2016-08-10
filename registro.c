#include "registro.h"

struct Produto * CriaProduto(char nome[100], double preco, Chave codigo)
{
	struct Produto * P = malloc(sizeof(struct Produto));
	int i = 0;
	for(i=0;i<100;i++){
		P->nome[i] = nome[i];
	}
	P->preco = preco;
	P->codigo = codigo;
	P->status = 1;
	return P;
}

struct Produto * Remover(struct Produto * P)
{
	if(P->status==1)
		setStatus(P);
	return P;
}

char * getNome(struct Produto * P)
{
	if(P->status==1)
	{
		return P->nome;
	}else{
		return NULL;
	}
	
}

Chave getChave(struct Produto * P)
{
	if(P->status==1)
	{
		return P->codigo;
	}else{
		return 0;
	}
}

double getPreco(struct Produto * P)
{
	if(P->status==1)
	{
		return P->preco;
	}else{
		return 0;
	}
}

int getStatus(struct Produto * P)
{
	return P->status;
}

void Imprimir(struct Produto * P)
{
	if (P == NULL) return;
	printf("Produto: %d\nNome: %s\nPreco: %f\nStatus: %d\n\n", P->codigo, P->nome, P->preco, P->status);
}

struct Produto * setNome (struct Produto * R, char nome[100]) {
	strcpy(R->nome, nome);
	
	return R;
}

struct Produto * setPreco (struct Produto * R, double preco) {
	R->preco = preco;
	
	return R;
}

struct Produto * setStatus (struct Produto * R) {
	R->status = 0;
	
	return R;
}

int C_Maior(Chave A, Chave B)
{
	return A > B;
}

int C_Igual(Chave A, Chave B)
{
	return A == B;
}

int C_Menor(Chave A, Chave B)
{
	return A < B;
}
