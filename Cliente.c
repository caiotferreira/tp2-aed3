#include <stdio.h>
#include <stdlib.h>

#include "registro.h"
#include "ArquivoIndexado.h"

int main (int argc, char** argv) {
	printf("Olá! \n");
	
	printf("Digite o nome do arquivo a ser criado: ");
	char nomeArquivo[100];
	scanf("%s", nomeArquivo);
	arquivoIndexado * A = CriaArquivoIndexado(nomeArquivo);
	
	Chave auto_incremento = 1;
	
	struct Produto * P;
	char nome[100];
	double preco;
	Chave chave;
	int op = 0;
	
	while (op != 5) {
		printf("\nEscolha uma das opções a seguir para prosseguir no programa: \n");
		
		printf("1 - Inserir novo registro \n2 - Remover um registro\n3 - Buscar um registro\n4 - Alterar um registro\n5 - Finalizar\n");
		scanf("%d", &op);
	
		switch (op)
		{
			case 1:
				//insere novo registro
				printf("Digite o nome do produto:\n");	
				scanf("%s", nome);
				printf("Digite o preco do produto:\n");	
				scanf("%lf", &preco);
				P = CriaProduto(nome, preco, auto_incremento++);
				printf("%d\n", P->codigo);
				if (InserirArquivoIndexado(A, P) == 1)
					printf("Produto inserido com sucesso!\n");
				
			break; 
			
			case 2: 
				//remove um registro da arvore
				printf("Digite a chave do produto a ser removido:\n");	
				scanf("%d", &chave);
				P = RemoverArquivoIndexado(A, chave);
				if (P != NULL)
					printf("Produto removido com sucesso!");
				else
					printf("Produto não encontrado.");
			break;
			
			case 3: 
				//busca um registro na arvore
				printf("Digite a chave do produto a ser buscado:\n");	
				scanf("%d", &chave);
				P = BuscarArquivoIndexado(A, chave);
				if (P != NULL)
				{
					printf("Nome: %s \n", getNome(P));
					printf("Preco: %lf \n", getPreco(P));
					printf("Codigo: %d \n", getChave(P));
				} else {
					printf("Produto não encontrado!");
				}
			break;
			
			case 4: 
				//altera um registro na arvore
				printf("Digite a chave do produto a ser alterado:\n");	
				scanf("%d", &chave);
				printf("Digite o nome do produto a ser alterado:\n");	
				scanf("%s", nome);
				printf("Digite o preco do produto a ser alterado:\n");	
				scanf("%lf", &preco);
				
				if (AlteraArquivoIndexado(A, chave, nome, preco) == 1)
					printf("Produto alterado com sucesso!");
					
			break;
		}
	}
	
	printf("\n\nTCHAU BRIGADO!");
	
	return EXIT_SUCCESS;
}

