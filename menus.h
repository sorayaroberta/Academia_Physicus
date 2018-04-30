#ifndef __MENUS_H__ //Caso isto não esteja definido/carregado na pilha eu parto para defini-lo na próxima linha.
#define __MENUS_H__

#include <stdio.h>

#define MENU_PRINCIPAL_CLIENTE 1
#define MENU_PRINCIPAL_PAGAMENTO 2
#define MENU_PRINCIPAL_RELATORIOS 3
#define MENU_PRINCIPAL_SAIR 4

#define MENU_CLIENTE_CADASTRAR 1
#define MENU_CLIENTE_EDITAR 2
#define MENU_CLIENTE_REMOVER 3
#define MENU_CLIENTE_VISUALIZAR 4
#define MENU_CLIENTE_VOLTAR 5

#define MENU_PAGAMENTOS_CADASTRAR 1
#define MENU_PAGAMENTOS_EDITAR 2
#define MENU_PAGAMENTOS_VOLTAR 3

void menu_principal();
void menu_cliente();
void menu_pagamentos();
void menu_relatorios();


#endif //Finalizo a definição
