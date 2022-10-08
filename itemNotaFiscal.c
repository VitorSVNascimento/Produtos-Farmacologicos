#include "itemNotaFiscal.h"
#include <stdlib.h>
struct ItemNotaFiscal{
    unsigned long id;
    unsigned long idNotaFiscal;
    unsigned long idProduto;
    float valorVenda;
    unsigned int quantidade;
};

unsigned long getIdItemNotaFiscal(TItemNotaFiscal item){
    return item->id;
}
void setIdItemNotaFiscal(TItemNotaFiscal item, unsigned long id){
    item->id = id;
}
unsigned long getIdNotaFiscalItemNotaFiscal(TItemNotaFiscal item){
    return item->idNotaFiscal;
}
void setIdNotaFiscalItemNotaFiscal(TItemNotaFiscal item, unsigned long id){
    item->idNotaFiscal=id;
}
unsigned long getIdProdutoItemNotaFiscal(TItemNotaFiscal item){
    return item->idProduto;
}
void setIdProdutoItemNotaFiscal(TItemNotaFiscal item, unsigned long id){
    item->idProduto=id;
}
unsigned int getQuantidadeItemNotaFiscal(TItemNotaFiscal item){
    return item->quantidade;
}
void setQuantidadeItemNotaFiscal(TItemNotaFiscal item, unsigned long qtde){
    item->quantidade=qtde;
}
float getValorVendaItemNotaFiscal(TItemNotaFiscal item){
    return item->valorVenda;
}
void setValorVendaItemNotaFiscal(TItemNotaFiscal item, float valor){
    item->valorVenda=valor;
}
int tamStructItemNotaFiscal(){
    return sizeof(struct ItemNotaFiscal);
}
TItemNotaFiscal novoItemNotaFiscal(){
    TItemNotaFiscal item=(TItemNotaFiscal)malloc(tamStructItemNotaFiscal());
    if(item)
        return item;
    return NULL;

}
void liberaItemNotaFiscal(TItemNotaFiscal item){
    free(item);  
}

void inicializarItemNotaFiscal(TItemNotaFiscal item,unsigned long id,unsigned long idProduto,unsigned long idNotaFiscal,unsigned int qtde, float valorVenda){
    item->id=id;
    item->idProduto = idProduto;
    item->idNotaFiscal = idNotaFiscal;
    item->quantidade = qtde;
    item->valorVenda=valorVenda;
    return;    
}
unsigned long novoIdItemNotaFiscal(FILE *f){
     unsigned long id;
    TItemNotaFiscal novo = novoItemNotaFiscal();

    id=1;
    fseek(f,0,SEEK_SET);
    while(fread(novo,tamStructItemNotaFiscal(),1,f)==1){

        if(novo->id==0)
            break;

        id++;

    }
    liberaItemNotaFiscal(novo);
    return id;   
}