#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "cliente.h"
#include "vendedor.h"
#include "validacao.h"
#include "fornecedor.h"
#include "funcoesgerais.h"

int retira_n(char *nome){
//recebe uma variavel char e remove o \n o subistituindo por \0 e retorna 0 se o nome for vazio

   if(nome[0]!='\n'){
        if(nome[strlen(nome)-1]=='\n'){
            nome[strlen(nome)-1]='\0';


}

   }else
   return 0;
   return 1;
}

//--------------------------------------FUNÇÃO QUE VALIDA CPF-------------------------------------------------------




int valida_cpf(char *cpf){
//valida o CPF retornando 0 caso seja invalido e 1 caso seja valido
int soma=0;
int i,validar;
//verifica se tem todos os numeros e faz a soma dos digitos caso descubra um valor valido retorna 0
        if(cpf[10] != '\0'){
            for (i=0;cpf[i]!='\0';i++){
            soma = soma+(cpf[i]-48);

            }

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
        break;
        default:
      validar= 0;

            }

        }else{
            validar=0;


        }

return validar;

         }


//------------------------------função que deixa o nome maiusculo-------------------------------------------------

void nome_maiusculo(char *nome){

int i;



for(i=0;i<strlen(nome);i++){
//remove todos os acentos possiveis e deixa as letras em maiuscula através strupr
switch (nome[i]){

case 'á':
case 'à':
case 'â':
case 'ã':
case 'ä':
case 'Ä':
case 'Å':
case 'Á':
case 'Â':
case 'À':
case 'Ã':

    nome[i]='A';
    break;
case 'É':
case 'Ê':
case 'Ë':
case 'È':
case 'é':
case 'ê':
case 'ë':
case 'è':
  nome[i]='E';
  break;
case 'Í':
case 'Î':
case 'Ï':
case 'Ì':
case 'í':
case 'î':
case 'ï':
case 'ì':
     nome[i]='I';
    break;


case 'ô':
case 'ó':
case 'ò':
case 'õ':
case 'ö':
case 'Ó':
case 'Ò':
case 'Õ':
case 'Ö':
        nome[i]='O';
break;

case 'Ü':
    case 'Ú':
    case 'Û':
    case 'ü':
    case 'ú':
    case 'û':
    case 'ù':
    nome[i]='U';
    break;
    case 'Ç':
    case 'ç':
    nome[i]='C';
    break;
    case 'ñ':
    case 'Ñ':
    nome[i]='N';
    break;
    default:
        break;
}

}
for(i=0;i<strlen(nome);i++){
 if(nome[i]>'Z'){
    nome[i]=nome[i]-32;
 }



}



}

//------------------------------------FUNÇÃO QUE VERIFICA SE TEM APENAS NUMEROS-----------------------------------

int apenas_numeros(char *numero){
//verifica se existem apenas numeros em uma string
int i;

for(i=0;i<strlen(numero);i++){

if(numero[i]<48||numero[i]>57){
//falso
return 0;


}
}
return 1;
}

//---------------------------------------------VERIFICA CPF REPETIDO---------------------------------------------------------------------

int cpf_Repetido(char *cpf,FILE *file,int tipo){
//percorre um arquivo e verifica se o cpf fornecido ja esta nele
//retorna 0 se for repetido
t_cliente novo;
t_vendedor novop;

fseek(file,0,SEEK_SET);
switch (tipo){
case 1:
while(fread(&novo,sizeof (t_cliente),1,file)==1){

if(strcmp(cpf,novo.cpf)==0)
    return 0;

}
return 1;
break;

case 3:
    while(fread(&novop,sizeof (t_vendedor),1,file)==1){

        if(strcmp(cpf,novo.cpf)==0)
            return 0;

}
            return 1;
                break;


}

return 1;
}

//=================VALIDA CNPJ======================

int valida_cnpj(char *cnpj){
//descobre os dois digitos validadores atraves do multiplicador padrão e os verifica com os dois ultimos digitos do cnpj
int i;

int multiplicador1[12]={5,4,3,2,9,8,7,6,5,4,3,2};
int multiplicador2[13]={6,5,4,3,2,9,8,7,6,5,4,3,2};
int soma=0;
int resto,validar;
int digito1,digito2;
int cnpjaux[12];
int cnpjaux2[13];

cnpjaux[0]=cnpj[0]-48;
cnpjaux[1]=cnpj[1]-48;
cnpjaux[2]=cnpj[2]-48;
cnpjaux[3]=cnpj[3]-48;
cnpjaux[4]=cnpj[4]-48;
cnpjaux[5]=cnpj[5]-48;
cnpjaux[6]=cnpj[6]-48;
cnpjaux[7]=cnpj[7]-48;
cnpjaux[8]=cnpj[8]-48;
cnpjaux[9]=cnpj[9]-48;
cnpjaux[10]=cnpj[10]-48;
cnpjaux[11]=cnpj[11]-48;

for(i=0;i<12;i++){

 soma=soma+cnpjaux[i]* multiplicador1[i];
}
resto=soma%11;
if(resto<2)
    resto=0;
    else
        resto=11-resto;
digito1=resto;


soma=0;
//segundo digito

cnpjaux2[0]=cnpj[0]-48;
cnpjaux2[1]=cnpj[1]-48;
cnpjaux2[2]=cnpj[2]-48;
cnpjaux2[3]=cnpj[3]-48;
cnpjaux2[4]=cnpj[4]-48;
cnpjaux2[5]=cnpj[5]-48;
cnpjaux2[6]=cnpj[6]-48;
cnpjaux2[7]=cnpj[7]-48;
cnpjaux2[8]=cnpj[8]-48;
cnpjaux2[9]=cnpj[9]-48;
cnpjaux2[10]=cnpj[10]-48;
cnpjaux2[11]=cnpj[11]-48;
cnpjaux2[12]=digito1;

for(i=0;i<13;i++){

 soma=soma+cnpjaux2[i]*multiplicador2[i];
}
resto=soma%11;
if(resto<2)
    resto=0;
    else
        resto=11-resto;
digito2=resto;
if(digito1==cnpj[12]-48 && digito2==cnpj[13]-48)
validar=1;
else
validar=0;

return validar;
}

