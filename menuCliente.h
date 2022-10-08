#ifndef MENUCLIENTE_H_INCLUDED
#define MENUCLIENTE_H_INCLUDED
#include "cliente.h"
void mCliente();
void cadastrarCliente(FILE *f);
void alteraCliente(FILE *f);
void consultaCliente(FILE *f);
void printaDadosCliente(TCliente c);
void listaTodos(FILE *arq);
void menuExcluirCliente(FILE *f);


#endif // MENUCLIENTE_H_INCLUDED
