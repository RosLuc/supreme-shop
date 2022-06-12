#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "vendedor.h"

#define DELETED -1
struct vendedor{
	char nome_v[81];
	int codigo_v;
	int status;
	int n_vendas;
};

struct hash_vend{
	int n, dim;
	Vendedor **v;
};

static int hash(Hash_vend *tab, int codigo){
	return (codigo % tab->dim);
}

Hash_vend *hshvl_cria(){
	Hash_vend *tab = (Hash_vend *)malloc(sizeof(Hash_vend));
	if (tab == NULL)
	{
		printf("\n\tErro ao alocar tabela de vendedores!\n");
		system("pause");
		exit(1);
	}
	tab->n = 0;
	tab->dim = 11;
	tab->v = (Vendedor **)malloc(tab->dim * sizeof(Vendedor *));
	if (tab->v == NULL)
	{
		printf("\n\tErro ao alocar vetor de vendedores!");
		system("pause");
		exit(1);
	}
	int i;
	for (i = 0; i < tab->dim; i++)
		tab->v[i] = NULL;
	return tab;
}



static void redimensiona(Hash_vend *tab)
{
	int max_ant = tab->dim;
	Vendedor **ant = tab->v;
	tab->n = 0;
	tab->dim *= 1.947;
	tab->v = (Vendedor **)malloc(tab->dim * sizeof(Vendedor *));
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
			hshv1_insere(tab, ant[i]);
		}
	}
	free(ant);
}


Vendedor *hshv1_insere(Hash_vend *tab, Vendedor *v)
{
	if (tab->n > 0.75 * tab->dim)
		redimensiona(tab);
	int h = hash(tab, v->codigo_v);
	while (tab->v[h] != NULL && tab->v[h]->status != DELETED)
	{
		h = (h + 1) % tab->dim;
	}
	tab->v[h] = v;
	tab->n++;
	return v;
}


void hshvl_libera(Hash_vend *tab)
{
	int i;
	for (i = 0; i < tab->dim; i++)
	{
		free(tab->v[i]);
	}
	free(tab);
}


void vendedor_cadastra(Hash_vend* vend){
	int v1 = 0,n = 0;
	do{
		Limpa_Tela();
		Vendedor* v = (Vendedor*)malloc(sizeof(Vendedor));
		if(v == NULL){
			printf("\n\tErro ao alocar vendedor ao cadastrar!\n");
			system("pause");
			exit(1);
		}
		mensagem_inicial();
		printf("\n\t\t\tCADASTRAR VENDEDOR! Informe:");
		printf("\n\tNome: ");
		n = scanf(" %80[^\n]", v->nome_v);
		LimpaBuffer();
		printf("\n\tCodigo vendas (Apenas numeros): ");
		n = scanf(" %d", &v->codigo_v);
		LimpaBuffer();
		printf("\n\tNumero de vendas: ");
		n = scanf(" %d", &v->n_vendas);
		LimpaBuffer();
		printf("\n----------------------------------------------------------------------------");
		if(n > 0){
			hshv1_insere(vend, v);
			hshvl_salva(vend);
			printf("\n\t\tVendedor cadastrado com sucesso!\n");
			system("pause");
		}
		else{
			printf("Erro, vendedor nao cadastrado com sucesso, verifique se informou corretamente todos os campos!\n");
			free(v);
			system("pause");
		}
		Limpa_Tela();
		v1 = sairdafuncao();
	}while(v1 == 0);
}

int hshvl_importa(Hash_vend *tab)
{
 	FILE *arq_vend = fopen("VENDEDORES.txt", "rt");
	if (arq_vend == NULL)
	{
		FILE *arq_vend_temp = fopen("VENDEDORES.txt", "wt");
		fclose(arq_vend_temp);
	}
	arq_vend = fopen("VENDEDORES.txt", "rt");
	if (arq_vend == NULL)
	{
		printf("\n\tErro ao abrir o arquivo VENDEDORES.txt!\n");
		system("pause");
		return 0;
	}

 	char linha[200];
	while(fgets(linha,200,arq_vend)){
   		Vendedor* v = (Vendedor*)malloc(sizeof(Vendedor));
		if(v==NULL){
			printf("\n\tErro ao alocar vendedor na importacao\n!");
	   		system("pause");
			fclose(arq_vend);
			return 0;
		}

 		int n = sscanf(linha,"%80[^\t]\t%d\t%d", v->nome_v, &v->codigo_v, &v->n_vendas);
  		v->status = 0;
  		if(n>0){
      		if(strcmp(v->nome_v,"NOME")!=0 )
       		hshv1_insere(tab,v);
       	}
	}
    fclose(arq_vend);
    return 1;
}

