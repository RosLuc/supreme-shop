#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include "estoque.h"

#define DELETED -1

struct produto
{
	int codigo, quantidade;
	int status;
	char tipo[10], marca[10], cor[10], tamanho;
	float preco;
};

struct hash_est
{
	int n;
	int dim;
	Produto **v;
};

static int hash(Hash_Est *tab, int codigo)
{
	return (codigo % tab->dim);
}

Hash_Est *hshpro_cria(void)
{
	Hash_Est *tab = (Hash_Est *)malloc(sizeof(Hash_Est));
	if (tab == NULL)
	{
		printf("\n\tErro ao alocar tabela de estoque!\n");
		system("pause");
		exit(1);
	}
	tab->n = 0;
	tab->dim = 11;
	tab->v = (Produto **)malloc(tab->dim * sizeof(Produto *));
	if (tab->v == NULL)
	{
		printf("\n\tErro ao alocar vetor de produtos!\n");
		system("pause");
		exit(1);
	}
	int i;
	for (i = 0; i < tab->dim; i++)
		tab->v[i] = NULL;
	return tab;
}

static void redimensiona(Hash_Est *tab)
{
	int max_ant = tab->dim;
	int i;
	Produto **ant = tab->v;
	tab->dim *= 1.947;
	tab->v = (Produto **)malloc(tab->dim * sizeof(Produto *));
	if (tab->v == NULL)
	{
		printf("\n\tErro ao realocar vetor de produtos!\n");
		system("pause");
		exit(1);
	}
	for (i = 0; i < tab->dim; i++)
		tab->v[i] = NULL;
	for (i = 0; i < max_ant; i++)
	{
		if (ant[i])
			hshpro_insere(tab, ant[i]);
	}
	free(ant);
}

Produto *hshpro_insere(Hash_Est *tab, Produto *e)
{
	if (tab->n > 0.75 * tab->dim)
		redimensiona(tab);
	int h = hash(tab, e->codigo);
	while (tab->v[h] != NULL && tab->v[h]->status != DELETED)
	{
		h = (h + 1) % tab->dim;
	}
	tab->v[h] = e;
	tab->n++;
	return e;
}

Produto *hshpro_busca(Hash_Est *tab, int codigo)
{
	int h = hash(tab, codigo);
	while (tab->v[h] != NULL && tab->v[h]->status != DELETED)
	{
		if (tab->v[h]->codigo == codigo)
			return tab->v[h];
		h = (h + 1) % tab->dim;
	}
	return NULL;
}

void hshpro_imprime_td(Hash_Est *tab)
{
	int i, n = 0;
	Limpa_Tela();
	mensagem_inicial();
	printf("\n----------------------------------------------------------------------------");
	printf("\n\t\t\tTODOS OS PRODUTOS EM ESTOQUE:\n");
	for (i = 0; i < tab->dim; i++)
	{
		if (tab->v[i] != NULL && tab->v[i]->status != DELETED)
		{
			printf("\n\tCodigo: %d", tab->v[i]->codigo);
			printf("\tTipo: %s", tab->v[i]->tipo);
			printf("\tMarca: %s", tab->v[i]->marca);
			printf("\n\tCor: %s", tab->v[i]->cor);
			printf("\tTamanho: %c", tab->v[i]->tamanho);
			printf("\tQuantidade: %d", tab->v[i]->quantidade);
			printf("\tPreco: %.2f\n", tab->v[i]->preco);
			n = 1;
		}
	}
	if (n == 0)
	{
		printf("\n\t\tNenhum produto cadastrado!");
	}
	printf("\n----------------------------------------------------------------------------\n");
	system("pause");
}

void hshpro_libera(Hash_Est *tab)
{
	int i;
	for (i = 0; i < tab->dim; i++)
	{
		free(tab->v[i]);
	}
	free(tab);
}

