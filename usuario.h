#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED

typedef struct usuario Usuario;
typedef struct arv UsuariosArv;
typedef struct arvno ArvNo;

#include "interacao_menus.h"
#include "cliente.h"

UsuariosArv* cria_usuarios_arv (void);
void insere_usuario_arv(UsuariosArv* a, Usuario* u);
Usuario* busca_usuario(UsuariosArv* s, char* login);
void libera_usuarios(UsuariosArv* s);
void  salva_usuario(UsuariosArv* s);
void realiza_cadastro(UsuariosArv* s);
int importa_usuarios(UsuariosArv* s);
Usuario* realiza_login(UsuariosArv* s);
void interface_usuarios(UsuariosArv* s, Usuario* u);
Usuario *realiza_login(UsuariosArv *s);

#endif
