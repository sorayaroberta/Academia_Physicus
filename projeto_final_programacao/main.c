#include <stdio.h>
#include <stdlib.h>
#include "menus.h"
#include "cliente.h"
#include "persistencia_cliente.h"
#include "pagamento.h"
#include "persistencia_pagamento.h"

#define REMOCAO_COM_SUCESSO 0

/***********LISTAS***********/
lCliente *lst_clientes;
lPagamento *lst_pagamentos;
/***************************/

/*******CARREGA DADOS*******/
void carrega_clientes();
void carrega_pagamentos();
/***************************/

/*******SALVA DADOS*******/
void salva_clientes();                         
void salva_pagamentos();
/***************************/

/***********MENUS***********/
void principal();
void area_cliente();
void area_relatorios();
void area_pagamentos();
/***************************/

/******AREA DO CLIENTE******/
void cliente_cadastro();
void cliente_visualiza();
void cliente_edicao();
void cliente_remocao();
/***************************/

/*****AREA DE PAGAMENTOS****/
void pagamentos_cadastro();
void pagamentos_edicao();
/***************************/

int main(int argc, char **argv){
	carrega_clientes();
	carrega_pagamentos();
	principal();
	return 0;
}

void principal(){
	int opcao_menu;
	do{
		menu_principal();
	
		printf("Informe a opção desejada: ");
		scanf("%d",&opcao_menu);
		
		switch(opcao_menu){
			case MENU_PRINCIPAL_CLIENTE:
			area_cliente();
			break;
			
			case MENU_PRINCIPAL_PAGAMENTO:
			area_pagamentos();
			break;
			
			case MENU_PRINCIPAL_RELATORIOS:
			area_relatorios();
			break;
			
			case MENU_PRINCIPAL_SAIR:
			salva_clientes();
			salva_pagamentos();
			printf("\n\nAté logo\n\n");
			break;
			
			default:
			printf("Opção Inválida!\n");
			break;
		}
	} while(opcao_menu != MENU_PRINCIPAL_SAIR);
}

void area_cliente(){
	int opcao_menu;
	do{
		menu_cliente();
		
		printf("Informe a opção desejada: ");
		scanf("%d",&opcao_menu);
		getchar();
		
		switch(opcao_menu){
			case MENU_CLIENTE_CADASTRAR:
			cliente_cadastro();
			break;
			
			case MENU_CLIENTE_EDITAR:
			cliente_edicao();
			break;
			
			case MENU_CLIENTE_REMOVER:
			cliente_remocao();
			break;
			
			case MENU_CLIENTE_VISUALIZAR:
			cliente_visualiza();
			break;
			
			case MENU_CLIENTE_VOLTAR:
			break;
			
			default:
			printf("Opção Inválida!\n");
			break;
		}
	} while(opcao_menu != MENU_CLIENTE_VOLTAR);
}

void area_pagamentos(){
	int opcao_menu;
	do{
		menu_pagamentos();
		
		printf("Informe a opção desejada: ");
		scanf("%d",&opcao_menu);
		getchar();
		
		switch(opcao_menu){
			case MENU_PAGAMENTOS_CADASTRAR:
			pagamentos_cadastro();
			break;
			
			case MENU_PAGAMENTOS_EDITAR:
			pagamentos_edicao();
			break;
			
			case MENU_PAGAMENTOS_VOLTAR:
			break;
			
			default:
			printf("Opção Inválida!\n");
			break;
		}
	} while(opcao_menu != MENU_PAGAMENTOS_VOLTAR);
}

void area_relatorios(){
	int mes, ano;
	printf("Informe o mês: ");
	fscanf(stdin,"%d",&mes);
	getchar();
	printf("Informe o ano: ");
	fscanf(stdin,"%d",&ano); 
	getchar();
	
	Pagamento *pagamento;
	Cliente *cliente;
	
	float lucro = 0;	
	for(lPagamento *iterador = lst_pagamentos; (iterador != NULL) && (iterador->pagamento != NULL); iterador = iterador->prox){
		pagamento = iterador->pagamento;
		cliente = pagamento->cliente;
		
		if((pagamento != NULL) && ((pagamento->data_pagamento->mes == mes) && (pagamento->data_pagamento->ano == ano))){
			if((cliente != NULL)){
				printf("%s está %s esse mês\n",cliente->nomeCliente,(pagamento->status == PAGO) ? "quite" : "em débito");
				if(pagamento->status == PAGO){
					lucro += pagamento->valor;
				}
			}
		}
	}
	
	printf("Este mẽs você conseguiu arrecadar R$%2.2f reais.\n",lucro);
}

