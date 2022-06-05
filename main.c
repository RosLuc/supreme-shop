#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <locale.h>
#include <string.h>
#include "cliente.h"
#include "interacao_menus.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {

	unsigned char op;
    unsigned int fech = 0;
    /*Sistema* sys = sis_cria();
    if(!importa_cadastro(sys)){
    	printf("\n\tErro ao importar usuario do arquivo!\n");
 		free(sys);
    	system("pause");
		return 0;
	}*/
	Cliente* cliente = hshcl_cria();
	if(!hshcl_importa(cliente)){
    	printf("\n\tErro ao importar usuario do arquivo!\n");
 		free(cliente);
    	system("pause");
		return 0;
	}
    do{
		Limpa_Tela();
		mensagem_inicial();
		printf("\n\t\t\t+++ BEM VINDO +++\n");
		ApresentaMenu(N_OPCOES, OPCAO1,TITULO_OPCAO1, TITULO_OPCAO2,
						TITULO_OPCAO3);
		printf("\n\n----------------------------------------------------------------------------");
		op = LeOpcao(OPCAO1, OPCAO1 + N_OPCOES - 1);
		switch(op) {
            case OPCAO1:
                Limpa_Tela();
                //Usuario* usu = realiza_login(sys);
                //f(usu != NULL){
                    //interface_usuarios(sys, usu);

                //   }
                opcoes_do_sistema(cliente);

                break;
            case OPCAO2:
				//Limpa_Tela();
               	//realiza_cadastro(sys);
                break;
            case OPCAO3:
				fech = 1;
            	printf("\n\t\tObrigado por usar esse programa.");
            	break;
            default:
                printf("\n\tEste programa possui um bug.");
                return 1;
        }

    }while(!fech);
	/*sis_salva(sys);
	sis_libera(sys);*/

	return 0;
}
