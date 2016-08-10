#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <stdlib.h>
#include "registro.h"

struct Arquivo {
	FILE* arq;
	char * nomeArq;
	int numRegistros;
};

struct Arquivo * CriaArquivo(char * nome);
int InsereArquivo(struct Arquivo * A, struct Produto * R);
int NumRegistros(struct Arquivo * A);
struct Produto * Le(struct Arquivo *A, int p);
void Escreve(struct Arquivo *A, struct Produto * R, int p);

#endif
