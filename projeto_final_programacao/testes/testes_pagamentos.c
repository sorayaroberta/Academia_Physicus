#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "pagamento.h"
#include "persistencia_pagamento.h"

void gera_clientes();
void testa_cadastro_pagamentos();
void testa_busca_pagamentos();
void testa_edicao_pagamentos();
void testa_visualiza_pagamento();
void testa_deleta_pagamento();
void testa_salvar_pagamentos_em_arquivo();

lPagamento* lst_pagamentos;
lCliente* lst_cliente;

int run_tests_pagamentos(){  
	gera_clientes();
	testa_cadastro_pagamentos();
	testa_busca_pagamentos();
	testa_edicao_pagamentos();
	testa_visualiza_pagamento();
	testa_salvar_pagamentos_em_arquivo();
	//testa_deleta_pagamento();
	return 0;
}

void gera_clientes(){
	lst_cliente=cria_lista_de_clientes();
	Cliente* cliente=(Cliente*) malloc(sizeof(Cliente));
	
	strcpy(cliente->nomeCliente,"soso");
	cliente->idade = 20;
	cliente->sexo = 'f';
	cliente->CPF = 	12345678901;
	cliente->numeroHome = 4;
	strcpy(cliente->rua,"rua dos prazeres");
	strcpy(cliente->cidade,"js");
	cliente->telefone = 99999;
	
	Cliente* cliente2=(Cliente*) malloc(sizeof(Cliente));
	
	strcpy(cliente2->nomeCliente,"nana");
	cliente2->idade = 24;
	cliente2->sexo = 'm';
	cliente2->CPF = 	12345678902;
	cliente2->numeroHome = 5;
	strcpy(cliente2->cidade,"nat");
	strcpy(cliente2->rua,"rua da formiga");
	cliente2->telefone = 8888;
	
	Cliente* cliente3=(Cliente*) malloc(sizeof(Cliente));
	
	strcpy(cliente3->nomeCliente,"adriane");
	cliente3->idade = 26;
	cliente3->sexo = 'f';
	cliente3->CPF = 	2365423145;
	cliente3->numeroHome = 10;
	strcpy(cliente3->cidade,"naTAL");
	strcpy(cliente3->rua,"rua do alambique");
	cliente3->telefone = 88424388;
	
	lst_cliente = cadastra_cliente(lst_cliente,cliente);
	lst_cliente = cadastra_cliente(lst_cliente,cliente2);
	lst_cliente = cadastra_cliente(lst_cliente,cliente3);
	
	for(lCliente *iter=lst_cliente; iter != NULL; iter=iter->prox){
		printf("%s\n",iter->cliente->nomeCliente);
	}
	
	printf("Nome: %s\n",lst_cliente->cliente->nomeCliente);
}

void testa_cadastro_pagamentos(){
	lst_pagamentos = cria_lista_de_pagamentos();
	
	Pagamento *pagamento = cria_pagamento();
	pagamento->data_pagamento->dia = 20;
	pagamento->data_pagamento->mes = 06;
	pagamento->data_pagamento->ano = 2017;
	
	pagamento->cliente = lst_cliente->cliente;
	pagamento->status = DEVENDO;
	pagamento->valor = 30;
	
	Pagamento *pagamento2 = cria_pagamento();
	pagamento2->data_pagamento->dia = 30;
	pagamento2->data_pagamento->mes = 06;
	pagamento2->data_pagamento->ano = 2017;
	
	pagamento2->cliente = lst_cliente->prox->cliente;
	pagamento2->status = DEVENDO;
	pagamento2->valor = 30;
	
	lst_pagamentos = cadastra_pagamento(lst_pagamentos,pagamento);
	lst_pagamentos = cadastra_pagamento(lst_pagamentos,pagamento2);
	
	printf("%d/%d/%d\n",lst_pagamentos->pagamento->data_pagamento->dia,lst_pagamentos->pagamento->data_pagamento->mes,lst_pagamentos->pagamento->data_pagamento->ano);
}
																			 
void testa_busca_pagamentos(){
	printf("=========================================\n");
	Pagamento *pagamento = busca_de_pagamento(lst_pagamentos,lst_cliente->cliente->CPF);
	if((pagamento != NULL) && (pagamento->data_pagamento->dia == 20)){
		printf("Teste de busca efetuado com sucesso!\n");
	} else {
		printf("Falha no teste de busca!!\n"); 
	}
}

void testa_edicao_pagamentos(){
	printf("=========================================\n");
	Pagamento *pagamento = busca_de_pagamento(lst_pagamentos,lst_cliente->cliente->CPF);
	printf("Status atual: %s\n",(pagamento->status == 0) ? "Pago" : "Devendo");
	pagamento->status = PAGO;
	edita_pagamento(lst_pagamentos,pagamento,pagamento->cliente->CPF);
	pagamento = busca_de_pagamento(lst_pagamentos,lst_cliente->cliente->CPF);
	printf("Status modificado: %s\n",(pagamento->status == 0) ? "Pago" : "Devendo");
}

void testa_visualiza_pagamento(){
	printf("=========================================\n");
	Pagamento *pagamento = lst_pagamentos->pagamento;
	printf("%s\n",pagamento->cliente->nomeCliente);
	printf("R$%2.2f\n",pagamento->valor);
	printf("%2d/%2d/%4d\n",pagamento->data_pagamento->dia,pagamento->data_pagamento->mes,pagamento->data_pagamento->ano);
	printf("Status atual: %s\n",(pagamento->status == 0) ? "Pago" : "Devendo");
}

void testa_deleta_pagamento(){
	printf("=========================================\n");
	printf("Visualização atual:\n");
	testa_visualiza_pagamento();
	printf("Apagando pagamentos...\n");
	Pagamento *pagamento = lst_pagamentos->pagamento;
	lst_pagamentos = deleta_pagamento(lst_pagamentos,pagamento->cliente->CPF);
	printf("Visualização modificada:\n");
	testa_visualiza_pagamento();
}

void testa_salvar_pagamentos_em_arquivo(){
	FILE *arq;
	arq = fopen("dadospagamentos.txt", "w");
	if(arq == NULL){
		printf("ERRO EM ABRIR O ARQUIVO\n");
	}
	
	salvar_pagamentos_em_arquivo(lst_pagamentos, arq);
	
	fclose(arq);
}
