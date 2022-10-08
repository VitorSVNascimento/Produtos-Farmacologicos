#include "vendedor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Vendedor {

    unsigned long id;
    char nome[100];
    char cpf[12];
    char email[50];
    char telefone[15];
    char password[20];
};

unsigned long getIdVendedor(TVendedor vendedor){
    return vendedor->id;
}

void setIdVendedor(TVendedor vendedor, unsigned long id){
    vendedor->id = id;
}

void getNomeVendedor(TVendedor vendedor, char *nome){
    strcpy(nome, vendedor->nome);
}

void setNomeVendedor(TVendedor vendedor, char *nome){
    strcpy(vendedor->nome, nome);
}

void getCpfVendedor(TVendedor vendedor, char *cpf){
    strcpy(cpf, vendedor->cpf);
}

void setCpfVendedor(TVendedor vendedor, char *cpf){
    strcpy(vendedor->cpf, cpf);
}

void getEmailVendedor(TVendedor vendedor, char *email){
    strcpy(email, vendedor->email);
}

void setEmailVendedor(TVendedor vendedor, char *email){
    strcpy(vendedor->email, email);
}

void getTelefoneVendedor(TVendedor vendedor, char *telefone){
    strcpy(telefone, vendedor->telefone);
}

void setTelefoneVendedor(TVendedor vendedor, char *telefone){
    strcpy(vendedor->telefone, telefone);
}

void getPasswordVendedor(TVendedor vendedor, char *password){
    strcpy(password, vendedor->password);
}

void setPasswordVendedor(TVendedor vendedor, char *password){
    strcpy(vendedor->password, password);
}

int tamStructVendedor(){
    return sizeof(struct Vendedor);
}

TVendedor novoVendedor(){

    TVendedor vendedor=(TVendedor)malloc(tamStructVendedor());
    if(vendedor)
        return vendedor;
    return NULL;

}


void inserirVendedorNaPosicao(TVendedor vendedor,FILE *arq,unsigned long posicao){
    fseek(arq,tamStructVendedor()*posicao,SEEK_SET);
    fwrite(vendedor,tamStructVendedor(),1,arq);
}

unsigned long novoIdVendedor(FILE *f){

    unsigned long id;
    TVendedor novo = novoVendedor();

    id=1;
    fseek(f,0,SEEK_SET);
    while(fread(novo,tamStructVendedor(),1,f)==1){

        if(novo->id==0)
            break;

        id++;

    }
    liberaVendedor(novo);
    return id;
}

void inicializarVendedor(TVendedor vendedor,unsigned long id,char *nome,char *cpf, char *email, char *telefone,char *password){

    vendedor->id=id;
    strcpy(vendedor->nome,nome);
    strcpy(vendedor->cpf,cpf);
    strcpy(vendedor->email,email);
    strcpy(vendedor->telefone,telefone);
    strcpy(vendedor->password,password);
    return;

}

void liberaVendedor(TVendedor vendedor){
    free(vendedor);
}

unsigned long buscaCpfVendedor(char *cpf,FILE *file){
    TVendedor busca = novoVendedor();
    int achou=0,posicao=0;

    fseek(file,0,SEEK_SET);
    while(fread(busca,tamStructVendedor(),1,file)==1&&!achou)
        (strcmp(cpf,busca->cpf)==0 && busca->id>0)? achou=1:posicao++;
    liberaVendedor(busca);
    if(achou)
        return posicao;
    return -1;
}
unsigned long buscaEmailVendedor(char *email,FILE *file){
    TVendedor busca = novoVendedor();
    int achou=0,posicao=0;

    fseek(file,0,SEEK_SET);
    while(fread(busca,tamStructVendedor(),1,file)==1&&!achou)
        (strcmp(email,busca->email)==0 && busca->id>0)? achou=1:posicao++;
    liberaVendedor(busca);
    if(achou)
        return posicao;
    return -1;
}

unsigned long buscaIdVendedor(unsigned long id, FILE *file){
    TVendedor busca = novoVendedor();
    int achou=0,posicao=0;

    fseek(file,0,SEEK_SET);
    while(fread(busca,tamStructVendedor(),1,file)==1&&!achou)
        (busca->id==id)? achou=1:posicao++;
    liberaVendedor(busca);
    if(achou)
        return posicao;
    return -1;

}

void excluirVendedor(TVendedor v,FILE *f, unsigned long posicao){
    v->id=0;
    inserirVendedorNaPosicao(v,f,posicao);

}

unsigned long buscaPrefixoVendedor(char *pre,FILE *file, unsigned long posInicial){
    TVendedor busca = novoVendedor();
    int achou=0,posicao=0,tam = strlen(pre);
    fseek(file,tamStructVendedor() * posInicial,SEEK_SET);
    while(fread(busca,tamStructVendedor(),1,file)==1&&!achou)
        (strncmp(pre,busca->nome,tam)==0 && busca->id>0)? achou=1:posicao++;

    liberaVendedor(busca);
    if(achou)
        return posicao + posInicial;
    return -1;
}

void atribuirDadosVendedor(TVendedor v,unsigned long posicao,FILE *f){
        fseek(f,tamStructVendedor()*posicao,SEEK_SET);
        fread(v,tamStructVendedor(),1,f);
        return ;
}

unsigned long registroValidosVendedor(FILE *f){
    unsigned long total=0;
    TVendedor v = novoVendedor();
    fseek(f,0,SEEK_SET);
    while(fread(v,tamStructVendedor(),1,f))
        if(v->id)
            total++;
    liberaVendedor(v);
    return total;
}

int validaSenha(FILE *f,unsigned long posicao,char *senha){
    TVendedor v = novoVendedor();
    fseek(f,tamStructVendedor() * posicao,SEEK_SET);
    fread(v,tamStructVendedor(),1,f);
    if(!strcmp(senha,v->password))
        return 1;
    return 0;
}
