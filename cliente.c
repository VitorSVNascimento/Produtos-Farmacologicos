#include "cliente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Cliente {

    unsigned long id;
    char nome[100];
    char cpf[12];
    char email[50];
    char telefone[15];

};

unsigned long getIdCliente(TCliente cliente){
    return cliente->id;
}

void setIdCliente(TCliente cliente, unsigned long id){
    cliente->id = id;
}

void getNomeCliente(TCliente cliente, char *nome){
    strcpy(nome, cliente->nome);
}

void setNomeCliente(TCliente cliente, char *nome){
    strcpy(cliente->nome, nome);
}

void getCpfCliente(TCliente cliente, char *cpf){
    strcpy(cpf, cliente->cpf);
}

void setCpfCliente(TCliente cliente, char *cpf){
    strcpy(cliente->cpf, cpf);
}

void getEmailCliente(TCliente cliente, char *email){
    strcpy(email, cliente->email);
}

void setEmailCliente(TCliente cliente, char *email){
    strcpy(cliente->email, email);
}

void getTelefoneCliente(TCliente cliente, char *telefone){
    strcpy(telefone, cliente->telefone);
}

void setTelefoneCliente(TCliente cliente, char *telefone){
    strcpy(cliente->telefone, telefone);
}

int tamStruct(){
    return sizeof(struct Cliente);
}

TCliente novoCliente(){

    TCliente cliente=(TCliente)malloc(tamStruct());
    if(cliente)
        return cliente;
    return NULL;

}

void inserirClienteNaPosicao(TCliente cliente,FILE *arq,unsigned long posicao){
    fseek(arq,tamStruct()*posicao,SEEK_SET);
    fwrite(cliente,tamStruct(),1,arq);
}

unsigned long novoIdCliente(FILE *f){

    unsigned long id;
    TCliente novo = novoCliente();

    id=1;
    fseek(f,0,SEEK_SET);
    while(fread(novo,tamStruct(),1,f)==1){

        if(novo->id==0)
            break;

        id++;

    }
    liberaCliente(novo);
    return id;
}

void inicializarCliente(TCliente cliente,unsigned long id,char *nome,char *cpf, char *email, char *telefone){

    cliente->id=id;
    strcpy(cliente->nome,nome);
    strcpy(cliente->cpf,cpf);
    strcpy(cliente->email,email);
    strcpy(cliente->telefone,telefone);
    return;

}

void liberaCliente(TCliente cliente){
    free(cliente);
}

unsigned long buscaCpfCliente(char *cpf,FILE *file){
    TCliente busca = novoCliente();
    int achou=0,posicao=0;

    fseek(file,0,SEEK_SET);
    while(fread(busca,tamStruct(),1,file)==1&&!achou)
        (strcmp(cpf,busca->cpf)==0 && busca->id>0)? achou=1:posicao++;
    liberaCliente(busca);
    if(achou)
        return posicao;
    return -1;
}

unsigned long buscaIdCliente(unsigned long id, FILE *file){
    TCliente busca = novoCliente();
    int achou=0,posicao=0;

    fseek(file,0,SEEK_SET);
    while(fread(busca,tamStruct(),1,file)==1&&!achou)
        (busca->id==id)? achou=1:posicao++;
    liberaCliente(busca);
    if(achou)
        return posicao;
    return -1;

}

void excluirCliente(TCliente c,FILE *f, unsigned long posicao){
    c->id=0;
    inserirClienteNaPosicao(c,f,posicao);

}

unsigned long buscaPrefixoCliente(char *pre,FILE *file, unsigned long posInicial){
    TCliente busca = novoCliente();
    int achou=0,posicao=0,tam = strlen(pre);
    fseek(file,tamStruct() * posInicial,SEEK_SET);
    while(fread(busca,tamStruct(),1,file)==1&&!achou)
        (strncmp(pre,busca->nome,tam)==0 && busca->id>0)? achou=1:posicao++;

    liberaCliente(busca);
    if(achou)
        return posicao + posInicial;
    return -1;
}

void atribuirDadosCliente(TCliente c,unsigned long posicao,FILE *f){
        fseek(f,tamStruct()*posicao,SEEK_SET);
        fread(c,tamStruct(),1,f);
        return ;
}

unsigned long registroValidos(FILE *f){
    unsigned long total=0;
    TCliente c = novoCliente();
    fseek(f,0,SEEK_SET);
    while(fread(c,tamStruct(),1,f))
        if(c->id)
            total++;
    liberaCliente(c);
    return total;
}
