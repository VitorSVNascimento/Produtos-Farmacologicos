#ifndef MENUVENDA_H_INCLUDED
#define MENUVENDA_H_INCLUDED
#define SUCESSO_AUTENTICACAO 1
#define FALHA_AUTENTICACAO 0
#include <stdio.h>
#include "carrinho.h"

void mVenda();
int autenticaVendedor(FILE *fVendedor,unsigned long *idVend);
void finalizaVenda(FILE *arqVend,FILE *arqProduto,FILE *arqCliente,unsigned long idVend,unsigned long idCli,carrinho carrinhoVenda);
void criaItensNotaFiscal(carrinho carrinhoVenda,FILE *arqItemNotaFiscal,FILE *fProduto,unsigned long idVenda);
#endif