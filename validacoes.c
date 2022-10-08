#include "validacoes.h"
#include <string.h>
#include <stdlib.h>
int validaCpf(char *cpf){
//valida o CPF retornando 0 caso seja invalido e 1 caso seja valido
    int soma=0;
    int i;
//verifica se tem todos os numeros e faz a soma dos digitos caso descubra um valor valido retorna 0
    if(strlen(cpf)!= 11)
        return 0;
    if(cpf[10] != '\0'){
        for (i=0;cpf[i]!='\0';i++)
        soma = soma+(cpf[i]-48);



        switch (soma) {
            case 10:
            case 11:
            case 12:
            case 21:
            case 22:
            case 23:
            case 32:
            case 33:
            case 34:
            case 43:
            case 44:
            case 45:
            case 54:
            case 55:
            case 56:
            case 65:
            case 66:
            case 67:
            case 76:
            case 77:
            case 78:
            case 87:
            case 88:

                return 1;
            default:
                return 0;

        }

    }else
        return 0;

}

int apenasNumeros(char *numero){
//verifica se existem apenas numeros em uma string
    int i,tam = strlen(numero);

    for(i=0;i<tam;i++)
        if(numero[i]<48||numero[i]>57)
            return 0;

    return 1;
}

int validaCnpj(char *cnpj){
int multiplicador1[12]={5,4,3,2,9,8,7,6,5,4,3,2};
int multiplicador2[13]={6,5,4,3,2,9,8,7,6,5,4,3,2};
int digito1,digito2,i;
int cnpjaux[12];
int cnpjaux2[13];

//transfere os valores inteiros da string para os auxiliares
for(i=0;i<12;i++){
    cnpjaux[i]=cnpj[i]-48;
    cnpjaux2[i]=cnpj[i]-48;
}
digito1=restoSomaCNPJ(cnpjaux,multiplicador1,12);
cnpjaux2[12]=digito1;


//segundo digito
digito2=restoSomaCNPJ(cnpjaux2,multiplicador2,13);
if(digito1==cnpj[12]-48 && digito2==cnpj[13]-48)
    return 1;
else
    return 0;

}

int restoSomaCNPJ(int *cnpj,int *multiplicador,int tam){
    int soma = 0,resto,i;
    for(i=0;i<tam;i++)
        soma=soma+cnpj[i]* multiplicador[i];

    resto=soma%11;
    if(resto<2)
        resto=0;
    else
        resto=11-resto;
    return resto;
}


int validaData(char *data){
char dataAux[11];
  int d[3],i;
  char *tokens;
  strcpy(dataAux,data);

  if(strlen(data)!=10)
    return 0;
  for(i=0;data[i]!='\0';i++)  {
    if(i==2 || i==5){
      if(data[i]!='/')
        return 0;
    }
    else
      if(data[i]<'0' || data[i]>'9')
        return 0;
  }

  tokens = strtok(dataAux,"/");
  i=0;
  while(tokens!=NULL){
    d[i]=atoi(tokens);
    i++;
    tokens = strtok(NULL,"/");
  }
  if(d[2]<1960)
    return 0;
  if(d[2]<=1960 && d[1]<=6 && d[0]<=20)
    return 0;
  if(d[0]==0)
    return 0;
  switch(d[1]){
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
      if(d[0]>31)
        return 0;
      else
        return 1;
    case 4:
    case 6:
    case 9:
    case 11:
      if(d[0]>30)
        return 0;
      else
        return 1;
    case 2:
       //verificando se o ano é bissexto
       if(((d[2]%4==0) && (d[2]%100!=0))||(d[2]%400==0)){
         if(d[0]>29)
           return 0;
         else
           return 1;
       }
       else{
         if(d[0]>28)
           return 0;
         else
           return 1;
       }
    default:
        return 0;
  }
}

