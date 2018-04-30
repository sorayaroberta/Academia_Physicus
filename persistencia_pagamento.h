#ifndef __PERSISTENCIA_PAGAMENTO_H__
#define __PERSISTENCIA_PAGAMENTO_H__

#include <stdio.h>
#include "pagamento.h"
#include "cliente.h"

lPagamento* carregar_arquivo_pagamentos(FILE *arquivo, lCliente *lst_clientes); // carrega em uma lista de pagamentos os dados de um arquivo

void salvar_pagamentos_em_arquivo(lPagamento* lista_pagamentos, FILE *arquivo); // Salva todos os pagamentos em arquivo

void salvar_pagamento_em_arquivo(Pagamento* pagamento,FILE *arquivo);  // Salva um único pagamento em arquivo

#endif
