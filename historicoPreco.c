#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "historicoPreco.h"
struct HistoricoPreco{
    unsigned long idProduto;
    char dataAlteracao[11];
    float valor;
};

unsigned long getIdProdutoHistoricoPreco(THistoricoPreco historico){
    return historico->idProduto;
}
void setIdProdutoHistoricoPreco(THistoricoPreco historico, unsigned long id){
    historico->idProduto = id;
}
void getDataAlteracao(THistoricoPreco historico, char *aux){
    strcpy(aux,historico->dataAlteracao);
}
void setDataAlteracao(THistoricoPreco historico, char *aux){
    strcpy(historico->dataAlteracao,aux);
}
float getValorHistoricoPreco(THistoricoPreco historico){
    return historico->valor;
}
void setValorHistoricoPreco(THistoricoPreco historico,float valor){
    historico->valor = valor;
}

int tamStructHistorico(){
    return sizeof(struct HistoricoPreco);
}
THistoricoPreco novoHistorico(){
    THistoricoPreco historico = (THistoricoPreco)malloc(tamStructHistorico());
    if(historico)
        return historico;
    return NULL;
}
void liberaHistorico(THistoricoPreco historico){
    free(historico);
}

void inicializaHistorico(THistoricoPreco historico, unsigned long idProduto, char *data, float valor){
    historico->idProduto = idProduto;
    strcpy(historico->dataAlteracao,data);
    historico->valor = valor;
}
