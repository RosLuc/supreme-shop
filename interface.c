#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include "cliente.h"
#include "usuario.h"
#include "estoque.h"
#include "vendedor.h"

void opcoes_cliente(Hash *TabCl)
{
    char op;
    unsigned int saida = 0;
    do
    {
        Limpa_Tela();
        mensagem_inicial();
        printf("\n\t\t\tOPCAO DE CLIENTES\n");
        ApresentaMenu(N_OPCA, OPCA1, TITULO_OPCA1, TITULO_OPCA2, TITULO_OPCA3, TITULO_OPCA4, TITULO_OPCA5);
        printf("\n----------------------------------------------------------------------------");
        op = LeOpcao(OPCA1, OPCA1 + N_OPCA - 1);
        switch (op)
        {
        case OPCA1:
            hshcl_cadastra(TabCl);
            break;
        case OPCA2:
            hshcl_retirarcompleto(TabCl);
            break;
        case OPCA3:
            hshcl_consulta(TabCl);
            break;
        case OPCA4:
            hshcl_imprime(TabCl);
            break;
        case OPCA5:
            saida = 1;
            break;
        default:
            printf("\n\tEste programa possui um bug.\n");
            system("pause");
            exit(1);
        }
    } while (!saida);
}

void opcoes_estoque(Hash_Est *TabEst)
{
    char op;
    unsigned int saida = 0;
    do
    {
        Limpa_Tela();
        mensagem_inicial();
        printf("\n\t\t\tOPCOES DO ESTOQUE\n");
        ApresentaMenu(N_OPA, OPA1, TITULO_OPA1, TITULO_OPA2, TITULO_OPA3, TITULO_OPA4, TITULO_OPA5);
        printf("\n----------------------------------------------------------------------------");
        op = LeOpcao(OPA1, OPA1 + N_OPA - 1);
        switch (op)
        {
        case OP1:
            hshpro_cadastra(TabEst);
            break;
        case OP2:
            hshpro_retirarcompleto(TabEst);
            break;
        case OP3:
            hshpro_imprime_td(TabEst);
            break;
        case OP4:
            hshpro_consulta(TabEst);
            break;
        case OP5:
            saida = 1;
            break;
        default:
            printf("\n\tEste programa possui um bug.\n");
            system("pause");
            exit(1);
        }
    } while (!saida);
}



void opcoes_vendedor(Hash_vend *TabVend)
{
    char op;
    unsigned int saida = 0;
    do
    {
        Limpa_Tela();
        mensagem_inicial();
        printf("\n\t\t\tOPCOES DO VENDEDOR\n");
        ApresentaMenu(N_OPC, OPC1, TITULO_OPC1, TITULO_OPC2, TITULO_OPC3, TITULO_OPC4, TITULO_OPC5);
        printf("\n----------------------------------------------------------------------------");
        op = LeOpcao(OPC1, OPC1 + N_OPC - 1);
        switch (op)
        {
        case OP1:
            vendedor_cadastra(TabVend);
            break;
        case OP2:
            hshvl_retirarcompleto(TabVend);
            break;
        case OP3:
            imprime_vend_td(TabVend);
            break;
        case OP4:
            hshvl_consulta(TabVend);
            break;
        case OP5:
            saida = 1;
            break;
        default:
            printf("\n\tEste programa possui um bug.\n");
            system("pause");
            exit(1);
        }
    } while (!saida);
}


void opcoes_do_sistema(Hash *TabCl, Hash_Est *TabEst, Hash_vend *TabVend)
{
    char op;
    unsigned int saida = 0;
    do
    {
        Limpa_Tela();
        mensagem_inicial();
        printf("\n\t\t\tOPCOES\n");
        ApresentaMenu(N_O, O1, TITULO_O1, TITULO_O2, TITULO_O3, TITULO_O4);
        printf("\n----------------------------------------------------------------------------");
        op = LeOpcao(O1, O1 + N_O - 1);
        switch (op)
        {
        case O1:
            opcoes_cliente(TabCl);
            break;
        case O2:
            opcoes_estoque(TabEst);
            break;
        case O3:
            opcoes_vendedor(TabVend);
            break;
        case O4:
            saida = 1;
            printf("\n\t\tDeslogando...");
            break;
        default:
            printf("\n\tEste programa possui um bug.\n");
            system("pause");
            exit(1);
        }
    } while (!saida);
}
