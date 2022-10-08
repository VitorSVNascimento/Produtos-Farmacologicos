#ifndef PRODUTOS_H_INCLUDED
#define PRODUTOS_H_INCLUDED
typedef struct{

unsigned long id;
char nome[100];
unsigned int quantidadeEstoque;
float precoUnitario;
}t_produto;

typedef struct{

unsigned long idProduto;
char dataAlteracao[11];
float valor;

}historico_preco;


void mProduto();
void cadProduto(FILE *);
void alterProduto(FILE *);
void consProduto(FILE *);
void delProduto(FILE *);
unsigned long novo_IDP(FILE *);
void mAlteraPreco();
#endif // PRODUTOS_H_INCLUDED
