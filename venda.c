#include "venda.h"
#include <string.h>
#include <stdlib.h>
struct NotaFiscal{
    unsigned long id;
    unsigned long idCliente;
    unsigned long idVendedor;
    char dataCompra[11];
    float valorTotal;
};

unsigned long getIdNotaFiscal(TNotaFiscal nota){
    return nota->id;
}
void setIdNotaFiscal(TNotaFiscal nota,unsigned long id){
    nota->id = id;
}
unsigned long getIdClienteNotaFiscal(TNotaFiscal nota){
    return nota->idCliente;
}
void setIdClienteNotaFiscal(TNotaFiscal nota,unsigned long id){
    nota->idCliente = id;
}
unsigned long getIdVendedorNotaFiscal(TNotaFiscal nota){
    return nota->idVendedor;
}

void setIdVendedorNotaFiscal(TNotaFiscal nota,unsigned long id){
    nota->idVendedor = id;
}

void getDataCompraNotaFiscal(TNotaFiscal nota, char *data){
    strcpy(data,nota->dataCompra);
}
void setDataCompraNotaFiscal(TNotaFiscal nota, char *data){
    strcpy(nota->dataCompra,data);
}

float getValorTotalNotaFiscal(TNotaFiscal nota){
    return nota->valorTotal;
}
void setValorTotalNotaFiscal(TNotaFiscal nota,float valorTotal){
    nota->valorTotal=valorTotal;
}

int tamStructNotaFiscal(){
    return sizeof(struct NotaFiscal);
}

TNotaFiscal novoNotaFiscal(){

    TNotaFiscal nota=(TNotaFiscal)malloc(tamStructNotaFiscal());
    if(nota)
        return nota;
    return NULL;

}

unsigned long novoIdNotaFiscal(FILE *f){

    unsigned long id;
    TNotaFiscal novo = novoNotaFiscal();

    id=1;
    fseek(f,0,SEEK_SET);
    while(fread(novo,tamStructNotaFiscal(),1,f)==1){

        if(novo->id==0)
            break;

        id++;

    }
    liberaNotaFiscal(novo);
    return id;
}

void inicializarNotaFiscal(TNotaFiscal nota,unsigned long id,unsigned long idCliente,unsigned long idVendedor, char *data, float total){

    nota->id=id;
    nota->idCliente = idCliente;
    nota->idVendedor = idVendedor;
    strcpy(nota->dataCompra,data);
    nota->valorTotal=total;
    return;

}

unsigned long buscaIdNotaFiscal(unsigned long id, FILE *file){
    TNotaFiscal busca = novoNotaFiscal();
    int achou=0,posicao=0;

    fseek(file,0,SEEK_SET);
    while(fread(busca,tamStructNotaFiscal(),1,file)==1&&!achou)
        (busca->id==id)? achou=1:posicao++;
    liberaNotaFiscal(busca);
    if(achou)
        return posicao;
    return -1;
}

void atribuirDadosNotaFiscal(TNotaFiscal nota,unsigned long posicao,FILE *f){
        fseek(f,tamStructNotaFiscal()*posicao,SEEK_SET);
        fread(nota,tamStructNotaFiscal(),1,f);
        return ;
}

void liberaNotaFiscal(TNotaFiscal nota){
    free(nota);
}