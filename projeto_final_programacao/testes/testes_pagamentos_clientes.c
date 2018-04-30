#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "persistencia_cliente.h"
#include "pagamento.h"
#include "persistencia_pagamento.h"

#define REMOCAO_COM_SUCESSO 0 // "Label" para simbolizar que a remoção ocorreu com sucesso

void carrega_clientes();
void carrega_pagamentos();
void visualiza_pagamentos_carregados();

lCliente *lst_clientes;
lPagamento *lst_pagamentos;

//int main(int argc, char **argv){
int ronaldita(){
	carrega_clientes();
	carrega_pagamentos();
	visualiza_pagamentos_carregados();
	return 0;
}

void carrega_clientes(){
	FILE *arq;
	arq = fopen("dadosclientes.txt", "r");
	lst_clientes = carregar_arquivo_clientes(arq);
	fclose(arq);
	int resultado_da_remocao = remove("dadosclientes.txt");
	if(resultado_da_remocao == REMOCAO_COM_SUCESSO){
		printf("Arquivo carregado e removido com sucesso!\n");
	} else {
		printf("Ige boy, num deu pra remover o arquivo nããoo...\n");
	}
}
void carrega_pagamentos(){
	FILE *arq;
	arq = fopen("dadospagamentos.txt", "r");
	lst_pagamentos = carregar_arquivo_pagamentos(arq,lst_clientes);
	fclose(arq);
	int resultado_da_remocao = remove("dadospagamentos.txt");
	if(resultado_da_remocao == REMOCAO_COM_SUCESSO){
		printf("Arquivo carregado e removido com sucesso!\n");
	} else {
		printf("Ige boy, num deu pra remover o arquivo de pagamentos nããoo...\n");
	}
}

void visualiza_pagamentos_carregados(){
	for(lPagamento *iterador = lst_pagamentos; (iterador != NULL) && (iterador->pagamento != NULL); iterador = iterador->prox){
		visualiza_pagamento(iterador->pagamento);
		printf("=====================\n");
	}
}
