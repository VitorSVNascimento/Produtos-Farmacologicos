#ifndef ITEMNOTAFISCAL_H_INCLUDED
#define ITEMNOTAFISCAL_H_INCLUDED
#include <stdio.h>
typedef struct ItemNotaFiscal *TItemNotaFiscal;

unsigned long getIdItemNotaFiscal(TItemNotaFiscal item);
void setIdItemNotaFiscal(TItemNotaFiscal item, unsigned long id);
unsigned long getIdProdutoItemNotaFiscal(TItemNotaFiscal item);
void setIdProdutoItemNotaFiscal(TItemNotaFiscal item, unsigned long id);
unsigned long getIdNotaFiscalItemNotaFiscal(TItemNotaFiscal item);
void setIdNotaFiscalItemNotaFiscal(TItemNotaFiscal item, unsigned long id);
unsigned int getQuantidadeItemNotaFiscal(TItemNotaFiscal item);
void setQuantidadeItemNotaFiscal(TItemNotaFiscal item, unsigned long qtde);
float getValorVendaItemNotaFiscal(TItemNotaFiscal item);
void setValorVendaItemNotaFiscal(TItemNotaFiscal item, float valor);
int tamStructItemNotaFiscal();
TItemNotaFiscal novoItemNotaFiscal();
void liberaItemNotaFiscal(TItemNotaFiscal item);
void inicializarItemNotaFiscal(TItemNotaFiscal item,unsigned long id,unsigned long idProduto,unsigned long idNotaFiscal,unsigned int qtde, float valorVenda);
unsigned long novoIdItemNotaFiscal(FILE *f);
#endif