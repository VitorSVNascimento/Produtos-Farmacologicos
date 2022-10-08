#ifndef COMPRA_H_INCLUDED
#define COMPRA_H_INCLUDED
#include <stdio.h>
typedef struct NotaCompra *TNotaCompra;
unsigned long getIdNotaCompra(TNotaCompra nota);
unsigned long getIdFornecedorNotaCompra(TNotaCompra nota);
void setIdNotaCompra(TNotaCompra nota,unsigned long id);
void setIdFornecedorNotaCompra(TNotaCompra nota,unsigned long id);

void getDataCompra(TNotaCompra nota,char *receptorData);
void setDataCompra(TNotaCompra nota,char *receptorData);
float getValorTotalNotaCompra(TNotaCompra nota);
int tamStructNotaCompra();
TNotaCompra novoNotaCompra();
void liberaNotaCompra(TNotaCompra nota);
unsigned long novoIdNotaCompra(FILE *f);
void inicializarNotaCompra(TNotaCompra nota,unsigned long id,unsigned long idFornecedor,char *data, float total);
unsigned long buscaIdNotaCompra(unsigned long id,FILE *f);
void atribuirDadosNotaCompra(TNotaCompra nota,unsigned long posicao,FILE *f);
#endif // COMPRA_H_INCLUDED
