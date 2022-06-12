#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include "cliente.h"
#define DELETED -1

// Definicaoo da estrutura com informaacoes de um cliente
struct cliente
{
	int status;
	char nome[81];
	int cpf;
	char telefone[15];
	char cidade[20];
	char rua[30];
	char bairro[30];
	char cep[15];
	int numero;
	float debito;
};

// Estrutura da hash
struct hash
{
	int n, dim;
	Cliente **v;
};

static int hsh(Hash *tab, int cpf)
{
	return (cpf % tab->dim);
}

Hash *hshcl_cria()
{
	Hash *tab = (Hash *)malloc(sizeof(Hash));
	if (tab == NULL)
	{
		printf("\n\tErro ao alocar tabela de clientes!\n");
		system("pause");
		exit(1);
	}
	tab->n = 0;
	tab->dim = 11;
	tab->v = (Cliente **)malloc(tab->dim * sizeof(Cliente *));
	if (tab->v == NULL)
	{
		printf("\n\tErro ao alocar vetor de clientes!");
		system("pause");
		exit(1);
	}
	int i;
	for (i = 0; i < tab->dim; i++)
		tab->v[i] = NULL;
	return tab;
}

static void redimensiona(Hash *tab)
{
	int max_ant = tab->dim;
	Cliente **ant = tab->v;
	tab->n = 0;
	tab->dim *= 1.947;
	tab->v = (Cliente **)malloc(tab->dim * sizeof(Cliente *));
	if (tab->v == NULL)
	{
		printf("\n\tErro ao alocar vetor de clientes!");
		system("pause");
		exit(1);
	}
	int i;
	for (i = 0; i < tab->dim; ++i)
		tab->v[i] = NULL;
	for (i = 0; i < max_ant; ++i)
	{
		if (ant[i])
		{
			hshcl_insere(tab, ant[i]);
		}
	}
	free(ant);
}

Cliente *hshcl_insere(Hash *tab, Cliente *c)
{
	if (tab->n > 0.75 * tab->dim)
		redimensiona(tab);
	int h = hsh(tab, c->cpf);
	while (tab->v[h] != NULL && tab->v[h]->status != DELETED)
		h = (h + 1) % tab->dim;
	tab->v[h] = c;
	tab->n++;
	return c;
}

void hshcl_libera(Hash *tab)
{
	int i;
	for (i = 0; i < tab->dim; i++)
	{
		free(tab->v[i]);
	}
	free(tab);
}

int hshcl_importa(Hash *tab)
{
	FILE *arq_cli = fopen("CLIENTES.txt", "rt");
	if (arq_cli == NULL)
	{
		FILE *arq_cli_temp = fopen("CLIENTES.txt", "wt");
		fclose(arq_cli_temp);
	}
	arq_cli = fopen("CLIENTES.txt", "rt");
	if (arq_cli == NULL)
	{
		printf("\n\tErro ao abrir o arquivo CLIENTES.txt!\n");
		system("pause");
		return 0;
	}
	char linha[200];
	while (fgets(linha, 200, arq_cli))
	{
		Cliente *c = (Cliente *)malloc(sizeof(Cliente));
		if (c == NULL)
		{
			printf("\n\tErro ao alocar cliente na importacao!\n");
			system("pause");
			return 0;
		}
		int n = sscanf(linha, "%80[^\t]\t%d\t%14[^\t]\t%19[^\t]\t%29[^\t]\t%d\t%29[^\t]\t%15[^\t]\t%f\t%8[^\n]", c->nome, &c->cpf,
									 c->telefone, c->cidade, c->rua, &c->numero, c->bairro, c->cep, &c->debito);
		c->status = 0;
		if (n > 0)
		{
			if (strcmp(c->nome, "NOME") != 0)
				hshcl_insere(tab, c);
		}
	}
	fclose(arq_cli);
	return 1;
}

