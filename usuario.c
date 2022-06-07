
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <windows.h>
#include "usuario.h"

struct usuario
{
	char nome[100];
	char login[20];
	char senha[20];
	int perfil;
};

struct arvno
{
	Usuario *info;
	ArvNo *esq;
	ArvNo *dir;
};

struct arv
{
	ArvNo *raiz;
};

UsuariosArv* sis_cria (void){
    UsuariosArv* s = (UsuariosArv*)malloc(sizeof(UsuariosArv));
    if(s == NULL){
        printf("Erro na alocacão do usuário ao arv de usuários!\n");
        system("pause");
        exit(1);
    }
    s->raiz = NULL;
    return s;
}

static ArvNo* insere(ArvNo* r, Usuario* u){
	if(r == NULL){
		r = (ArvNo*)malloc(sizeof(ArvNo));
		if(u == NULL){
            printf("Erro na alocaçãoo do nó no sistema!\n");
            system("pause");
            exit(1);
		}
		r->info = u;
		r->esq = r->dir = NULL;
	}
	else if(strcmp(r->info->login, u->login) > 0)
		r->esq = insere(r->esq, u);
	else
		r->dir = insere(r->dir, u);
	return r;
}

void insere_usuario_arv(UsuariosArv* a, Usuario* u){
	a->raiz = insere(a->raiz, u);
}

static Usuario* busca(ArvNo* r, char* login){
    if(r != NULL){
        if(strcmp(r->info->login, login) > 0)return busca(r->esq, login);
        else if(strcmp(r->info->login, login) < 0)return busca(r->dir, login);
        else return r->info;
    }
    return NULL;
}

Usuario* busca_usuario(UsuariosArv* s, char* login){
    return busca(s->raiz, login);
}

static void salva (FILE* fp, ArvNo* r){
    if(r != NULL){
        salva(fp, r->esq);
        fprintf(fp, "NOME:\t%s\nLOGIN:\t%s\nSENHA:\t%s\nPERFIL:\t%d\n\n", r->info->nome, r->info->login, r->info->senha, r->info->perfil);
        salva(fp, r->dir);
    }
}

void  salva_usuario(UsuariosArv* s){
    FILE* fp = fopen("USUARIOS.txt", "wt");
    if(fp == NULL){
        printf("Erro na abertura do arquivo ao salvar o usu�rio");
        system("pause");
        exit(1);
    }
    salva(fp, s->raiz);
}

static Usuario* usuario_cadastra(char* nome, char* login, char* senha, int perfil){
	Usuario* novo = (Usuario*) malloc(sizeof(Usuario));
	if(novo == NULL){
        printf("Erro na alocacão do usuario!\n");
        system("pause");
        exit(1);
	}

	strcpy(novo->nome, nome);
	strcpy(novo->login, login);
	strcpy(novo->senha, senha);
	novo->perfil = perfil;

	return novo;
}

int importa_usuarios(UsuariosArv* usuariosArv){
    char nome[100];
    char login[20];
    char senha[20];
    int perfil;
    FILE* fp = fopen("USUARIOS.txt", "rt");
    if(fp == NULL){
        printf("\n\tErro na abertura do arquivo de usuario ao importar!\n");
        system("pause");
        return 0;
    }
	int n = 0;
	do{
		n = fscanf(fp, "NOME:\t%99[^\n]\nLOGIN:\t%19[^\n]\nSENHA:\t%19[^\n]\nPERFIL:\t%d\n\n", nome, login, senha, &perfil);
   		if(n > 0){
			Usuario* usu = usuario_cadastra(nome, login, senha, perfil);
        	insere_usuario_arv(usuariosArv, usu);
		}

	}while(n > 0);
    fclose(fp);
    return 1;
}

void realiza_cadastro(UsuariosArv *s)
{
	int v = 0;
	do
	{
		Usuario *novo = (Usuario *)malloc(sizeof(Usuario));
		if (novo == NULL)
		{
			printf("Erro na alocacão do usuário ao cadastrar!\n");
			system("pause");
			exit(1);
		}
		mensagem_inicial();
		printf("\n\t\t\tCADASTRAR USUÁRIO!\n");
		printf("\n\t\tÉ obrigatório o preenchimento de todos os campos.\n");
		printf("\n\tDigite seu nome: ");
		scanf(" %99[^\n]", novo->nome);
		LimpaBuffer();
		printf("\n\tDigite seu login: ");
		scanf(" %19[^\n]", novo->login);
		LimpaBuffer();
		printf("\n\tDigite sua senha: ");
		scanf(" %19[^\n]", novo->senha);
		LimpaBuffer();
		do
		{
			printf("\n\tQual seu perfil?\nDigite (1) para ADMINISTRADOR e (2) para RECEPCIONISTA: ");
			scanf("%d", &novo->perfil);
			LimpaBuffer();
		} while (novo->perfil != 1 && novo->perfil != 2);
		printf("\n----------------------------------------------------------------------------");
		if (busca_usuario(s, novo->login) == NULL)
		{
			insere_usuario_arv(s, novo);
			salva_usuario(s);
			printf("\n\t\tUsuário cadastrado com sucesso!\n");
			system("pause");
		}
		else
		{
			printf("\n\t\tUsuário já está cadastrado!\n");
			free(novo);
			system("pause");
		}
		Limpa_Tela();
		v = sairdafuncao();
	} while (v == 0);
}
