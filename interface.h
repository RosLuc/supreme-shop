#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

#include "interacao_menus.h"
#include "usuario.h"
#include "estoque.h"

typedef struct cliente Cliente;
typedef struct hash Hash;

void opcoes_do_sistema();
void opcoes_cliente();
void opcoes_estoque(Hash_Est* TabEst);

#endif