int hshpro_importa(Hash_Est *tab)
{
	FILE *arq_pro = fopen("PRODUTOS.txt", "rt");
	if (arq_pro == NULL)
	{
		FILE *arq_pro_temp = fopen("PRODUTOS.txt", "wt");
		fclose(arq_pro_temp);
	}
	arq_pro = fopen("PRODUTOS.txt", "rt");
	if (arq_pro == NULL)
	{
		printf("\n\tErro ao abrir o arquivo PRODUTOS.txt!\n");
		system("pause");
		return 0;
	}
	char linha[200];
	while (fgets(linha, 200, arq_pro))
	{
		Produto *p = (Produto *)malloc(sizeof(Produto));
		if (p == NULL)
		{
			printf("\n\tErro ao alocar produto na importacao!\n");
			system("pause");
			return 0;
		}
		int n = sscanf(linha, "%d\t%9[^\t]\t%9[^\t]\t%9[^\t]\t%c\t%d\t%f", &p->codigo, p->tipo,
									 p->marca, p->cor, &p->tamanho, &p->quantidade, &p->preco);
		p->status = 0;
		if (n > 0)
		{
			if (strcmp(p->tipo, "|TIPO") != 0)
				hshpro_insere(tab, p);
		}
	}
	fclose(arq_pro);
	return 1;
}

void hshpro_exporta(Hash_Est *tab)
{
	FILE *arq_pro = fopen("PRODUTOS.txt", "wt");
	if (arq_pro == NULL)
	{
		printf("\n\tErro ao abrir o arquivo PRODUTOS.txt!\n");
		system("pause");
		exit(1);
	}
	fprintf(arq_pro, "CODIGO\t|TIPO\t|MARCA\t|COR\t|TAMANHO\t|QUANTIDADE\t|PRECO\n");
	int i;
	for (i = 0; i < tab->dim; i++)
	{
		if (tab->v[i] != NULL && tab->v[i]->status != DELETED)
		{
			fprintf(arq_pro, "%d\t", tab->v[i]->codigo);
			fprintf(arq_pro, "%s\t", tab->v[i]->tipo);
			fprintf(arq_pro, "%s\t", tab->v[i]->marca);
			fprintf(arq_pro, "%s\t", tab->v[i]->cor);
			fprintf(arq_pro, "%c\t", tab->v[i]->tamanho);
			fprintf(arq_pro, "%d\t", tab->v[i]->quantidade);
			fprintf(arq_pro, "%.2f\n", tab->v[i]->preco);
		}
	}
	fclose(arq_pro);
}

void hshpro_cadastra(Hash_Est *tab)
{
	int v = 0, n = 1;
	do
	{
		Limpa_Tela();
		Produto *p = (Produto *)malloc(sizeof(Produto));
		if (p == NULL)
		{
			printf("\n\tErro ao alocar produto ao cadastrar!\n");
			system("pause");
			exit(1);
		}
		mensagem_inicial();
		printf("\n\t\t\tCADASTRAR PRODUTO! Informe:");
		do
		{
			printf("\n\tCodigo (Apenas numeros): ");
			n = scanf(" %d", &p->codigo);
			LimpaBuffer();
		} while (n == 0);
		printf("\n\tTipo: ");
		n = scanf(" %9[^\n]", p->tipo);
		LimpaBuffer();
		printf("\n\tMarca: ");
		n = scanf(" %9[^\n]", p->marca);
		LimpaBuffer();
		printf("\n\tCor: ");
		n = scanf(" %9[^\n]", p->cor);
		LimpaBuffer();
		printf("\n\tTamanho(P,M,G,GG,EG...): ");
		p->tamanho = getchar();
		p->tamanho = toupper(p->tamanho);
		LimpaBuffer();
		printf("\n\tQuantas pecas: ");
		n = scanf(" %d", &p->quantidade);
		LimpaBuffer();
		printf("\n\tPreco: ");
		n = scanf(" %f", &p->preco);
		LimpaBuffer();
		p->status = 0;
		printf("\n----------------------------------------------------------------------------");
		if (n > 0 && hshpro_insere(tab, p) != NULL)
		{
			printf("\n\t\tProduto cadastrado com sucesso!\n");
			hshpro_exporta(tab);
			system("pause");
		}
		else
		{
			printf("Erro, produto n�o cadastrado com sucesso, verifique se informou corretamente todos os campos!\n");
			free(p);
			system("pause");
		}
		Limpa_Tela();
		v = sairdafuncao();
	} while (v == 0);
}

