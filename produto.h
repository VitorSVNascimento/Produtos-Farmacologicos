#ifndef PRODUTO_H_INCLUDED
#define PRODUTO_H_INCLUDED
#include <stdio.h>
typedef struct Produto *TProduto;

// Getters e Seters
unsigned long getIdProduto(TProduto produto);
void setIdProduto(TProduto produto, unsigned long id);
void getNomeProduto(TProduto produto, char *nome);
void setNomeProduto(TProduto produto, char *nome);
unsigned int getQtdeEstoqueProduto(TProduto produto);
void setQtdeEstoqueProduto(TProduto produto, unsigned int qtde);
float getPrecoUnitarioProduto(TProduto produto);
void setPrecoUnitarioProduto(TProduto produto, float precoUnitario);


TProduto novoProduto();
int tamStructProduto();
void liberaProduto(TProduto produto);

void inicializarProduto(TProduto produto,unsigned long id,char *nome,unsigned int quantidadeEstoque, float preco);

void inserirProdutoNaPosicao(TProduto produto,FILE *arq,unsigned long posicao);
unsigned long novoIdProduto(FILE *f);

unsigned long buscaIdProduto(unsigned long id,FILE *file);
unsigned long buscaPrefixoProduto(char *pre,FILE *file,unsigned long posInicial);
void excluirProduto(TProduto produto,FILE *f,unsigned long posicao);

void atribuirDadosProduto(TProduto produto,unsigned long posicao,FILE *f);
unsigned long registroValidosProduto(FILE *f);


#endif // PRODUTO_H_INCLUDED
