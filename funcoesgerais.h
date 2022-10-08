#ifndef FUNCOESGERAIS_H_INCLUDED
#define FUNCOESGERAIS_H_INCLUDED
void busca_ID(FILE*,unsigned long,int);
void busca_cpf(FILE*,char*,int);
void busca_prefixo(FILE*,char*,int);
void listagem(FILE*,int);
int verifica_senha(FILE *,char*,unsigned long);
void busca_cnpj(FILE*,char*);
void data_sistema(char *);
int recebe_data(char *);
void separa_data(char*,int*,int*,int*);
#endif // FUNCOESGERAIS_H_INCLUDED
