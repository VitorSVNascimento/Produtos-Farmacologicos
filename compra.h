#ifndef COMPRA_H_INCLUDED
#define COMPRA_H_INCLUDED

typedef struct{
unsigned long id;
unsigned long idFornecedor;
char dataCompra[11];
float valorTotal;

}nota_compra;

typedef struct{
unsigned long id;
unsigned long idProduto;
unsigned long idNotaCompra;
unsigned int quantidade;
float valorUnitario;


}item_nota_compra;

void mCompra();
void menuCompras(FILE *,unsigned long idv);
void finaliza_venda(unsigned long,carrinho,FILE *,FILE *);
unsigned long gera_IDNC(FILE *);
unsigned long gera_IDINC(FILE *);













#endif // COMPRA_H_INCLUDED
