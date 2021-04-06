#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED



typedef struct{

unsigned long id ;
char nome[100];
char cpf[12];
char email[50];
char telefone[15];
}t_cliente;





void mCliente();
void alterCliente(FILE*);
void cadCliente(FILE*);
void consCliente(FILE*);
void delCliente(FILE*);
unsigned long novo_ID(FILE*);

#endif // CLIENTE_H_INCLUDED
