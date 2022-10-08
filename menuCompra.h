#ifndef MENUCOMPRA_H_INCLUDED
#define MENUCOMPRA_H_INCLUDED
#include "carrinho.h"
void mCompra();
void finalizaCompra(FILE *arqForn,FILE *arqProduto,carrinho carrinhoCompra,unsigned long idForn);
void criaItensNotaCompra(carrinho carrinhoCompra,unsigned long idNotaCompra,FILE *arqItemNotaCompra,FILE *fProduto);
#endif // MENUCOMPRA_H_INCLUDED
