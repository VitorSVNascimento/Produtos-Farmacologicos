#ifndef MENUFORNECEDOR_H_INCLUDED
#define MENUFORNECEDOR_H_INCLUDED
#include "fornecedor.h"
void mFornecedor();
void cadastrarFornecedor(FILE *f);
void alteraFornecedor(FILE *f);
void consultaFornecedor(FILE *f);
void printaDadosFornecedor(TFornecedor fornecedor);
void listaTodosFornecedor(FILE *arq);
void menuExcluirFornecedor(FILE *f);


#endif // MENUFORNECEDOR_H_INCLUDED