void hshcl_salva(Hash *tab)
{
	FILE *arq_cli = fopen("CLIENTES.txt", "wt");
	if (arq_cli == NULL)
	{
		printf("\n\tErro ao abrir o arquivo CLIENTES.txt!\n");
		system("pause");
		exit(1);
	}
	fprintf(arq_cli, "NOME\t|CPF\t|TELEFONE\t|CIDADE\t|RUA\t|NUMERO\t|BAIRRO\t|CEP\t|DEBITO\n\n");
	int i;
	for (i = 0; i < tab->dim; i++)
	{
		if (tab->v[i] != NULL && tab->v[i]->status != DELETED)
		{
			fprintf(arq_cli, "%s\t", tab->v[i]->nome);
			fprintf(arq_cli, "%d\t", tab->v[i]->cpf);
			fprintf(arq_cli, "%s\t", tab->v[i]->telefone);
			fprintf(arq_cli, "%s\t", tab->v[i]->cidade);
			fprintf(arq_cli, "%s\t", tab->v[i]->rua);
			fprintf(arq_cli, "%d\t", tab->v[i]->numero);
			fprintf(arq_cli, "%s\t", tab->v[i]->bairro);
			fprintf(arq_cli, "%s\t", tab->v[i]->cep);
			fprintf(arq_cli, "%.2f\n", tab->v[i]->debito);
		}
	}
	fclose(arq_cli);
}

Cliente *hshcl_busca(Hash *tab, int cpf)
{
	int h = hsh(tab, cpf);
	while (tab->v[h] != NULL && tab->v[h]->status != DELETED)
	{
		if (tab->v[h]->cpf == cpf)
			return tab->v[h];
		h = (h + 1) % tab->dim;
	}
	return NULL;
}

void hshcl_cadastra(Hash *tab)
{
	int v = 0;
	do
	{
		Cliente *c = (Cliente *)malloc(sizeof(Cliente));
		if (c == NULL)
		{
			printf("\n\tErro ao alocar cliente ao cadastrar!\n");
			system("pause");
			exit(1);
		}
		Limpa_Tela();
		mensagem_inicial();
		printf("\n\t\t\tCADASTRA CLIENTE! Informe:");
		printf("\n\tNome: ");
		scanf("%80[^\n]", c->nome);
		LimpaBuffer();
		int n = 1;
		do
		{
			printf("\n\tInforme apenas os números do CPF(EX.:08673133637)- \n\tCPF: ");
			n = scanf("%d", &c->cpf);
			LimpaBuffer();
		} while (n <= 0);
		printf("\n\tTelefone: ");
		n = scanf("%14[^\n]", c->telefone);
		LimpaBuffer();
		printf("\n\tCidade: ");
		n = scanf("%19[^\n]", c->cidade);
		LimpaBuffer();
		printf("\n\tRua: ");
		n = scanf("%29[^\n]", c->rua);
		LimpaBuffer();
		printf("\n\tNumero: ");
		n = scanf("%d", &c->numero);
		LimpaBuffer();
		printf("\n\tBairro: ");
		n = scanf("%29[^\n]", c->bairro);
		LimpaBuffer();
		printf("\n\tCEP: ");
		n = scanf("%14[^\n]", c->cep);
		LimpaBuffer();
		c->debito = 0.00f;
		c->status = 0;
		printf("\n----------------------------------------------------------------------------");
		Cliente *cl = hshcl_busca(tab, c->cpf);
		if (n > 0 && cl == NULL && hshcl_insere(tab, c) != NULL)
		{
			hshcl_salva(tab);
			printf("\n\t\tCliente cadastrado com sucesso!\n");
			system("pause");
		}
		else if (cl != NULL)
		{
			printf("\n\t\tCliente com esse CPF ja cadastrado\n!");
			free(c);
			system("pause");
		}
		else
		{
			printf("\n\tErro ao cadastrar cliente, verifique se adicionou todos os campos corretamente!\n");
			free(c);
			system("pause");
		}
		Limpa_Tela();
		v = sairdafuncao();
	} while (v == 0);
}
static void imprime(Cliente *c)
{
	printf(" \n\tNome: %s", c->nome);
	printf(" \tCPF: %d", c->cpf);
	printf(" \tTelefone: %s", c->telefone);
	printf(" \n\tCidade: %s", c->cidade);
	printf(" \tRua: %s", c->rua);
	printf(" \tNumero: %d", c->numero);
	printf(" \n\tBairro: %s", c->bairro);
	printf(" \tCEP: %s", c->cep);
	printf(" \tDebito: %.2f", c->debito);
}

