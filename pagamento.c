//Arquivo para implementar as funções
#include "pagamento.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
//diz respeito a criação de uma lista de pagamentos
Pagamento* cria_pagamento(){
	Pagamento *pagamento = (Pagamento*) malloc(sizeof(Pagamento));
	pagamento->data_pagamento = (Data*) malloc(sizeof(Data));
	pagamento->cliente = (Cliente*) malloc(sizeof(Data));
	
	return pagamento;
}

lPagamento* cria_lista_de_pagamentos(){
	lPagamento *lista_pagamentos = (lPagamento*) malloc(sizeof(lPagamento)); 
	lista_pagamentos->pagamento=NULL;
	lista_pagamentos->prox=NULL;
	return lista_pagamentos;
}
//diz respeito ao cadastro de um pagamento
lPagamento* cadastra_pagamento(lPagamento *lst, Pagamento *pagamento){
	lPagamento *lista = cria_lista_de_pagamentos();
	lista->pagamento = pagamento;
	lista->prox = lst;
	return lista;
}
//diz respeito a busca  de um pagamento
Pagamento* busca_de_pagamento(lPagamento *lst, long long int CPF){
	lPagamento *inicializa;
	
	for(inicializa=lst; inicializa!= NULL;inicializa=inicializa->prox){
		if(inicializa->pagamento->cliente->CPF==CPF){
			return inicializa->pagamento;
		}	
	}
	
	return NULL;
}

void edita_pagamento(lPagamento *lst, Pagamento *pagamento, long long int CPF)
{
	Pagamento *pagamento_para_editar = busca_de_pagamento(lst,CPF);
	if(pagamento_para_editar != NULL){
		pagamento_para_editar->data_pagamento->dia = pagamento->data_pagamento->dia;
		pagamento_para_editar->data_pagamento->mes = pagamento->data_pagamento->mes;
		pagamento_para_editar->data_pagamento->ano = pagamento->data_pagamento->ano;
		pagamento_para_editar->status = pagamento->status ;
		pagamento_para_editar->valor = pagamento->valor;
	}
}
													 
void visualiza_pagamento(Pagamento *pagamento){
	printf("#########################\n");
	printf("Dados pessoais do pagamento\n");
	printf("Clietnte %s\n",pagamento->cliente->nomeCliente);
	printf("Idade: %d\n",pagamento->cliente->idade);
	printf("Sexo: %c\n",pagamento->cliente->sexo);
	printf("CPF: %lld\n",pagamento->cliente->CPF);
	printf("Rua: %s\n",pagamento->cliente->rua);
	printf("Número da casa: %d\n",pagamento->cliente->numeroHome);
	printf("Cidade: %s\n",pagamento->cliente->cidade);
	printf("Telefone: %d\n",pagamento->cliente->telefone);
	printf("Status: %d\n",pagamento->status);
	printf("Data do pagamento: %2d/%2d/%4d\n",pagamento->data_pagamento->dia,pagamento->data_pagamento->mes,pagamento->data_pagamento->ano);
	printf("Valor: %2.2f\n",pagamento->valor);
	printf("#########################\n");
}
lPagamento* deleta_pagamento(lPagamento *lst,long long int CPF){
	lPagamento *iterador;
	if(lst == NULL)//verificar se a lista ta vazia para
		return lst;
	
	for(iterador = lst;iterador != NULL;iterador = iterador->prox){
		if(iterador->pagamento->cliente->CPF == CPF){
			lst=iterador->prox;
			break;
		} else if((iterador->prox != NULL) && (iterador->prox->pagamento != NULL) && (iterador->prox->pagamento->cliente->CPF==CPF)){
			iterador->prox = iterador->prox->prox;
			break;
		}
	}
	
	return lst;
}
