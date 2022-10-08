#ifndef VENDEDOR_H_INCLUDED
#define VENDEDOR_H_INCLUDED

typedef struct{

unsigned long id ;
char nome[100];
char cpf[12];
char email[50];
char telefone[15];
char password[20];
}t_vendedor;


void mVendedor();
void cadVendedor(FILE *);
void alterVendedor(FILE*);
void consVendedor(FILE*);
void delVendedor(FILE*);
unsigned long novo_IDV(FILE *);
int email_repetido(char *, FILE *);

#endif // VENDEDOR_H_INCLUDED
