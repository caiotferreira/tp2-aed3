#include "ArvoreB.h"

#define REMOCAO_NORMAL 1
#define REMOCAO_MENOR 0
#define NAO_PROMOVE 0
#define PROMOVE 1
#define CHAVE_JA_EXISTE 2

struct ArvoreB* CriaArvoreB()
{
	struct ArvoreB *A = malloc(sizeof(struct ArvoreB));
	A->raiz = malloc(sizeof(struct No));
	A->raiz->numElementos = 0;

	return A;
}

int BuscaInterno(struct No *N, Chave chave)
{
	if(N==NULL) return -1;
	
	//Percorre as Chave do nó enquanto e for maior que a chave atual
	int i = 0; 
	while(i < N->numElementos && chave > N->valoresAssociados[i])
		i++;

	//Se não encontrou a chave, busca no filho
	if(i == N->numElementos || chave != N->valoresAssociados[i])
		return BuscaInterno(N->Filho[i], chave);

	//Encontrou a chave
	return N->valoresAssociados[i];
}

int Busca(struct ArvoreB *A, Chave chave)
{
	//Árvore não foi criada
	if(A == NULL) return 0;

	return BuscaInterno(A->raiz, chave);
}

void Divide(struct No *N, int *itemPromovido, struct No **filhoDItemPromovido, int * valorAssociadoPromovido)
{
	//Declara vetores para armazenar as Chave e também os Filho da página cheia
	int chaves[ORDEM];
	int valoresAssociados[ORDEM];
	struct No *Filho[ORDEM+1];

	//Copia os elementos para os vetores auxiliares
	int i;
	for(i = 0; i < N->numElementos && (*itemPromovido) > N->valoresAssociados[i]; i++)
	{
		valoresAssociados[i] = N->valoresAssociados[i];
		chaves[i] = N->chaves[i];
		Filho[i] = N->Filho[i];
	}

	Filho[i] = N->Filho[i];
	chaves[i] = *itemPromovido;
	valoresAssociados[i] = *valorAssociadoPromovido;
	Filho[i+1] = *filhoDItemPromovido;
	i++;

	for(; i < ORDEM; i++)
	{
		valoresAssociados[i] = N->valoresAssociados[i-1];
		chaves[i] = N->chaves[i-1];
		Filho[i+1] = N->Filho[i];
	} 

	//Declara uma nova página para fazer o split
	int meio = ORDEM/2;
	*filhoDItemPromovido = malloc(sizeof(struct No));
	(*filhoDItemPromovido)->numElementos = ORDEM-1-meio;

	//Seleciona o elemento do meio da página estourada
	*itemPromovido = chaves[meio];
	*valorAssociadoPromovido = valoresAssociados[meio];

	//Copia a primeira metade para a página da esquerda
	N->numElementos = meio;
	for(i = 0; i < meio; i++)
	{
		N->valoresAssociados[i] = valoresAssociados[i];
		N->chaves[i] = chaves[i];
		N->Filho[i] = Filho[i];
	}
	N->Filho[i] = Filho[i];

	//Coopia a segunda metade para apágina da direita
	int j;
	for(i = meio+1, j = 0; i < ORDEM; i++, j++)
	{
		(*filhoDItemPromovido)->chaves[j] = chaves[i];
		(*filhoDItemPromovido)->valoresAssociados[j] = valoresAssociados[i];
		(*filhoDItemPromovido)->Filho[j] = Filho[i];
	}
	(*filhoDItemPromovido)->Filho[j] = Filho[i];
}

