#ifndef __PERSISTENCIA_CLIENTE_H__
#define __PERSISTENCIA_CLIENTE_H__

#include <stdio.h>
#include "cliente.h"

lCliente* carregar_arquivo_clientes(FILE *arquivo); // carrega em uma lista de clientes os dados de um arquivo

void salvar_clientes_em_arquivo(lCliente* lista_clientes,FILE *arquivo); // Salva todos os clientes em arquivo

void salvar_cliente_em_arquivo(Cliente* cliente,FILE *arquivo);  // Salva um único cliente em arquivo

#endif
