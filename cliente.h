#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H__INCLUDED

#include "interacao_menus.h"



typedef struct cliente Cliente;
typedef struct hash Hash;

Hash* hshcl_cria();
Cliente* hshcl_insere(Hash* tab, Cliente* c);
void hshcl_libera (Hash* tab);
int hshcl_importa(Hash* tab);
void hshcl_salva(Hash* tab);
Cliente* hshcl_busca (Hash* tab, int cpf);
void hshcl_cadastra(Hash* tab);
static void imprime(Cliente* c);
void hshcl_consulta(Hash* tab);

#endif


