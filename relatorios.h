#ifndef RELATORIOS_H_INCLUDED
#define RELATORIOS_H_INCLUDED
#define TIPO_CLIENTE 1
#define TIPO_VENDEDOR 0
#include <stdio.h>
#include "compra.h"
#include "itemNotaCompra.h"
#include "venda.h"
#include "itemNotaFiscal.h"
#include "vendedor.h"

void mRelatorio();
void relatorioUm();
void relatorioDois();
void relatorioTres();
void relatorioQuatro();
void relatorioCinco();
void relatorioSeis();
void relatorioSete();
void relatorioOito();
void printaNotaCompraTela(TNotaCompra nota,FILE *arqProduto,FILE *arqForn,FILE *arqItem);
void printaItensNotaCompraTela(unsigned long idNota,FILE *arqProduto, FILE *arqItem);
void printaNotaCompraTexto(TNotaCompra nota,FILE *arqTxt,FILE *arqProduto,FILE *arqForn,FILE *arqItem);
void printaItensNotaCompraTexto(unsigned long idNota,FILE *arqTxt,FILE *arqProduto, FILE *arqItem);
void printaNotaFiscalTela(TNotaFiscal nota,FILE *arqProduto,FILE *arqVend,FILE *arqItem,FILE *arqCliente);
void printaItensNotaFiscalTela(unsigned long idNota,FILE *arqProduto, FILE *arqItem);
void printaNotaFiscalTexto(TNotaFiscal nota,FILE *arqTxt,FILE *arqProduto,FILE *arqVend,FILE *arqItem,FILE *arqCliente);
void printaItensNotaFiscalTexto(FILE *arqTxt,unsigned long idNota,FILE *arqProduto, FILE *arqItem);
int verificaNotaFiscal(TNotaFiscal nota,char *data1,char *data2,int tipo,unsigned long idTipo);
int verificaMesVendedorNotaFiscal(TNotaFiscal nota,int mes,int idVendedor);
float calculaValorVendaVendedor(FILE *arqVendedor,FILE *arqNotaFiscal,char *data1,char *data2,unsigned long idVendedor,int mes);
float calculaMaiorValorVenda(FILE *arqVendedor,FILE *arqNotaFiscal,char *data1,char *data2,int mes);
void printaDadosVendedorTexto(TVendedor v, FILE *arqTxt);
#endif // RELATORIOS_H_INCLUDED
