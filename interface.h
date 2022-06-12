#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

#include "interacao_menus.h"
#include "usuario.h"
#include "estoque.h"
#include "vendedor.h"

void opcoes_do_sistema(Hash *TabCl, Hash_Est *TabEst, Hash_vend *TabVend);
void opcoes_cliente(Hash *TabCl);
void opcoes_estoque(Hash_Est* TabEst);
void opcoes_vendedor(Hash_vend *TabVend);

#endif


