#include "produto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Produto{

    unsigned long id;
    char nome[100];
    unsigned int quantidadeEstoque;
    float precoUnitario;
};

unsigned long getIdProduto(TProduto produto){
    return produto->id;
}

void setIdProduto(TProduto produto, unsigned long id){
    produto->id = id;
}

void getNomeProduto(TProduto produto, char *nome){
    strcpy(nome, produto->nome);
}

void setNomeProduto(TProduto produto, char *nome){
    strcpy(produto->nome, nome);
}

unsigned int getQtdeEstoqueProduto(TProduto produto){
    return produto->quantidadeEstoque;
}

void setQtdeEstoqueProduto(TProduto produto, unsigned int qtde){
    produto->quantidadeEstoque = qtde;
}

float getPrecoUnitarioProduto(TProduto produto){
    return produto->precoUnitario;
}

void setPrecoUnitarioProduto(TProduto produto, float precoUnitario){
    produto->precoUnitario = precoUnitario;
}

int tamStructProduto(){
    return sizeof(struct Produto);
}

TProduto novoProduto(){

    TProduto produto=(TProduto)malloc(tamStructProduto());
    if(produto)
        return produto;
    return NULL;

}

void inserirProdutoNaPosicao(TProduto produto,FILE *arq,unsigned long posicao){
    fseek(arq,tamStructProduto()*posicao,SEEK_SET);
    fwrite(produto,tamStructProduto(),1,arq);
}

unsigned long novoIdProduto(FILE *f){

    unsigned long id;
    TProduto novo = novoProduto();

    id=1;
    fseek(f,0,SEEK_SET);
    while(fread(novo,tamStructProduto(),1,f)==1){

        if(novo->id==0)
            break;

        id++;

    }
    liberaProduto(novo);
    return id;
}

void inicializarProduto(TProduto produto,unsigned long id,char *nome,unsigned int quantidadeEstoque, float preco){

    produto->id=id;
    strcpy(produto->nome,nome);
    produto->precoUnitario=preco;
    produto->quantidadeEstoque=quantidadeEstoque;
    return;

}

void liberaProduto(TProduto produto){
    free(produto);
}

unsigned long buscaPrefixoProduto(char *pre,FILE *file, unsigned long posInicial){
    TProduto busca = novoProduto();
    int achou=0,posicao=0,tam = strlen(pre);
    fseek(file,tamStructProduto() * posInicial,SEEK_SET);
    while(fread(busca,tamStructProduto(),1,file)==1&&!achou)
        (strncmp(pre,busca->nome,tam)==0 && busca->id>0)? achou=1:posicao++;

    liberaProduto(busca);
    if(achou)
        return posicao + posInicial;
    return -1;
}

unsigned long buscaIdProduto(unsigned long id, FILE *file){
    TProduto busca = novoProduto();
    int achou=0,posicao=0;

    fseek(file,0,SEEK_SET);
    while(fread(busca,tamStructProduto(),1,file)==1&&!achou)
        (busca->id==id)? achou=1:posicao++;
    liberaProduto(busca);
    if(achou)
        return posicao;
    return -1;

}

void excluirProduto(TProduto produto,FILE *f, unsigned long posicao){
    produto->id=0;
    inserirProdutoNaPosicao(produto,f,posicao);

}

void atribuirDadosProduto(TProduto produto,unsigned long posicao,FILE *f){
        fseek(f,tamStructProduto()*posicao,SEEK_SET);
        fread(produto,tamStructProduto(),1,f);
        return ;
}

unsigned long registroValidosProduto(FILE *f){
    unsigned long total=0;
    TProduto produto = novoProduto();
    fseek(f,0,SEEK_SET);
    while(fread(produto,tamStructProduto(),1,f))
        if(produto->id)
            total++;
    liberaProduto(produto);
    return total;
}

