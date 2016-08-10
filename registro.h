#ifndef REGISTRO_H
#define REGISTRO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int Chave;
extern Chave auto_incremento;

struct Produto
{
	char nome[100];
	double preco;
	Chave codigo;
	int status; //1 para ativo, 0 para excluído
};

struct Produto * CriaProduto(char nome[100], double preco, Chave codigo);
struct Produto * Remover(struct Produto * P);
void Imprimir(struct Produto * P);
struct Produto * alteraStatus(struct Produto * R);

char * getNome(struct Produto * P);
Chave getChave(struct Produto * P);
double getPreco(struct Produto * P);
int getStatus(struct Produto * P);

struct Produto * setNome(struct Produto * P, char nome[100]);
struct Produto * setPreco(struct Produto * P, double preco);
struct Produto * setStatus(struct Produto * P);

int C_Maior(Chave A, Chave B);
int C_Igual(Chave A, Chave B);
int C_Menor(Chave A, Chave B);

#endif
