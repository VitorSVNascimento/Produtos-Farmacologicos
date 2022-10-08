#include "fornecedor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Fornecedor{

    unsigned long id;
    char cnpj[15];
    char nome[100];
    char email[50];
    char telefone[15];
};

unsigned long getIdFornecedor(TFornecedor fornecedor){
    return fornecedor->id;
}

void setIdFornecedor(TFornecedor fornecedor, unsigned long id){
    fornecedor->id = id;
}

void getNomeFornecedor(TFornecedor fornecedor, char *nome){
    strcpy(nome, fornecedor->nome);
}

void setNomeFornecedor(TFornecedor fornecedor, char *nome){
    strcpy(fornecedor->nome, nome);
}

void getCnpjFornecedor(TFornecedor fornecedor, char *cnpj){
    strcpy(cnpj, fornecedor->cnpj);
}

void setCnpjFornecedor(TFornecedor fornecedor, char *cnpj){
    strcpy(fornecedor->cnpj, cnpj);
}

void getEmailFornecedor(TFornecedor fornecedor, char *email){
    strcpy(email, fornecedor->email);
}

void setEmailFornecedor(TFornecedor fornecedor, char *email){
    strcpy(fornecedor->email, email);
}

void getTelefoneFornecedor(TFornecedor fornecedor, char *telefone){
    strcpy(telefone, fornecedor->telefone);
}

void setTelefoneFornecedor(TFornecedor fornecedor, char *telefone){
    strcpy(fornecedor->telefone, telefone);
}

int tamStructFornecedor(){
    return sizeof(struct Fornecedor);
}

TFornecedor novoFornecedor(){

    TFornecedor fornecedor=(TFornecedor)malloc(tamStructFornecedor());
    if(fornecedor)
        return fornecedor;
    return NULL;

}


void inserirFornecedorNaPosicao(TFornecedor fornecedor,FILE *arq,unsigned long posicao){
    fseek(arq,tamStructFornecedor()*posicao,SEEK_SET);
    fwrite(fornecedor,tamStructFornecedor(),1,arq);
}

unsigned long novoIdFornecedor(FILE *f){

    unsigned long id;
    TFornecedor novo = novoFornecedor();

    id=1;
    fseek(f,0,SEEK_SET);
    while(fread(novo,tamStructFornecedor(),1,f)==1){

        if(novo->id==0)
            break;

        id++;

    }
    liberaFornecedor(novo);
    return id;
}

void inicializarFornecedor(TFornecedor fornecedor,unsigned long id,char *nome,char *cnpj, char *email, char *telefone){

    fornecedor->id=id;
    strcpy(fornecedor->nome,nome);
    strcpy(fornecedor->cnpj,cnpj);
    strcpy(fornecedor->email,email);
    strcpy(fornecedor->telefone,telefone);
    return;

}

void liberaFornecedor(TFornecedor fornecedor){
    free(fornecedor);
}

unsigned long buscaCnpjFornecedor(char *cnpj,FILE *file){
    TFornecedor busca = novoFornecedor();
    int achou=0,posicao=0;

    fseek(file,0,SEEK_SET);
    while(fread(busca,tamStructFornecedor(),1,file)==1&&!achou)
        (strcmp(cnpj,busca->cnpj)==0 && busca->id>0)? achou=1:posicao++;
    liberaFornecedor(busca);
    if(achou)
        return posicao;
    return -1;
}
unsigned long buscaNomeFornecedor(char *nome,FILE *file){
    TFornecedor busca = novoFornecedor();
    int achou=0,posicao=0;

    fseek(file,0,SEEK_SET);
    while(fread(busca,tamStructFornecedor(),1,file)==1&&!achou)
        (strcmp(nome,busca->nome)==0 && busca->id>0)? achou=1:posicao++;
    liberaFornecedor(busca);
    if(achou)
        return posicao;
    return -1;
}

unsigned long buscaIdFornecedor(unsigned long id, FILE *file){
    TFornecedor busca = novoFornecedor();
    int achou=0,posicao=0;

    fseek(file,0,SEEK_SET);
    while(fread(busca,tamStructFornecedor(),1,file)==1&&!achou)
        (busca->id==id)? achou=1:posicao++;
    liberaFornecedor(busca);
    if(achou)
        return posicao;
    return -1;

}

void excluirFornecedor(TFornecedor fornecedor,FILE *f, unsigned long posicao){
    fornecedor->id=0;
    inserirFornecedorNaPosicao(fornecedor,f,posicao);

}

unsigned long buscaPrefixoFornecedor(char *pre,FILE *file, unsigned long posInicial){
    TFornecedor busca = novoFornecedor();
    int achou=0,posicao=0,tam = strlen(pre);
    fseek(file,tamStructFornecedor() * posInicial,SEEK_SET);
    while(fread(busca,tamStructFornecedor(),1,file)==1&&!achou)
        (strncmp(pre,busca->nome,tam)==0 && busca->id>0)? achou=1:posicao++;

    liberaFornecedor(busca);
    if(achou)
        return posicao + posInicial;
    return -1;
}

void atribuirDadosFornecedor(TFornecedor fornecedor,unsigned long posicao,FILE *f){
        fseek(f,tamStructFornecedor()*posicao,SEEK_SET);
        fread(fornecedor,tamStructFornecedor(),1,f);
        return ;
}

unsigned long registroValidosFornecedor(FILE *f){
    unsigned long total=0;
    TFornecedor fornecedor = novoFornecedor();
    fseek(f,0,SEEK_SET);
    while(fread(fornecedor,tamStructFornecedor(),1,f))
        if(fornecedor->id)
            total++;
    liberaFornecedor(fornecedor);
    return total;
}
