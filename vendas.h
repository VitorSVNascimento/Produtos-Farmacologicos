#ifndef VENDAS_H_INCLUDED
#define VENDAS_H_INCLUDED

typedef struct{

unsigned long  id ;
unsigned long idCliente;
 unsigned long idVendedor;
 char dataCompra[11];
 float valorTotal;

}t_nota_fiscal;

typedef struct{
unsigned long id;
unsigned long idNota;
unsigned long idDoProduto;
float valorVenda;
unsigned int quantidade;

}t_item_nota_fiscal;



typedef struct{

unsigned long idProduto;
unsigned int  quantidadeVendida;
float valorVenda;

}item_carrinho;

typedef struct Nodo{
    item_carrinho info;
    struct Nodo *next;
}t_nodo;

typedef struct{
    t_nodo *inicio, *fim;
    int tamanho;
}t_carrinho;

typedef t_carrinho *carrinho;

carrinho criaCarrinho();

void terminaCarrinho(carrinho);

int insereFinal(carrinho, item_carrinho);

void imprime(carrinho,FILE *);

int removeItem(carrinho,unsigned long);


void mVendas();
void menuVendas(FILE *,FILE *,FILE *,unsigned long ,unsigned long );
int verifica_carrinho(carrinho,unsigned long);
void altera_qtde(unsigned long,unsigned int,carrinho);
void finaliza_compra(unsigned long,unsigned long,carrinho,FILE *,FILE *,FILE *);
unsigned long gera_IDNF(FILE *);
float gera_valor_total(carrinho);
unsigned long gera_IDINF(FILE *);
#endif // VENDAS_H_INCLUDED