static void imprime(Produto *p)
{
	printf("\n\tCodigo: %d\t", p->codigo);
	printf("\tTipo: %s\t", p->tipo);
	printf("\tMarca: %s\t", p->marca);
	printf("\tCor: %s\t", p->cor);
	printf("\n\tTamanho: %c\t", p->tamanho);
	printf("\tQuantidade: %d\t", p->quantidade);
	printf("\tPreco: %.2f\n", p->preco);
}

void hshpro_consulta(Hash_Est *tab)
{
	int v = 0;
	do
	{
		Limpa_Tela();
		mensagem_inicial();
		int cod;
		printf("\n\t\t\tCONSULTAR PRODUTO! Informe:");
		printf("\n\tCodigo: ");
		scanf("%d", &cod);
		LimpaBuffer();
		Produto *p = hshpro_busca(tab, cod);
		if (p != NULL && p->status != DELETED)
		{
			imprime(p);
			printf("\n----------------------------------------------------------------------------\n");
			system("pause");
		}
		else
		{
			printf("\n----------------------------------------------------------------------------");
			printf("\n\t\tProduto nao esta cadastrado!\n");
			system("pause");
		}
		Limpa_Tela();
		v = sairdafuncao();
	} while (v == 0);
}

void hshpro_retirarcompleto(Hash_Est *tab)
{
	int v = 0;
	do
	{
		Limpa_Tela();
		mensagem_inicial();
		int cod;
		printf("\n\t\t\tEXCLUIR PRODUTO DO ESTOQUE! Informe:");
		printf("\n\tCodigo: ");
		scanf("%d", &cod);
		LimpaBuffer();
		Produto *p = hshpro_busca(tab, cod);
		if (p != NULL && p->status != DELETED)
		{
			int a;
			do
			{
				printf("\n\tTem certeza que deseja exclui?\n\tDigite (1) para SIM e (2) para NAO:");
				scanf("%d", &a);
				LimpaBuffer();
			} while (a != 1 && a != 2);
			if (a == 1)
			{
				p->status = DELETED;
				printf("\n----------------------------------------------------------------------------\n");
				printf("\n\tProduto retirado com sucesso!\n");
				system("pause");
			}
			else
			{
				printf("\n----------------------------------------------------------------------------\n");
				printf("\n\tCancelada !\n");
				system("pause");
			}
		}
		else
		{
			printf("\n\t\tProduto nao encontrado!\n");
			system("pause");
		}
		Limpa_Tela();
		v = sairdafuncao();
	} while (v == 0);
}

// usada pelo tab vendedor!
float capt_valor(Produto *p)
{
	if (p != NULL && p->status != DELETED)
		return p->preco;
	else
		return 0.00;
}
void imprime_pro(Produto *p)
{
	if (p != NULL && p->status != DELETED)
		printf("%d\t%s %s %s\t%.2f\t", p->codigo, p->tipo, p->marca, p->cor, p->preco);
}
int imp_cod_produto(Produto *p)
{
	if (p != NULL && p->status != DELETED)
		return p->codigo;
	else
		return 0;
}
int qt_produtos(Produto *p)
{
	if (p != NULL && p->status != DELETED)
		return p->quantidade;
	else
		return 0;
}
void hshpro_subtrair(Produto *p, int q)
{
	if (p != NULL && p->status != DELETED)
		p->quantidade -= q;
	if (p->quantidade == 0)
		p->status = DELETED;
}

void hshpro_acrecentar(Produto *p)
{
	if (p != NULL)
		p->quantidade++;
}
