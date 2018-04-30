//Arquivo para implementar as funções
#include "cliente.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
//Cria lista de varios clientes
lCliente* cria_lista_de_clientes(){
	lCliente *lista_clientes = (lCliente*) malloc(sizeof(lCliente));
	lista_clientes->cliente=NULL;
	lista_clientes->prox=NULL;
	return lista_clientes;
}

lCliente* cadastra_cliente(lCliente *lst, Cliente *cliente){
	lCliente *lista = cria_lista_de_clientes();
	lista->cliente = cliente;
	lista->prox = lst;
	return lista;
}

Cliente* busca_de_cliente(lCliente *lst,long long int CPF){
	lCliente *inicializa;
	for(inicializa=lst; (inicializa!= NULL) && (inicializa->cliente != NULL);inicializa=inicializa->prox){
		if(inicializa->cliente->CPF==CPF){
			return inicializa->cliente;
		}	
	}
	return NULL;
}

void edita_cliente(lCliente *lst, Cliente *cliente, long long int CPF)
{
	Cliente *cliente_para_editar = busca_de_cliente(lst,CPF);
	if(cliente_para_editar != NULL){
		strcpy(cliente_para_editar->nomeCliente,cliente->nomeCliente);
		cliente_para_editar->idade = cliente->idade;
		cliente_para_editar->sexo = cliente->sexo;
		cliente_para_editar->CPF = cliente->CPF;
		strcpy(cliente_para_editar->rua,cliente->rua);
		cliente_para_editar->numeroHome = cliente->numeroHome;
		strcpy(cliente_para_editar->cidade,cliente->cidade);
		cliente_para_editar->telefone = cliente->telefone;
	}
}

void visualiza_cliente(Cliente *cliente){
	printf("#########################\n");
	printf("Dados pessoais do cliente\n");
	printf("Nome do cliente: %s\n",cliente->nomeCliente);
	printf("Idade: %d\n",cliente->idade);
	printf("Sexo: %c\n",cliente->sexo);
	printf("CPF: %lld\n",cliente->CPF);
	printf("Rua: %s\n",cliente->rua);
	printf("Número da casa: %d\n",cliente->numeroHome);
	printf("Cidade: %s\n",cliente->cidade);
	printf("Telefone: %d\n",cliente->telefone);
	printf("#########################\n");
}
lCliente* deleta_cliente(lCliente *lst,long long int CPF){
	lCliente *iterador;
	if(lst == NULL)//verificar se a lista ta vazia para
		return lst;
	
	for(iterador = lst;iterador != NULL;iterador = iterador->prox){
		if(iterador->cliente->CPF == CPF){
			lst=iterador->prox;
			break;
		} else if((iterador->prox != NULL) && (iterador->prox->cliente != NULL) && (iterador->prox->cliente->CPF==CPF)){
			iterador->prox = iterador->prox->prox;
			break;
		}
	}
	
	return lst;
}
