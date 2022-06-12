#ifndef VENDEDOR_H_INCLUDED
#define VENDEDOR_H_INCLUDED

#include "interacao_menus.h"

typedef struct vendedor Vendedor;
typedef struct hash_vend Hash_vend;

Hash_vend *hshvl_cria();
Vendedor *hshv1_insere(Hash_vend *tab, Vendedor *v);
static void redimensiona(Hash_vend *tab);
void hshvl_libera(Hash_vend *tab);
void vendedor_cadastra(Hash_vend* vend);
int hshvl_importa(Hash_vend *tab);
void hshvl_salva(Hash_vend *tab);


static void imprime_vend(Vendedor *v);
Vendedor* busca_vendedor(Hash_vend* vend, int codigo);
void imprime_vend_td (Hash_vend* vend);
void hshvl_consulta(Hash_vend *tab);
void hshvl_retirarcompleto(Hash_vend *tab);

#endif
