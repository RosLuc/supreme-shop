#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <locale.h>
#include <string.h>
#include "cliente.h"
#include "interacao_menus.h"
#include "interface.h"
#include "usuario.h"
#include "estoque.h"
#include "vendedor.h"

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "");
	unsigned char op;
	unsigned int fech = 0;
	UsuariosArv *usuariosArv = cria_usuarios_arv();
	if (!importa_usuarios(usuariosArv))
	{
		printf("\n\tErro ao importar usuario do arquivo!\n");
		free(usuariosArv);
		system("pause");
		return 0;
	}
	Hash *tabCliente = hshcl_cria();
	if (!hshcl_importa(tabCliente))
	{
		printf("\n\tErro ao importar cliente do arquivo!\n");
		free(tabCliente);
		system("pause");
		return 0;
	}
	Hash_Est *tabEstoque = hshpro_cria();
	if (!hshpro_importa(tabEstoque))
	{
		printf("\n\tErro ao importar estoque do arquivo!\n");
		free(tabEstoque);
		system("pause");
		return 0;
	}
	Hash_vend *tabVendedor = hshvl_cria();
	if (!hshvl_importa(tabVendedor))
	{
		printf("\n\tErro ao importar estoque do arquivo!\n");
		free(tabVendedor);
		system("pause");
		return 0;
	}

	do
	{
		Limpa_Tela();
		mensagem_inicial();
		printf("\n\t\t\t+++ BEM VINDO +++\n");
		ApresentaMenu(N_OPCOES, OPCAO1, TITULO_OPCAO1, TITULO_OPCAO2,
									TITULO_OPCAO3);
		printf("\n\n----------------------------------------------------------------------------");
		op = LeOpcao(OPCAO1, OPCAO1 + N_OPCOES - 1);
		switch (op)
		{
		case OPCAO1:
			Limpa_Tela();
			Usuario *usu = realiza_login(usuariosArv);
			if (usu != NULL)
			{
				opcoes_do_sistema(tabCliente, tabEstoque, tabVendedor);
			}
			break;
		case OPCAO2:
			Limpa_Tela();
			realiza_cadastro(usuariosArv);
			break;
		case OPCAO3:
			fech = 1;
			printf("\n\t\tObrigado por usar esse programa.");
			break;
		default:
			printf("\n\tEste programa possui um bug.");
			return 1;
		}

	} while (!fech);
	salva_usuario(usuariosArv);
	libera_usuarios(usuariosArv);

	return 0;
}
