#include "persistencia_pagamento.h"
#include <stdlib.h>
#include <string.h>
//salva um pagamento
void salvar_pagamento_em_arquivo(Pagamento *pagamento,FILE *arquivo){
	fprintf(arquivo,"%d/%d/%d#",pagamento->data_pagamento->dia,pagamento->data_pagamento->mes,pagamento->data_pagamento->ano);
	fprintf(arquivo,"%2.2f#",pagamento->valor);
	fprintf(arquivo,"%d#",pagamento->status);
	fprintf(arquivo,"%lld\n",pagamento->cliente->CPF);
}
//salva a lista de pagamentos
void salvar_pagamentos_em_arquivo(lPagamento *lista_pagamentos,FILE *arquivo){
	for(lPagamento *iter = lista_pagamentos; iter != NULL; iter=iter->prox){
		if(iter->pagamento != NULL){
			salvar_pagamento_em_arquivo(iter->pagamento,arquivo);
		}
	}
}

lPagamento* carregar_arquivo_pagamentos(FILE *arquivo, lCliente *lst_clientes){
	lPagamento* lst_pagamento = cria_lista_de_pagamentos();
	Pagamento* pagamento;
	
	int dia;
	int mes;
	int ano;
	float valor;
	int status;
	long long int CPF;
	
	// Carrega os pagamentos que estão em arquivo em uma lista de pagamentos
	// Os pagamentos mais antigos são os que ficarão no início da lista [obs.: não queremos isso]
	while( (fscanf(arquivo,"%d/%d/%d#%f#%d#%lld\n", &dia, &mes, &ano, &valor, &status, &CPF)) != EOF ){
		pagamento = cria_pagamento();
		pagamento->data_pagamento->dia = dia;
		pagamento->data_pagamento->mes = mes;
		pagamento->data_pagamento->ano = ano;
		
		pagamento->valor = valor;
		pagamento->status = status;
		
		pagamento->cliente = busca_de_cliente(lst_clientes,CPF);
		
		lst_pagamento = cadastra_pagamento(lst_pagamento,pagamento);
	}

	// Para mudar essa ordem, crio outra lista
	// Ordenar pagamentos de modo que os mais recentes apareçam primeiro na lista
	lPagamento *lst_pagamento_2 = cria_lista_de_pagamentos();
	
	for(lPagamento *iterador = lst_pagamento; iterador != NULL; iterador = iterador->prox){
		if(iterador->pagamento != NULL){
			lst_pagamento_2 = cadastra_pagamento(lst_pagamento_2,iterador->pagamento);
		}
	}
	
	return lst_pagamento_2;
}
