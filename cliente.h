#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED
#include <stdio.h>
//tamanhos utilizados para: NOME(100), EMAIL(50),CPF(12), TELEFONE(15);
typedef struct Cliente *TCliente;

// Getters e Seters
unsigned long getIdCliente(TCliente cliente);
void setIdCliente(TCliente cliente, unsigned long id);
void getNomeCliente(TCliente cliente, char *nome);
void setNomeCliente(TCliente cliente, char *nome);
void getCpfCliente(TCliente cliente, char *cpf);
void setCpfCliente(TCliente cliente, char *cpf);
void getEmailCliente(TCliente cliente, char *email);
void setEmailCliente(TCliente cliente, char *email);
void getTelefoneCliente(TCliente cliente, char *telefone);
void setTelefoneCliente(TCliente cliente, char *telefone);

/*
    ALOCA MEMÓRIA PARA REGISTRAR UM NOVO CLIENTE
    PARAMETROS: ()
    RETORNOS: RETORNA UM TCLIENTE CASO CONSIGA ALOCA E NULL CASO FALHAR
*/
TCliente novoCliente();
int tamStruct();
void liberaCliente(TCliente cliente);

/*
    INICIALIZA OS CAMPOS DA STRUCT DE ACORDO COM OS PARAMETROS PASSADOS
    PARAMETROS: cliente (cliente onde os dados serão atribuidos),nome(nome do cliente),cpf(cpf do cliente),email(email do cliente)
    ,telefone(telefone do cliente)
    RETORNOS: VOID
*/
void inicializarCliente(TCliente cliente,unsigned long id,char *nome,char *cpf, char *email, char *telefone);

/*
    insere um cliente na posição passada por parametro do arquivo passado por parametro
    parametros: cliente (struct do tipo Cliente), FILE *arq(arquivo onde o cliente será inserido), posicao( parte do arquivo em que será inserido o cliente)
*/
void inserirClienteNaPosicao(TCliente cliente,FILE *arq,unsigned long posicao);

/*
    gera um novo id para o cliente de maneira automatica 
    parametros: FILE *arq(arquivo onde os clientes estão gravados)
    retorna: o proximo id disponivel
*/
unsigned long novoIdCliente(FILE *f);

/*funções que buscam um cliente retornando a posição em que ele está no arquivo ou -1 caso contrario*/
unsigned long buscaCpfCliente(char *cpf,FILE *f);
unsigned long buscaIdCliente(unsigned long id,FILE *file);
unsigned long buscaPrefixoCliente(char *pre,FILE *file,unsigned long posInicial);
/*
    exclui um cliente do arquivo passado por parametro de maneira logica alterando seu id para 0
    parametros: cliente (struct do tipo Cliente), FILE *arq(arquivo onde o cliente será removido), posicao( parte do arquivo em que será removido o cliente)
*/
void excluirCliente(TCliente c,FILE *f,unsigned long posicao);
/*
    Atribui ao cliente passado por parametro os dados do cliente da posição passada por parametro 
*/
void atribuirDadosCliente(TCliente c,unsigned long posicao,FILE *f);
/*
    retorna o numero de clientes que possuem o id diferente de 0
*/
unsigned long registroValidos(FILE *f);
#endif // CLIENTE_H_INCLUDED
