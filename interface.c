#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include "cliente.h"
#include "usuario.h"

void opcoes_cliente(Hash *TabCl)
{
    char op;
    unsigned int saida = 0;
    do
    {
        Limpa_Tela();
        mensagem_inicial();
        printf("\n\t\t\tMENU DE CLIENTES\n");
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

void opcoes_do_sistema(Hash *TabCl)
{
    char op;
    unsigned int saida = 0;
    do
    {
        Limpa_Tela();
        mensagem_inicial();
        printf("\n\t\t\tOPÇÕES\n");
        ApresentaMenu(N_O, O1, TITULO_O1, TITULO_O2, TITULO_O3, TITULO_O4);
        printf("\n----------------------------------------------------------------------------");
        op = LeOpcao(O1, O1 + N_O - 1);
        switch (op)
        {
        case O1:
            opcoes_cliente(TabCl);
            break;
        case O2:
            printf("Aguardando..");
            break;
        case O3:
            printf("Aguardando..");
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