void hshcl_consulta(Hash *tab)
{
	int v = 0, cpf, n = 1;
	do
	{
		Limpa_Tela();
		mensagem_inicial();
		printf("\n\t\t\tCONSULTA CLIENTE! Informe:");
		do
		{
			printf("\n\tInforme apenas os numeros do CPF(EX.:08673133637)- \n\tCPF: ");
			n = scanf("%d", &cpf);
			LimpaBuffer();
		} while (n == 0);
		Cliente *c = hshcl_busca(tab, cpf);
		if (c != NULL && c->status != DELETED)
		{
			imprime(c);
			printf("\n----------------------------------------------------------------------------\n");
		}
		else
		{
			printf("\n----------------------------------------------------------------------------");
			printf("\n\tNao possui Cliente com esse cpf cadastrado, verifique se informou o cpf corretamente!\n");
		}
		system("pause");
		Limpa_Tela();
		v = sairdafuncao();
	} while (v == 0);
}

void hshcl_imprime(Hash *tab)
{
	int i, n = 0;
	Limpa_Tela();
	mensagem_inicial();
	printf("\n\t\t\tTODOS OS CLIENTES:");
	for (i = 0; i < tab->dim; i++)
	{
		if (tab->v[i] != NULL && tab->v[i]->status != DELETED)
		{
			printf("\n\tNome: %s", tab->v[i]->nome);
			printf("\tCPF: %d", tab->v[i]->cpf);
			printf("\tTelefone: %s", tab->v[i]->telefone);
			printf("\n\tCidade: %s", tab->v[i]->cidade);
			printf("\tRua: %s", tab->v[i]->rua);
			printf("\tNumero: %d", tab->v[i]->numero);
			printf("\n\tBairro: %s", tab->v[i]->bairro);
			printf("\tCEP: %s", tab->v[i]->cep);
			printf("\tDebito: %.2f", tab->v[i]->debito);
			n = 1;
		}
	}
	if (n == 0)
	{
		printf("\n\t\tNenhum Cliente cadastrado!");
	}
	printf("\n----------------------------------------------------------------------------\n");
	system("pause");
}

void hshcl_retirarcompleto(Hash *tab)
{
	int v = 0, n = 1;
	do
	{
		Limpa_Tela();
		mensagem_inicial();
		int cpf;
		printf("\n\t\tREMOVER CLIENTE! Informe:");
		do
		{
			printf("\n\tInforme apenas os numeros do CPF(EX.:08673133637)- \n\tCPF: ");
			n = scanf("%d", &cpf);
			LimpaBuffer();
		} while (n == 0);
		Cliente *cl = hshcl_busca(tab, cpf);
		if (cl != NULL)
		{
			int u;
			n = 0;
			do
			{
				printf("\n\tTem certeza que deseja realizar essa acao, não podera ser desfeita?\n\tDigite (1) para SIM e (2) para NAO:");
				n = scanf("%d", &u);
				LimpaBuffer();
			} while (n <= 0);
			if (u == 1)
			{
				cl->status = DELETED;
				printf("\n----------------------------------------------------------------------------\n");
				printf("\n\t\tCliente removido com sucesso!\n");
			}
		}
		else
		{
			printf("\n----------------------------------------------------------------------------\n");
			printf("\n\t\tCliente não encontrado!\n");
		}
		hshcl_salva(tab);
		system("pause");
		Limpa_Tela();
		v = sairdafuncao();
	} while (v == 0);
}
