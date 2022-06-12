#ifndef ESTOQUE_H_INCLUDED
#define ESTOQUE_H_INCLUDED

#include "interacao_menus.h"


typedef struct produto Produto;
typedef struct hash_est Hash_Est;

Hash_Est* hshpro_cria (void);
Produto* hshpro_insere (Hash_Est* tab, Produto* e);
Produto* hshpro_busca (Hash_Est* tab, int codigo);
void hshpro_imprime_td (Hash_Est* tab);
void hshpro_libera (Hash_Est* tab);
int hshpro_importa(Hash_Est* tab);
void hshpro_exporta(Hash_Est* tab);
void hshpro_cadastra(Hash_Est* tab);
void hshpro_consulta(Hash_Est* tab);
void hshpro_retirarcompleto(Hash_Est* tab);

void hshpro_subtrair(Produto* p, int q);
void hshpro_acrecentar(Produto* p);
float capt_valor(Produto* p);
void imprime_pro(Produto* p);
int imp_cod_produto(Produto* p);
int qt_produtos(Produto* p);

#endif
