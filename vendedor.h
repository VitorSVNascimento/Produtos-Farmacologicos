#ifndef VENDEDOR_H_INCLUDED
#define VENDEDOR_H_INCLUDED
#include <stdio.h>
typedef struct Vendedor *TVendedor;

// Getters e Seters
unsigned long getIdVendedor(TVendedor vendedor);
void setIdVendedor(TVendedor vendedor, unsigned long id);
void getNomeVendedor(TVendedor vendedor, char *nome);
void setNomeVendedor(TVendedor vendedor, char *nome);
void getCpfVendedor(TVendedor vendedor, char *cpf);
void setCpfVendedor(TVendedor vendedor, char *cpf);
void getEmailVendedor(TVendedor vendedor, char *email);
void setEmailVendedor(TVendedor vendedor, char *email);
void getTelefoneVendedor(TVendedor vendedor, char *telefone);
void setTelefoneVendedor(TVendedor vendedor, char *telefone);
void getPasswordVendedor(TVendedor vendedor, char *password);
void setPasswordVendedor(TVendedor vendedor, char *password);

/*
    ALOCA MEMÓRIA PARA REGISTRAR UM NOVO VENDEDOR
    PARAMETROS: ()
    RETORNOS: RETORNA UM TVENDEDOR CASO CONSIGA ALOCA E NULL CASO FALHAR
*/
TVendedor novoVendedor();
int tamStructVendedor();
void liberaVendedor(TVendedor vendedor);

/*
    INICIALIZA OS CAMPOS DA STRUCT DE ACORDO COM OS PARAMETROS PASSADOS
    PARAMETROS: vendedor (vendedor onde os dados serão atribuidos),nome(nome do vendedor),cpf(cpf do vendedor),email(email do vendedor)
    ,telefone(telefone do vendedor)
    RETORNOS: VOID
*/
void inicializarVendedor(TVendedor vendedor,unsigned long id,char *nome,char *cpf, char *email, char *telefone, char *password);

void inserirVendedorNaPosicao(TVendedor vendedor,FILE *arq,unsigned long posicao);
unsigned long novoIdVendedor(FILE *f);

unsigned long buscaCpfVendedor(char *cpf,FILE *f);
unsigned long buscaEmailVendedor(char *email,FILE *f);
unsigned long buscaIdVendedor(unsigned long id,FILE *file);
unsigned long buscaPrefixoVendedor(char *pre,FILE *file,unsigned long posInicial);
void excluirVendedor(TVendedor v,FILE *f,unsigned long posicao);

void atribuirDadosVendedor(TVendedor v,unsigned long posicao,FILE *f);
unsigned long registroValidosVendedor(FILE *f);
int validaSenha(FILE *f,unsigned long posicao,char *senha);



#endif // VENDEDOR_H_INCLUDED
