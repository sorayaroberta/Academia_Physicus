#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "persistencia_cliente.h"

#define REMOCAO_COM_SUCESSO 0 // "Label" para simbolizar que a remoção ocorreu com sucesso

void testa_cadastro_cliente();
void testa_busca_clientes();
void testa_edita_clientes();
void testa_visualiza_clientes();
void testa_deleta_clientes();
void testa_carrega_arquivo();
void testa_salvar_em_arquivo();

lCliente* lst_cliente;

int frida()
//int main(int argc, char **argv)
{
	//testa_carrega_arquivo();
	testa_cadastro_cliente();
	testa_salvar_em_arquivo();
	//testa_busca_clientes();
	//testa_edita_clientes();
	//testa_visualiza_clientes();
	//testa_deleta_clientes();
	return 0;
}

void testa_cadastro_cliente(){
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

void testa_busca_clientes(){
	long long int CPF = 12345678902;
	Cliente* resultado;
	
	resultado = busca_de_cliente(lst_cliente,CPF);
	if(resultado != NULL){
		printf("Achou! É %s\n",resultado->nomeCliente);
	} else {
		printf("Num achou!");
	}
	
	CPF = 12345678901;
	resultado = busca_de_cliente(lst_cliente,CPF);
	if(resultado != NULL){
		printf("Achou! É %s\n",resultado->nomeCliente);
	} else {
		printf("Num achou!");
	}
}

void testa_edita_clientes(){
	long long int CPF = 12345678902;
	Cliente* resultado;
	
	resultado = busca_de_cliente(lst_cliente,CPF);
	printf("Antigo nome: %s\n",resultado->nomeCliente);
	strcpy(resultado->nomeCliente,"pedrota");
	edita_cliente(lst_cliente,resultado,CPF);
	resultado = busca_de_cliente(lst_cliente,CPF);
	printf("Novo nome: %s\n",resultado->nomeCliente);
}

void testa_visualiza_clientes(){
	for(lCliente *iter=lst_cliente; iter != NULL; iter=iter->prox){
		if(iter->cliente != NULL){
			visualiza_cliente(iter->cliente);
		}
	}
}

void testa_deleta_clientes(){
	printf("\n\n\n\n\nApagando...");
	
	long long int CPF = 12345678902;
	lst_cliente = deleta_cliente(lst_cliente,CPF);
	
	CPF = 2365423145;
	lst_cliente = deleta_cliente(lst_cliente,CPF);
	
	testa_visualiza_clientes();
}

void testa_salvar_em_arquivo(){
	FILE *arq;
	arq = fopen("dadosclientes.txt", "w");
	if(arq == NULL){
		printf("ERRO EM ABRIR O ARQUIVO\n");
	}
	
	salvar_clientes_em_arquivo(lst_cliente, arq);
	
	fclose(arq);
}
					
void testa_carrega_arquivo(){
	FILE *arq;
	arq = fopen("dadosclientes.txt", "r");
	lst_cliente = carregar_arquivo_clientes(arq);
	testa_visualiza_clientes();
	fclose(arq);
	int resultado_da_remocao = remove("dadosclientes.txt");
	if(resultado_da_remocao == REMOCAO_COM_SUCESSO){
		printf("Arquivo carregado e removido com sucesso!\n");
	} else {
		printf("Ige boy, num deu pra remover o arquivo nããoo...\n");
	}
}