void cliente_cadastro(){
	/*char nomeCliente[50];
	int idade;
	char sexo;
	long long int CPF;
	char rua[40];
	int numeroHome;
	char cidade[40];
	int telefone;*/
	
	Cliente *cliente = (Cliente*) malloc(sizeof(Cliente));
	
	printf("===CADASTRO DE CLIENTES===\n");
	printf("Nome: ");
	fscanf(stdin,"%[^\n]",cliente->nomeCliente);
	getchar();                        
	printf("Idade: ");
	fscanf(stdin,"%d",&cliente->idade);
	getchar();
	printf("Sexo: ");
	fscanf(stdin,"%c",&cliente->sexo);
	getchar();
	printf("CPF: ");
	fscanf(stdin,"%lld",&cliente->CPF);
	getchar();
	printf("Rua: ");
	fscanf(stdin,"%[^\n]",cliente->rua);
	getchar();
	printf("Número da casa: ");                                   
	fscanf(stdin,"%d",&cliente->numeroHome);
	getchar();
	printf("Cidade: ");
	fscanf(stdin,"%[^\n]",cliente->cidade);
	getchar();
	printf("Telefone: ");
	fscanf(stdin,"%d",&cliente->telefone);
	getchar();
	
	lst_clientes = cadastra_cliente(lst_clientes,cliente);
	printf("Cliente cadastrado com sucesso!\n");
}

void cliente_visualiza(){
	printf("===VISUALIZA CLIENTES===\n");
	
	long long int CPF;
	printf("Informe o CPF que você deseja visualizar:");
	scanf("%lld",&CPF);
	
	Cliente *cliente = busca_de_cliente(lst_clientes,CPF);
	
	if(cliente == NULL){
		printf("Nenhum cliente cadastrado tem o CPF informado.\n");
	} else {
		printf("%s\n",cliente->nomeCliente);
		printf("%d anos\n",cliente->idade);
		printf("Sexo: %c\n",cliente->sexo);
		printf("CPF: %lld\n",cliente->CPF);
		printf("Mora em: %s, número %d\n",cliente->rua,cliente->numeroHome);
		printf("Cidade: %s\n",cliente->cidade);
		printf("Telefone: %d\n",cliente->telefone);
	}
}
void cliente_edicao(){
	printf("===EDITA CLIENTE===\n");
	
	long long int CPF;
	printf("Informe o CPF do usuário que você deseja editar:");
	fscanf(stdin,"%lld",&CPF);
	getchar();
	
	Cliente *cliente_para_editar = busca_de_cliente(lst_clientes,CPF);
	
	if(cliente_para_editar != NULL){
		printf("Editar nome do cliente: ");
		fscanf(stdin,"%[^\n]",cliente_para_editar->nomeCliente);
		getchar();
		printf("Editar idade: ");
		fscanf(stdin,"%d",&cliente_para_editar->idade);
		getchar();
		printf("Editar sexo: ");
		fscanf(stdin,"%c",&cliente_para_editar->sexo);
		getchar();
		printf("Editar Rua: ");
		fscanf(stdin,"%[^\n]",cliente_para_editar->rua);
		getchar();
		printf("Editar número da casa: ");
		fscanf(stdin,"%d",&cliente_para_editar->numeroHome);
		getchar();
		printf("Editar cidade: ");
		fscanf(stdin,"%[^\n]",cliente_para_editar->cidade);
		getchar();
		printf("Editar telefone: ");
		fscanf(stdin,"%d",&cliente_para_editar->telefone);
		getchar();
		
		edita_cliente(lst_clientes,cliente_para_editar,CPF);
		printf("Cliente editado com sucesso!\n");
	} else {
		printf("Não foi encontrado com CPF %lld!\n",&CPF);
	}
}
void cliente_remocao(){
	printf("===REMOVE DE CLIENTES===\n");

	long long int CPF;
	printf("Informe o CPF do usuário que você deseja excluir:");
	fscanf(stdin,"%lld",&CPF);
	getchar();
	Cliente *cliente_para_excluir = busca_de_cliente(lst_clientes,CPF);
	
	if(cliente_para_excluir == NULL){
		printf("Cliente não encontrado!!");
		return;
	}
	
	printf("Tem certeza que você deseja excluir %s que tem o CPF %lld [S/N]?",cliente_para_excluir->nomeCliente,cliente_para_excluir->CPF);
	char resposta ;
	scanf("%c",&resposta);
	if((resposta == 'S') || (resposta == 's')){
		lst_clientes = deleta_cliente(lst_clientes,CPF);
		printf("Cliente apagado com sucesso!");
	}
}

