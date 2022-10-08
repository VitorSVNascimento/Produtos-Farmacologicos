#ifndef MENUPRODUTO_H_INCLUDED
#define MENUPRODUTO_H_INCLUDED
#include "produto.h"
void mProduto();
void cadastrarProduto(FILE *f);
void alteraProduto(FILE *f);
void consultaProduto(FILE *f);
void printaDadosProduto(TProduto produto);
void listaTodosProduto(FILE *arq);
void listaProdutosEmEstoque(FILE *arq);
void menuExcluirProduto(FILE *f);

#endif // MENUPRODUTO_H_INCLUDED
