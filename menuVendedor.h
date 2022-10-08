#ifndef MENUVENDEDOR_H_INCLUDED
#define MENUVENDEDOR_H_INCLUDED
#include "vendedor.h"
void mVendedor();
void cadastrarVendedor(FILE *f);
void alteraVendedor(FILE *f);
void consultaVendedor(FILE *f);
void printaDadosVendedor(TVendedor v);
void listaTodosVendedor(FILE *arq);
void menuExcluirVendedor(FILE *f);
int menuAlteraSenha(FILE *f,unsigned long pos,char *senha);
#endif // MENUVENDEDOR_H_INCLUDED
