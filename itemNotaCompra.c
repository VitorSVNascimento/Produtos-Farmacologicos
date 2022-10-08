#include "itemNotaCompra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct ItemNotaCompra{
    unsigned long id;
    unsigned long idProduto;
    unsigned long idNotaCompra;
    unsigned int quantidade;
    float valorUnitario;

};

unsigned long getIdItemNotaCompra(TItemNotaCompra item){
    return item->id;
}

void setIdItemNotaCompra(TItemNotaCompra item, unsigned long id){
    item->id = id;
}

unsigned long getIdProdutoItem(TItemNotaCompra item){
    return item->idProduto;
}

void setIdProdutoItem(TItemNotaCompra item, unsigned long id){
    item->idProduto = id;
}

unsigned long getIdNotaCompraItem(TItemNotaCompra item){
    return item->idNotaCompra;
}

void setIdNotaCompraItem(TItemNotaCompra item, unsigned long id){
    item->idNotaCompra = id;
}

unsigned int getQuantidadeItemNotaCompra(TItemNotaCompra item){
    return item->quantidade;
}

void setQuantidadeItemNotaCompra(TItemNotaCompra item, unsigned long qtde){
    item->quantidade = qtde;
}

float getValorUnitarioItemNotaCompra(TItemNotaCompra item){
    return item->valorUnitario;
}

void setValorUnitarioItemNotaCompra(TItemNotaCompra item, float valor){
    item->valorUnitario = valor;
}

int tamStructItemNotaCompra(){
    return sizeof(struct ItemNotaCompra);
}

TItemNotaCompra novoItemNotaCompra(){

    TItemNotaCompra item=(TItemNotaCompra)malloc(tamStructItemNotaCompra());
    if(item)
        return item;
    return NULL;

}
void liberaItemNotaCompra(TItemNotaCompra item){
    free(item);
}

void inicializarItemNotaCompra(TItemNotaCompra item,unsigned long id,unsigned long idProduto,unsigned long idNotaCompra,unsigned int qtde, float valorUnitario){

    item->id=id;
    item->idProduto = idProduto;
    item->idNotaCompra = idNotaCompra;
    item->quantidade = qtde;
    item->valorUnitario=valorUnitario;
    return;

}

unsigned long novoIdItemNotaCompra(FILE *f){

    unsigned long id;
    TItemNotaCompra novo = novoItemNotaCompra();

    id=1;
    fseek(f,0,SEEK_SET);
    while(fread(novo,tamStructItemNotaCompra(),1,f)==1){

        if(novo->id==0)
            break;

        id++;

    }
    liberaItemNotaCompra(novo);
    return id;
}
