#ifndef VALIDACOES_H_INCLUDED
#define VALIDACOES_H_INCLUDED

/*
    varifica se o cpf é válido atráves da soma dos digitos
    retrona 1 se for válido e 0 se for inválido
*/
int validaCpf(char *cpf);
/*
    varifica se a string possui apenas numeros
    retrona 1 se for apenas numeros e 0 caso contrário
*/
int apenasNumeros(char *numero);
/*
    varifica se o cnpj é válido atráves dos digitos validadores
    retrona 1 se for válido e 0 se for inválido
*/
int validaCnpj(char *cnpj);
int restoSomaCNPJ(int *cnpj,int *multiplicador,int tam);
/*
    varifica se a data é válida
    retrona 1 se for válida e 0 se for inválida
*/
int validaData(char *data);
#endif // VALIDACOES_H_INCLUDED
