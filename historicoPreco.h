#ifndef HISTORICOPRECO_H_INCLUDED
#define HISTORICOPRECO_H_INCLUDED
#include <stdio.h>

typedef struct HistoricoPreco *THistoricoPreco;

//Getters e Seters
unsigned long getIdProdutoHistoricoPreco(THistoricoPreco historico);
void setIdProdutoHistoricoPreco(THistoricoPreco historico, unsigned long id);
void getDataAlteracao(THistoricoPreco historico, char *aux);
void setDataAlteracao(THistoricoPreco historico, char *aux);
float getValorHistoricoPreco(THistoricoPreco historico);
void setValorHistoricoPreco(THistoricoPreco historico,float valor);

THistoricoPreco novoHistorico();
int tamStructHistorico();
void liberaHistorico(THistoricoPreco historico);

void inicializaHistorico(THistoricoPreco historico, unsigned long idProduto, char *data, float valor); 

#endif