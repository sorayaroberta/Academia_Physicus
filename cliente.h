#ifndef __CLIENTE_H__
#define __CLIENTE_H__

#define APAGA 0
#define NAOAPAGA 1
//Gera o tipo de dados para cadastro do cliente
typedef struct Cliente {
  char nomeCliente[50];
  int idade;
  char sexo;
  long long int CPF;
  char rua[40];
  int numeroHome;
  char cidade[40];
  int telefone;
} Cliente;
//gera o tipo de dados para guardar todos os clientes cadastrados
typedef struct lCliente {
	Cliente *cliente;
	struct lCliente *prox;
} lCliente;

//Assinaturas
lCliente* cria_lista_de_clientes();
lCliente* cadastra_cliente(lCliente *lst, Cliente *cliente);// define a sssinatura do método cadastra cliente
Cliente* busca_de_cliente(lCliente *lst,long long int CPF);//busca pelo CPF e retorna da lista cliente qual cliente está associado aquele valor
void edita_cliente(lCliente *lst, Cliente *cliente, long long int CPF);//este ultimo paramento vai guardar o CPF original antes de possivelmente ser editado
void visualiza_cliente(Cliente *cliente);
lCliente* deleta_cliente(lCliente *lst,long long int CPF);

#endif
