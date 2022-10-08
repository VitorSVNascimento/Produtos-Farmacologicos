#ifndef ITEMNOTACOMPRA_H_INCLUDED
#define ITEMNOTACOMPRA_H_INCLUDED
#include <stdio.h>
typedef struct ItemNotaCompra *TItemNotaCompra;

unsigned long getIdItemNotaCompra(TItemNotaCompra item);
void setIdItemNotaCompra(TItemNotaCompra item, unsigned long id);
unsigned long getIdProdutoItem(TItemNotaCompra item);
void setIdProdutoItem(TItemNotaCompra item, unsigned long id);
unsigned long getIdNotaCompraItem(TItemNotaCompra item);
void setIdNotaCompraItem(TItemNotaCompra item, unsigned long id);
unsigned int getQuantidadeItemNotaCompra(TItemNotaCompra item);
void setQuantidadeItemNotaCompra(TItemNotaCompra item, unsigned long qtde);
float getValorUnitarioItemNotaCompra(TItemNotaCompra item);
void setValorUnitarioItemNotaCompra(TItemNotaCompra item, float valor);
int tamStructItemNotaCompra();
TItemNotaCompra novoItemNotaCompra();
void liberaItemNotaCompra(TItemNotaCompra item);
void inicializarItemNotaCompra(TItemNotaCompra item,unsigned long id,unsigned long idProduto,unsigned long idNotaCompra,unsigned int qtde, float valorUnitario);
unsigned long novoIdItemNotaCompra(FILE *f);

#endif // ITEMNOTACOMPRA_H_INCLUDED