int InsereInterno(struct No *N, Chave chave, int p, int *itemPromovido, struct No **filhoDItemPromovido, int * valorAssociadoPromovido, int *x)
{
	//Se for um nó nulo, insere na página pai
	if(N == NULL)
	{
		*itemPromovido = chave;
		*valorAssociadoPromovido = p;
		*filhoDItemPromovido = NULL;
		*x = 1;
		return PROMOVE;
	}

	//Senão, procura o ponto i onde "chave" deveria estar na página atual
	int i;
	for(i = 0; i < N->numElementos && chave > N->valoresAssociados[i]; i++);

	//Se a chave já estiver na página, retorna
	if(i < N->numElementos && chave == N->valoresAssociados[i] )
	{
		printf("ERRO, item ja existente\n");
		return CHAVE_JA_EXISTE;
	}
	//Senão, manda inserir na página filha adequada
	int retorno = InsereInterno(N->Filho[i], chave, p, itemPromovido, filhoDItemPromovido, valorAssociadoPromovido, x);

	//Se nenhum item for promovido da página filha, retorna
	if(retorno == NAO_PROMOVE || retorno == CHAVE_JA_EXISTE)
		return retorno;

	//Se um item for promovido e houver espaço nesta página
	if(N->numElementos < ORDEM-1)
	{
		int pos = i;
		for(i = N->numElementos; i > pos; i--)
		{
			N->chaves[i] = N->chaves[i-1];
			N->valoresAssociados[i] = N->valoresAssociados[i-1];
			N->Filho[i+1] = N->Filho[i];
		} 
		N->valoresAssociados[pos] = *valorAssociadoPromovido;
		N->Filho[pos+1] = *filhoDItemPromovido;
		N->chaves[pos] = *itemPromovido;
		N->numElementos++;
		return NAO_PROMOVE;
	}
	//Se não houver espaço, faz a divisão de página
	//itemPromovido será o pivô e filhoDItemPromovido será a nova página, o pivô será inserido na página pai
	Divide(N, itemPromovido, filhoDItemPromovido, valorAssociadoPromovido);
	return PROMOVE; 
}

int Insere(struct ArvoreB *A, Chave chave, int p)
{
	//Árvore não foi criada ainda
	if(A == NULL) return 0;

	Chave chavePromovida;
	int valorAssociadoPromovido;
	struct No *filhoDItemPromovido;
	int x;
	if( InsereInterno(A->raiz, chave, p, &chavePromovida, &filhoDItemPromovido, &valorAssociadoPromovido, &x) == PROMOVE)
	{
		struct No *aux = A->raiz;
		A->raiz = malloc(sizeof(struct No));
		A->raiz->valoresAssociados[0] = chavePromovida;
		A->raiz->Filho[0] = aux;
		A->raiz->Filho[1] = filhoDItemPromovido;
		A->raiz->numElementos = 1;
	}
	return x;
}

void ImprimeInterno(struct No *N)
{
	if(N==NULL) return;

	int i;
	for(i = 0; i < N->numElementos; i++)
	{
		printf("%d ", N->valoresAssociados[i]);
	}
	printf("\n");

	for(i = 0; i < N->numElementos; i++)
	{
		ImprimeInterno(N->Filho[i]);
	}
	ImprimeInterno(N->Filho[i]);
}

void Imprime(struct ArvoreB *A)
{
	if(A == NULL) return;
	ImprimeInterno(A->raiz);
}

