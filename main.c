#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <locale.h>
#include <string.h>
#include "cliente.h"
#include "interacao_menus.h"
#include "interface.h"
#include "usuario.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[])
{

	unsigned char op;
	unsigned int fech = 0;
	UsuariosArv *usuariosArv = sis_cria();
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
		printf("\n\tErro ao importar usuario do arquivo!\n");
		free(tabCliente);
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
			// Usuario* usu = realiza_login(sys);
			// f(usu != NULL){
			// interface_usuarios(sys, usu);

			//   }
			opcoes_do_sistema(tabCliente);

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
	/*sis_salva(sys);
	sis_libera(sys);*/

	return 0;
}
