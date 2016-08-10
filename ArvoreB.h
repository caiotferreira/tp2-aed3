#ifndef ARVOREB_H
#define ARVOREB_H

#define ORDEM 4

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "registro.h"

struct No
{
	Chave chaves[ORDEM-1];
	int valoresAssociados[ORDEM-1];
	struct No *Filho[ORDEM];
	int numElementos;
};

struct ArvoreB
{
	struct No *raiz;
};

struct ArvoreB* CriaArvoreB();
int Insere(struct ArvoreB *A, Chave chave, int p);
int Remove(struct ArvoreB *A, Chave chave);
int Busca(struct ArvoreB *A, Chave chave);
void Imprime(struct ArvoreB *A);

#endif
