#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include "interacao_menus.h"


void LimpaBuffer(void) {
    int valorLido;
    do {
        valorLido = getchar();
    } while ((valorLido != '\n') && (valorLido != EOF));
}

int LeOpcao(int menorValor, int maiorValor){
    int op;
    while (1) {
        printf("\nDigite sua opcao: ");
        op = getchar();
        if (op >= menorValor && op <= maiorValor) {
            LimpaBuffer();
            break;
        }
        else {
            printf("\n\t\tOpcao invalida. Tente novamente.");
            printf("\n\t\tA opcao deve estar entre %c e %c.\n", menorValor, maiorValor);
            printf("\n\t\tEnter para tentar novamente!");
            LimpaBuffer();
        }
    }
    return op;
}

void ApresentaMenu(int nItens, int menorOpcao, ...){
    int i;
    va_list argumentos;
    va_start(argumentos, menorOpcao);
    for(i = 0; i < nItens; ++i) {
        printf("\n\t\t\t%c-%s", menorOpcao++, va_arg(argumentos, char *));
    }
    va_end(argumentos);
}

void Limpa_Tela(void){
	system("cls");
}

void mensagem_inicial(){
	printf("\n\t\tALE'S - SISTEMAS DE MONITORAMENTO EM LOJAS!\n");
	printf("\n----------------------------------------------------------------------------");
}

int sairdafuncao(){
	unsigned char OP;
	mensagem_inicial();
	printf("\n\t\tDeseja voltar para tela inicial?");
	ApresentaMenu(N_OPS, OPCS1,TITULO_OPS1, TITULO_OPS2);
	printf("\n----------------------------------------------------------------------------");
	OP = LeOpcao(OPCS1, OPCS1 + N_OPS - 1);
	switch(OP) {
       	case OPCAO1:
			return 0;
		   	break;
       	case OPCAO2:
		   	return 1;
       		break;
       	default:
           	printf("\nEste programa possui um bug.");
           	exit(1);
 	}
}
