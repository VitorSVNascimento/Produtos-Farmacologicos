#ifndef FORNECEDOR_H_INCLUDED
#define FORNECEDOR_H_INCLUDED
#include <stdio.h>
typedef struct Fornecedor *TFornecedor;

// Getters e Seters
unsigned long getIdFornecedor(TFornecedor fornecedor);
void setIdFornecedor(TFornecedor fornecedor, unsigned long id);
void getNomeFornecedor(TFornecedor fornecedor, char *nome);
void setNomeFornecedor(TFornecedor fornecedor, char *nome);
void getCnpjFornecedor(TFornecedor fornecedor, char *cnpj);
void setCnpjFornecedor(TFornecedor fornecedor, char *cnpj);
void getEmailFornecedor(TFornecedor fornecedor, char *email);
void setEmailFornecedor(TFornecedor fornecedor, char *email);
void getTelefoneFornecedor(TFornecedor fornecedor, char *telefone);
void setTelefoneFornecedor(TFornecedor fornecedor, char *telefone);


TFornecedor novoFornecedor();
int tamStructFornecedor();
void liberaFornecedor(TFornecedor fornecedor);

void inicializarFornecedor(TFornecedor fornecedor,unsigned long id,char *nome,char *cnpj, char *email, char *telefone);

void inserirFornecedorNaPosicao(TFornecedor fornecedor,FILE *arq,unsigned long posicao);
unsigned long novoIdFornecedor(FILE *f);

unsigned long buscaCnpjFornecedor(char *cnpj,FILE *f);
unsigned long buscaNomeFornecedor(char *nome,FILE *f);
unsigned long buscaIdFornecedor(unsigned long id,FILE *file);
unsigned long buscaPrefixoFornecedor(char *pre,FILE *file,unsigned long posInicial);
void excluirFornecedor(TFornecedor fornecedor,FILE *f,unsigned long posicao);

void atribuirDadosFornecedor(TFornecedor fornecedor,unsigned long posicao,FILE *f);
unsigned long registroValidosFornecedor(FILE *f);
#endif // FORNECEDOR_H_INCLUDED
