#ifndef __PAGAMENTO_H__
#define __PAGAMENTO_H__

#include "cliente.h"

// Define os possíveis status de um pagamento
#define PAGO 0
#define DEVENDO 1

typedef struct data{
	int dia;
	int mes;
	int ano;
} Data;

//Gera o tipo de dados para cadastro do pagamento
typedef struct Pagamento {
  Data *data_pagamento;
  Cliente *cliente;
  int status;
  float valor; 
} Pagamento;

//gera o tipo de dados para guardar todos os Pagamentos cadastrados
typedef struct lPagamento {
	Pagamento *pagamento;
	struct lPagamento *prox;
} lPagamento;

//Assinaturas
Pagamento* cria_pagamento();
lPagamento* cria_lista_de_pagamentos();
lPagamento* cadastra_pagamento(lPagamento *lst, Pagamento *pagamento);// define a sssinatura do método cadastra Pagamento
Pagamento* busca_de_pagamento(lPagamento *lst,long long int CPF);//busca pelo CPF e retorna da lista Pagamento qual Pagamento está associado aquele valor
void edita_pagamento(lPagamento *lst, Pagamento *pagamento, long long int CPF);//este ultimo paramento vai guardar o CPF original antes de possivelmente ser editado
void visualiza_pagamento(Pagamento *pagamento);
lPagamento* deleta_pagamento(lPagamento *lst,long long int CPF);

#endif