int Remove_Interno(struct No *r, Chave chave, int tipo, int *chavePromovida, int *valorAssociadoPromovido)
{
	if(r == NULL) return -1;

	int i = 0;
	if(tipo == REMOCAO_NORMAL) 
		while(i < r->numElementos && chave > r->valoresAssociados[i])
			i++;

	int retorno = -1;
	
	if((tipo == REMOCAO_MENOR && r->Filho[i] == NULL) 
		|| (tipo == REMOCAO_NORMAL && i < r->numElementos && chave == r->valoresAssociados[i]))
	{
		//Elemento encontrado
		if(r->Filho[i] == NULL)
		{	
			*chavePromovida = r->chaves[i];
			*valorAssociadoPromovido = r->valoresAssociados[i];
			//Folha, puxar todo mundo uma posição para trás
			for(++i; i < r->numElementos; i++)
			{
				r->chaves[i-1] = r->chaves[i];
				r->valoresAssociados[i-1] = r->valoresAssociados[i];
			}
			r->numElementos--;
			return *valorAssociadoPromovido;
		}

		//remove pos i
		retorno = r->valoresAssociados[i];
		Remove_Interno(r->Filho[i+1], chave, REMOCAO_MENOR, chavePromovida, valorAssociadoPromovido);
		r->chaves[i] = *chavePromovida;
		r->valoresAssociados[i] = *valorAssociadoPromovido;
		i++;
	}
	else
	{
		//Elemento não encontrado
		retorno = Remove_Interno(r->Filho[i], chave, tipo, chavePromovida, valorAssociadoPromovido);
	}

	//Verifica se o filho onde ocorreu a remoção têm o número mínimo de elementos
	if(r->Filho[i] && r->Filho[i]->numElementos < (ORDEM-1)/2)
	{
		if(i > 0 && r->Filho[i-1]->numElementos > (ORDEM-1)/2)
		{
			//Recebe um item da esquerda
			int j;
			struct No *f = r->Filho[i];
			struct No *g = r->Filho[i-1];
			f->Filho[f->numElementos+1] = f->Filho[f->numElementos];
			for(j = f->numElementos; j > 0; j--)
			{
				f->chaves[j] = f->chaves[j-1];
				f->valoresAssociados[j] = f->valoresAssociados[j-1];
				f->Filho[j] = f->Filho[j-1];
			}
			f->chaves[0] = r->chaves[i-1];
			f->valoresAssociados[0] = r->valoresAssociados[i-1];
			f->Filho[0] = g->Filho[g->numElementos];
			(f->numElementos)++;
			r->chaves[i-1] = g->chaves[g->numElementos-1];
			r->valoresAssociados[i-1] = g->valoresAssociados[g->numElementos-1];
			(g->numElementos)--; 
		}
		else if(i < r->numElementos && r->Filho[i+1]->numElementos > (ORDEM-1)/2)
		{
			//Recebe um item da direita
			int j;
			struct No *f = r->Filho[i];
			struct No *g = r->Filho[i+1];
	
			f->chaves[f->numElementos] = r->chaves[i];
			f->valoresAssociados[f->numElementos] = r->valoresAssociados[i];
			f->Filho[f->numElementos+1] = g->Filho[0];
			(f->numElementos)++;
			r->chaves[i] = g->chaves[0];
			r->valoresAssociados[i] = g->valoresAssociados[0];
			for(j = 1; j < g->numElementos; j++)
			{
				g->chaves[j-1] = g->chaves[j];
				g->valoresAssociados[j-1] = g->valoresAssociados[j];
				g->Filho[j-1] = g->Filho[j]; 
			}
			g->Filho[i-1] = g->Filho[i];
			(g->numElementos)--; 
		}
		else
		{
			//Merge
			int j;

			struct No *f, *g;

			if(i>0)
			{
				f = r->Filho[i];
				g = r->Filho[i-1];
				i--;
			}
			else
			{
				g = r->Filho[i];
				f = r->Filho[i+1];
			}
			g->chaves[g->numElementos] = r->chaves[i];
			g->valoresAssociados[g->numElementos] = r->valoresAssociados[i];
			(g->numElementos)++;
			for(j = 0; j < f->numElementos; j++)
			{
				g->chaves[g->numElementos] = f->chaves[j];
				g->valoresAssociados[g->numElementos] = f->valoresAssociados[j];
				g->Filho[g->numElementos] = f->Filho[j];
				(g->numElementos)++;
			}
			g->Filho[g->numElementos] = f->Filho[j];
			free(f);
			for(; i < r->numElementos-1; i++)
			{
				r->chaves[i] = r->chaves[i+1];
				r->valoresAssociados[i] = r->valoresAssociados[i+1];
				r->Filho[i+1] = r->Filho[i+2];
			}
			r->numElementos--;
		}
	}
	return retorno;
}

int Remove(struct ArvoreB *A, Chave chave)
{
	if(A == NULL) return -1;
	Chave chavePromovida;
	int valorAssociadoPromovido;

	int retorno = Remove_Interno(A->raiz, chave, REMOCAO_NORMAL, &chavePromovida, &valorAssociadoPromovido);

	if(A->raiz->numElementos == 0)
	{
		struct No *r = A->raiz;
		A->raiz = A->raiz->Filho[0];
		free(r);
	}
	return retorno;
}



