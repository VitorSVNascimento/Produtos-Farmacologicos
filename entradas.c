#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "cliente.h"
#include "validacao.h"
#include "vendedor.h"
#include "fornecedor.h"
#include "entradas.h"
#include "funcoesgerais.h"


void recebe_nome(char *nome){

int teste=1;

//recebe o nome de alguma variavel remove o \n e muda pra maiusculo
do{
  printf("\nForneça o Nome:|");
     setbuf(stdin,NULL);
    fgets(nome,100,stdin);

teste=retira_n(nome);

        if(teste==0)
            printf("\n-------------------------Nome não pode ser vazio!!!----------------------------------------");

nome_maiusculo(nome);

}while(teste==0);
}

//---------------------------------------FUNÇÃO DE ARMAZENAMENTO E VALIDAÇÃO DE CPF------------------------------

void recebe_cpf(char *cpf,FILE *file,int tipo){

int teste=1;
do {
        printf("\nForneça o CPF:|");
           fgets(cpf,12,stdin);
            setbuf(stdin,NULL);

teste=0;
        if(retira_n(cpf)==0){

            printf("\n-------------------------CPF não pode ser vazio!!!----------------------------------------");

        }else{

teste=cpf_Repetido(cpf,file,tipo);

            if(teste==0){printf("\nEste CPF já está cadastrado!!!");

            }else{

teste=valida_cpf(cpf);

                if(teste==0)printf("CPF Invalido!!!");



            }

        }
}while(teste==0);
}

void recebe_email(char *email){
int teste=1;

do{       setbuf(stdin,NULL);
        printf("\nForneça o E-mail:|");
          fgets(email,50,stdin);
teste=retira_n(email);

        if(teste==0)
            printf("\n-------------------------E-mail não pode ser vazio!!!----------------------------------------");

nome_maiusculo(email);


}while(teste==0);
}

void recebe_telefone(char *telefone){

int teste=1;

do{           setbuf(stdin,NULL);
              printf("\nForneça o telefone,utilize somente numeros:");
                 fgets(telefone,15,stdin);


        if(retira_n(telefone)==0){
            printf("\n-------------------------Telefone não pode ser vazio!!!----------------------------------------");
        }else {

teste=apenas_numeros(telefone);

        if(teste==0) printf("\n-----Utilize apenas numeros!!!-----");

        }


 }while(teste==0);
}

//=================================RECEBE CNPJ============================

void recebe_cnpj(char *cnpj,FILE *file){
int teste;
teste=1;
do{

        printf("\nForneça o CNPJ(apenas numeros):|");
            setbuf(stdin,NULL);
           fgets(cnpj,15,stdin);
teste=0;
if(apenas_numeros(cnpj)==0){printf("\nUtilize apenas números!!!");

}else{

        if(retira_n(cnpj)==0){

            printf("\n-------------------------CNPJ não pode ser vazio!!!----------------------------------------");

        }else{

teste=cnpj_Repetido(cnpj,file);

            if(teste==0){printf("\nEste CNPJ já está cadastrado!!!");

            }else{

teste=valida_cnpj(cnpj);
                if(teste==0)printf("CNPJ Invalido!!!");



            }

        }
}
}while(teste==0);

}

int recebe_data(char *data){
char dataAux[11];
  int d[3],i;
  char *tokens;
//recebe a data e retorna 0 caso ela seja invalida
printf("\nForneça a nova data(formato:dd/mm/aaaa):");
setbuf(stdin,NULL);
  fgets(data,11,stdin);
    retira_n(data);

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
    case 1:;
    case 3:;
    case 5:;
    case 7:;
    case 8:;
    case 10:;
    case 12:
      if(d[0]>31)
        return 0;
      else
        return 1;
    case 4:;
    case 6:;
    case 9:;
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

void data_sistema(char *data){

 time_t t = time(NULL);
  struct tm tm = *localtime(&t);
//tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

data[0]=tm.tm_mday/10+'0';
data[1]=tm.tm_mday%10+'0';
data[2]='/';
data[3]=(tm.tm_mon+1)/10+'0';
data[4]=(tm.tm_mon+1)%10+'0';
data[5]='/';
data[6]=(tm.tm_year+1900)/1000+'0';
data[7]=(tm.tm_year+1900)%1000/100+'0';
data[8]=(tm.tm_year+1900)%1000%100/10+'0';
data[9]=(tm.tm_year+1900)%1000%100%10+'0';
data[10]='\0';

}
