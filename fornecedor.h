#ifndef FORNECEDOR_H_INCLUDED
#define FORNECEDOR_H_INCLUDED
typedef struct{
unsigned long id;
char cnpj[15];
char nome[100];
char email[50];

}t_fornecedor;

void mFornecedor();
void alterFornecedor(FILE*);
void cadFornecedor(FILE*);
void consFornecedor(FILE*);
void delFornecedor(FILE *);
unsigned long novo_IDF(FILE*);
int nome_repetido(char *,FILE *);
int cnpj_Repetido(char *,FILE *);




#endif // FORNECEDOR_H_INCLUDED
