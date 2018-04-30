#include "persistencia_cliente.h"
#include <stdlib.h>
#include <string.h>

void salvar_cliente_em_arquivo(Cliente *cliente,FILE *arquivo){
	fprintf(arquivo,"%s#",cliente->nomeCliente);
	fprintf(arquivo,"%d#",cliente->idade);
	fprintf(arquivo,"%c#",cliente->sexo);
	fprintf(arquivo,"%lld#",cliente->CPF);
	fprintf(arquivo,"%s#",cliente->rua);
	fprintf(arquivo,"%d#",cliente->numeroHome);
	fprintf(arquivo,"%s#",cliente->cidade);
	fprintf(arquivo,"%d\n",cliente->telefone);
}

void salvar_clientes_em_arquivo(lCliente *lista_clientes,FILE *arquivo){
	for(lCliente *iter = lista_clientes; iter != NULL; iter=iter->prox){
		if(iter->cliente != NULL){
			salvar_cliente_em_arquivo(iter->cliente,arquivo);
		}
	}
}

lCliente* carregar_arquivo_clientes(FILE *arquivo){
	lCliente* lst_cliente = cria_lista_de_clientes();
	Cliente* cliente;
	
	char nomeCliente[50];
	int idade;
	char sexo;
	long long int CPF;
	char rua[40];
	int numeroHome;
	char cidade[40];
	int telefone;
	
	while( (fscanf(arquivo,"%[^#]#%d#%c#%lld#%[^#]#%d#%[^#]#%d\n", nomeCliente, &idade, &sexo, &CPF, rua, &numeroHome, cidade, &telefone))!=EOF ){
		cliente = (Cliente*) malloc(sizeof(Cliente));
		strcpy(cliente->nomeCliente,nomeCliente);
		cliente->idade = idade;
		cliente->sexo = sexo;
		cliente->CPF = CPF;
		strcpy(cliente->rua,rua);
		strcpy(cliente->cidade,cidade);
		cliente->telefone = telefone;
		lst_cliente = cadastra_cliente(lst_cliente,cliente);
	}
	
	return lst_cliente;
}



/*
 * char nomeCliente[50];
  int idade;
  char sexo;
  long long int CPF;
  char rua[40];
  int numeroHome;
  char cidade[40];
  int telefone;*/
//void apagar_em_arquivo(Cliente* cliente,FILE *arquivo);