void pagamentos_cadastro(){
	Pagamento *pagamento = cria_pagamento();
	printf("Informe o dia:");
	fscanf(stdin,"%d",&pagamento->data_pagamento->dia);
	getchar();
	printf("Informe o mes:");
	fscanf(stdin,"%d",&pagamento->data_pagamento->mes);
	getchar();
	printf("Informe o ano:");
	fscanf(stdin,"%d",&pagamento->data_pagamento->ano);
	getchar();
	printf("Informe o valor:");
	fscanf(stdin,"%f",&pagamento->valor);
	getchar();
	printf("Informe o CPF do cliente:");
	long long int CPF;
	fscanf(stdin,"%lld",&CPF);
	getchar();
	pagamento->cliente = busca_de_cliente(lst_clientes,CPF);
	printf("O cliente pagou [S/N]? ");
	char pagou;
	fscanf(stdin,"%c",&pagou);
	getchar();
	if(pagou == 'S'){
		pagamento->status = PAGO;
	} else {
		pagamento->status = DEVENDO;
	}
	lst_pagamentos = cadastra_pagamento(lst_pagamentos,pagamento);
	
	printf("Pagamento registrado com sucesso!\n");
}

void pagamentos_edicao(){
	printf("===EDITA PAGAMENTO===\n");
	
	long long int CPF;
	printf("Informe o CPF do usuário que você deseja editar:");
	fscanf(stdin,"%lld",&CPF);
	getchar();
	
	Pagamento *pagamento_para_editar = busca_de_pagamento(lst_pagamentos,CPF);
	
	if(pagamento_para_editar != NULL){
		printf("Editar o dia do pagamento: ");
		fscanf(stdin,"%d",&pagamento_para_editar->data_pagamento->dia);
		getchar();
		printf("Editar o mês do pagamento: ");
		fscanf(stdin,"%d",&pagamento_para_editar->data_pagamento->mes);
		getchar();
		printf("Editar o ano do pagamento: ");
		fscanf(stdin,"%d",&pagamento_para_editar->data_pagamento->ano);
		getchar();
		printf("Editar o status do pagamento [P - Pago | D - Devendo]: ");
		char status;
		fscanf(stdin,"%c",&status);
		getchar();
		if(status == 'P'){
			pagamento_para_editar->status = PAGO;
		} else if(status == 'D'){
			pagamento_para_editar->status = DEVENDO;
		}
		
		edita_pagamento(lst_pagamentos,pagamento_para_editar,CPF);
		printf("Pagamento editado com sucesso!\n");
	} else {
		printf("Não foi encontrado pagamento associado a cliente com CPF %lld!\n",&CPF);
	}
}

void carrega_clientes(){
	FILE *arq;
	arq = fopen("dadosclientes.txt", "rw+");
	
	if(arq == NULL){
		arq = fopen("dadosclientes.txt", "rwa+");
	}
	
	lst_clientes = carregar_arquivo_clientes(arq);
	fclose(arq);
	int resultado_da_remocao = remove("dadosclientes.txt");
	/*if(resultado_da_remocao != REMOCAO_COM_SUCESSO){
		printf("Não foi possível remover o arquivo de clientes\n");
		exit(1);
	}*/
}

void carrega_pagamentos(){
	FILE *arq;
	arq = fopen("dadospagamentos.txt", "rw+");
	
	if(arq == NULL){
		arq = fopen("dadospagamentos.txt", "rwa+");
	}
	
	lst_pagamentos = carregar_arquivo_pagamentos(arq,lst_clientes);
	fclose(arq);
	int resultado_da_remocao = remove("dadospagamentos.txt");
	/*if(resultado_da_remocao != REMOCAO_COM_SUCESSO){
		printf("Não foi possível remover o arquivo de pagamentos\n");
		exit(1);
	}*/
}

void salva_clientes(){
	printf("Salvando os dados dos clientes em arquivo...\n");
	FILE *arq;
	arq = fopen("dadosclientes.txt", "w");
	if(arq == NULL){
		printf("ERRO EM ABRIR O ARQUIVO\n");
	}
	
	salvar_clientes_em_arquivo(lst_clientes, arq);
	
	fclose(arq);
}

void salva_pagamentos(){
	printf("Salvando os dados dos pagamentos em arquivo...\n");
	FILE *arq;
	arq = fopen("dadospagamentos.txt", "w");
	if(arq == NULL){
		printf("ERRO EM ABRIR O ARQUIVO\n");
	}
	
	salvar_pagamentos_em_arquivo(lst_pagamentos, arq);
	
	fclose(arq);
}
