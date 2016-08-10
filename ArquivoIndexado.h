#ifndef ARQUIVO_INDEXADO_H
#define ARQUIVO_INDEXADO_H

#include "registro.h"
#include "arquivo.h"
#include "ArvoreB.h"
#include <stdlib.h>

#define TAM_MAX 1000

typedef struct
{
	struct Arquivo * arquivo;
	struct ArvoreB * indice;
} arquivoIndexado;

arquivoIndexado* CriaArquivoIndexado(char *nome);
int InserirArquivoIndexado(arquivoIndexado *A, struct Produto * R);
struct Produto * BuscarArquivoIndexado(arquivoIndexado *A, Chave c);
struct Produto * RemoverArquivoIndexado(arquivoIndexado *A, Chave c);
int AlteraArquivoIndexado (arquivoIndexado *A, Chave c, char nome[100], double preco);

#endif
