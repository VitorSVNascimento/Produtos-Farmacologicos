#ifndef VENDA_H_INCLUDED
#define VENDA_H_INCLUDED
#include <stdio.h>
typedef struct NotaFiscal *TNotaFiscal;
unsigned long getIdNotaFiscal(TNotaFiscal nota);
void setIdNotaFiscal(TNotaFiscal nota,unsigned long id);
unsigned long getIdClienteNotaFiscal(TNotaFiscal nota);
void setIdClienteNotaFiscal(TNotaFiscal nota,unsigned long id);
unsigned long getIdVendedorNotaFiscal(TNotaFiscal nota);
void setIdVendedorNotaFiscal(TNotaFiscal nota,unsigned long id);
void getDataCompraNotaFiscal(TNotaFiscal nota, char *data);
void setDataCompraNotaFiscal(TNotaFiscal nota, char *data);
float getValorTotalNotaFiscal(TNotaFiscal nota);
void setValorTotalNotaFiscal(TNotaFiscal nota,float valorTotal);
int tamStructNotaFiscal();
TNotaFiscal novoNotaFiscal();
unsigned long novoIdNotaFiscal(FILE *f);
void inicializarNotaFiscal(TNotaFiscal nota,unsigned long id,unsigned long idCliente,unsigned long idVendedor, char *data, float total);
unsigned long buscaIdNotaFiscal(unsigned long id, FILE *file);
void atribuirDadosNotaFiscal(TNotaFiscal nota,unsigned long posicao,FILE *f);
void liberaNotaFiscal(TNotaFiscal nota);
#endif