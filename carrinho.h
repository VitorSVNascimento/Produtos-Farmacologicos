#ifndef CARRINHO_H_INCLUDED
#define CARRINHO_H_INCLUDED
#include <stdio.h>
typedef struct{

unsigned long idProduto;
unsigned int  quantidadeVendida;
float valorVenda;

}itemCarrinho;

typedef struct Nodo{
    itemCarrinho info;
    struct Nodo *next;
}TNodo;

typedef struct{
    TNodo *inicio, *fim;
    int tamanho;
}TCarrinho;

typedef TCarrinho *carrinho;

/*
    Aloca espaço de memória para o carrinho de compras
    parametros: ()
    retorna: uma lista encadeada do tipo TCarrinho
*/
carrinho criaCarrinho();

/*
    desaloca espaço de memória do carrinho de compras
    parametros: carrinho(uma lista encadeada do tipo TCarrinho)
    retorna: void
*/
void terminaCarrinho(carrinho);

/*
    Insere um item no final do carrinho de compras
    parametros: carrinho(uma lista encadeada do tipo TCarrinho), itemCarrinho(o item do tipo itemCarrinho que sera inserido no fim da lista )
    retorna: 1 caso consiga inserir e 0 caso não consiga
*/
int insereFinal(carrinho, itemCarrinho);

/*
    Imprime na tela todos os itens do carrinho de compras
    parametros: carrinho(uma lista encadeada do tipo TCarrinho), FILE *(o arquivo onde está armazenado os produtos, que será usado apenas para printar o seus respectivos nomes )
    retorna: void
*/
void imprime(carrinho,FILE *);

/*
    Remove o item com id passado por parametro do carrinho de compras
    parametros: carrinho(uma lista encadeada do tipo TCarrinho), unsigned long id(o id do item a ser removido do carrinho )
    retorna: 1 se remover o item e 0 caso contrario
*/
int removeItem(carrinho,unsigned long);
/*
    verifica se o item com id passado por parametro já existe no carrinho de compras
    parametros: carrinho(uma lista encadeada do tipo TCarrinho), unsigned long id(o id do item a ser buscado no carrinho )
    retorna: 1 se o item já estiver no carrinho e 0 caso contrario
*/
int verificaCarrinho(carrinho,unsigned long);

/*
    altera a quantidade do item com id passado por parametro
    parametros: unsigned long id(o id do item a ser alterado no carrinho ), unsigned int quantidade(nova quantidade a ser atribuida para este item), carrinho(uma lista encadeada do tipo TCarrinho)
    retorna: 1 se o item já estiver no carrinho e 0 caso contrario
*/
void alteraQtde(unsigned long,unsigned int,carrinho);

/*
    gera o valor total dos produtos do carrinho
    parametros: carrinho(uma lista encadeada do tipo TCarrinho)
    retorna: o valor total obtido através do valor unitário * quatidade de cada produto do carrinho
*/
float geraValorTotal(carrinho cc);

#endif // CARRINHO_H_INCLUDED
