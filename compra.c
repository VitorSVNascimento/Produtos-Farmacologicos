#include "compra.h"
#include <string.h>
#include <stdlib.h>
struct NotaCompra{
    unsigned long id;
    unsigned long idFornecedor;
    char dataCompra[11];
    float valorTotal;
};

unsigned long getIdNotaCompra(TNotaCompra nota){
    return nota->id;
}
void setIdNotaCompra(TNotaCompra nota,unsigned long id){
    nota->id = id;
}
unsigned long getIdFornecedorNotaCompra(TNotaCompra nota){
    return nota->idFornecedor ;
}
void setIdFornecedorNotaCompra(TNotaCompra nota,unsigned long id){
    nota->idFornecedor = id;
}

void getDataCompra(TNotaCompra nota,char *receptorData){
    strcpy(receptorData,nota->dataCompra);
}
void setDataCompra(TNotaCompra nota,char *receptorData){
    strcpy(nota->dataCompra,receptorData);
}
float getValorTotalNotaCompra(TNotaCompra nota){
    return nota->valorTotal;
}
void setValorTotalNotaCompra(TNotaCompra nota,float total){
    nota->valorTotal=total;
}

int tamStructNotaCompra(){
    return sizeof(struct NotaCompra);
}

TNotaCompra novoNotaCompra(){

    TNotaCompra nota=(TNotaCompra)malloc(tamStructNotaCompra());
    if(nota)
        return nota;
    return NULL;

}
void liberaNotaCompra(TNotaCompra nota){
    free(nota);
}

unsigned long novoIdNotaCompra(FILE *f){

    unsigned long id;
    TNotaCompra novo = novoNotaCompra();

    id=1;
    fseek(f,0,SEEK_SET);
    while(fread(novo,tamStructNotaCompra(),1,f)==1){

        if(novo->id==0)
            break;

        id++;

    }
    liberaNotaCompra(novo);
    return id;
}

void inicializarNotaCompra(TNotaCompra nota,unsigned long id,unsigned long idFornecedor,char *data, float total){

    nota->id=id;
    nota->idFornecedor = idFornecedor;
    strcpy(nota->dataCompra,data);
    nota->valorTotal=total;
    return;

}

unsigned long buscaIdNotaCompra(unsigned long id, FILE *file){
    TNotaCompra busca = novoNotaCompra();
    int achou=0,posicao=0;

    fseek(file,0,SEEK_SET);
    while(fread(busca,tamStructNotaCompra(),1,file)==1&&!achou)
        (busca->id==id)? achou=1:posicao++;
    liberaNotaCompra(busca);
    if(achou)
        return posicao;
    return -1;
}

void atribuirDadosNotaCompra(TNotaCompra nota,unsigned long posicao,FILE *f){
        fseek(f,tamStructNotaCompra()*posicao,SEEK_SET);
        fread(nota,tamStructNotaCompra(),1,f);
        return ;
}