void hshvl_salva(Hash_vend *tab)
{
    FILE* arq_vend = fopen("VENDEDORES.txt", "at");
	if(arq_vend == NULL){
		printf("\n\tErro ao abrir o arquivo VENDEDOR.txt!\n");
		system("pause");
		exit(1);
	}
	fprintf(arq_vend, "NOME\t|CODIGO DE VENDAS\t|NUMERO DE VENDAS\n");
	int i;
	for(i = 0; i < tab->dim; i++){
		if(tab->v[i] != NULL && tab->v[i]->status != DELETED){
			fprintf(arq_vend,"%s\t", tab->v[i]->nome_v);
			fprintf(arq_vend,"%d\t", tab->v[i]->codigo_v);
			fprintf(arq_vend,"%d\n", tab->v[i]->n_vendas);

		}
	}
	fclose(arq_vend);
}


static void imprime_vend(Vendedor *v){
	printf("\tNome: %s", v->nome_v);
	printf("\tCodigo de vendas: %d", v->codigo_v);
	printf("\tNumero de vendas: %d", v->n_vendas);
}

Vendedor* busca_vendedor(Hash_vend* tab, int codigo){
	int h = hash(tab, codigo);
	while (tab->v[h] != NULL && tab->v[h]->status != DELETED)
	{
		if (tab->v[h]->codigo_v == codigo)
			return tab->v[h];
		h = (h + 1) % tab->dim;
	}
	return NULL;
}


void imprime_vend_td (Hash_vend* vend){
	int i, n = 0;
	Limpa_Tela();
	mensagem_inicial();
	printf("\n\t\t\tTODOS OS VENDEDORES:");
	for (i = 0; i < vend->dim; i++)
	{
		if(vend->v[i] != NULL && vend->v[i]->status != DELETED){
			printf("\n\tNome: %s", vend->v[i]->nome_v);
			printf("\tCodigo de vendas: %d", vend->v[i]->codigo_v);
			printf("\n\tNumero de vendas: %d", vend->v[i]->n_vendas);
			n = 1;
        }
	}
	if (n == 0)
	{
		printf("\n\t\tNenhum vendedor cadastrado!");
	}
	printf("\n----------------------------------------------------------------------------\n");
	system("pause");

}
void hshvl_consulta(Hash_vend *tab)
{
	int count = 1;
	do
	{
		Limpa_Tela();
		mensagem_inicial();
		int cod;
		printf("\n\t\t\tCONSULTAR VENDEDOR! Informe:");
		printf("\n\tCodigo: ");
		scanf("%d", &cod);
		LimpaBuffer();
		Vendedor *v = busca_vendedor(tab, cod);
		if (v != NULL && v->status != DELETED)
		{
            imprime_vend(v);
			printf("\n----------------------------------------------------------------------------\n");
			system("pause");
		}
		else
		{
			printf("\n----------------------------------------------------------------------------");
			printf("\n\tVendedor nao cadastrado!\n");
			system("pause");
		}
		Limpa_Tela();
		count = sairdafuncao();

	} while (count != 0);

}


void hshvl_retirarcompleto(Hash_vend *tab)
{
	int count = 1;
	do
	{
		Limpa_Tela();
		mensagem_inicial();
		int cod;
		printf("\n\t\t\tEXCLUIR VENDEDOR! Informe:");
		printf("\n\tCodigo: ");
		scanf("%d", &cod);
		LimpaBuffer();
		Vendedor *v = busca_vendedor(tab, cod);
		if (v != NULL && v->status != DELETED)
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
				v->status = DELETED;
				printf("\n----------------------------------------------------------------------------\n");
				printf("\n\tVendedor excluido com sucesso!\n");
				system("pause");
			}
			else
			{
				printf("\n----------------------------------------------------------------------------\n");
				printf("\n\tAcao Cancelada !\n");
				system("pause");
			}
		}
		else
		{
			printf("\n\t\tVendedor nao encontrado!\n");
			system("pause");
		}
		Limpa_Tela();
		count = sairdafuncao();
	} while (count != 1);

}
