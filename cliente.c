#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "validacao.h"
#include "vendedor.h"
#include "entradas.h"
#include "funcoesgerais.h"




void mCliente(){
int sair;
FILE *f;

f=fopen("cliente.dat","rb+");
if(f==NULL)
f=fopen("cliente.dat","wb+");
if(f!=NULL){

do{
 printf("\n|----------------Menu de Clientes-----------------------");
 printf("\n|O que deseja Fazer");
 printf("\n|1-Cadastrar Clientes");
 printf("\n|2-Alterar Clientes");
 printf("\n|3-Consultar Clientes");
 printf ("\n|4Excluir Cliente");
 printf ("\n|5-Menu pricipal");
 printf("\n|Opção:");
 scanf ("%d",&sair);


switch(sair){

case 1:

cadCliente(f);
break;

case 2:
alterCliente(f);


break;
case 3:
consCliente(f);

break;

case 4:
 delCliente(f);
break;

}


}while(sair!=5);


fclose(f);
}else
printf("Impossivel abrir o arquivo");
return ;
}


//-----------------------------------função de cadastro-------------------------------------------------------------------------

void cadCliente(FILE *file){

t_cliente novo;
int menu,tipo=1;
unsigned long posicao;


do{
novo.id=novo_ID(file);

printf("\nID do cliente:|%lu",novo.id);

recebe_nome(novo.nome);

recebe_cpf(novo.cpf,file,tipo);

recebe_email(novo.email);

recebe_telefone(novo.telefone);

setbuf(stdin,NULL);

posicao=novo.id-1;
//coloca o novo cliente no fim do arquivo
fseek(file,sizeof(t_cliente)*posicao,SEEK_SET);
    fwrite(&novo,sizeof(t_cliente),1,file);

printf("\n----------------------------------CADASTRO CONCLUIDO------------------------------------------------------------");
printf("\nDeseja continuar cadastrando???");
printf("\n1-Sim|2-Não");
printf("\nOpção:");
scanf("%d",&menu);
}while (menu==1);
}

//------------------------------------------------------FUNÇÃO DE ID---------------------------------------------------------------

unsigned long novo_ID(FILE *file){

unsigned long id;
t_cliente novo;
//loop que incrementa o id enquanto o arquivo não estiver acabado
id=1;
fseek(file,0,SEEK_SET);
while(fread(&novo,sizeof (t_cliente),1,file)==1){

if(novo.id==0)
break;

id++;

}

return id;

}


//--------------------------------FIM DA FUNÇÕES DE CADASTROS---------------------------------------------------------------------Q

//------------------------------------MENU DE ALTERAÇÃO-----------------------------------------------------------------------------

void alterCliente(FILE *file){
unsigned long id,posicao;
int achou,s_n;


t_cliente novo;

do{
printf("\n-----------------Menu de Alteração de Cliente-----------------------");
printf("\nForneça o Id que deseja alterar:");
scanf("%lu",&id);

if(id!=0){
achou =0;
//loop que procura o id
fseek(file,0,SEEK_SET);
while(fread(&novo,sizeof (t_cliente),1,file)==1&&achou==0){

if(id==novo.id){
  achou=1;}else posicao ++;

  }
if(achou==1){
        //loop que busca o cliente pedido e mostra os dados atuais
fseek(file,sizeof(t_cliente)*posicao,SEEK_SET);
fread(&novo,sizeof(t_cliente),1,file);

    printf("\n|---------------Dados atuais--------------------|");
    printf("\n|ID:%lu",novo.id);
    printf("\n|Nome:%s",novo.nome);
    printf("\n|CPF:%s",novo.cpf);
    printf("\n|EMAIL:%s",novo.email);
    printf("\n|TELEFONE:%s",novo.telefone);
    printf("\n|-----------------------------------------------|");

    printf("\nDeseja Realmente alterar?");
    printf("\n|1-Sim|n2-Não\n|Opção:");
    scanf ("%d",&s_n);

    if(s_n==1){

    printf("\nDeseja alterar o nome???");

   printf("\n|1-Sim|n2-Não\n|Opção:");
    scanf("%d",&s_n);

        if(s_n==1)
        recebe_nome(novo.nome);

    printf("\nDeseja alterar o e-mail???");

    printf("\n|1-Sim|n2-Não\n|Opção:");
    scanf("%d",&s_n);

        if(s_n==1)
        recebe_email(novo.email);
    printf("\nDeseja alterar o telefone???");

    printf("\n|1-Sim|n2-Não\n|Opção:");
    scanf("%d",&s_n);

        if(s_n==1)
        recebe_telefone(novo.telefone);

fseek(file,sizeof(t_cliente)*posicao,SEEK_SET);
fwrite(&novo,sizeof(t_cliente),1,file);

    }
    printf("\n|---------------Alteração Concluida--------------------|");
    printf("\n|-----------------Dados atuais-------------------------|");
    printf("\n|ID:%lu",novo.id);
    printf("\n|Nome:%s",novo.nome);
    printf("\n|CPF:%s",novo.cpf);
    printf("\n|EMAIL:%s",novo.email);
    printf("\n|TELEFONE:%s",novo.telefone);
    printf("\n|------------------------------------------------------|");


}else
printf("\n---------ID não encontrado---------");


}else
printf("\n---------ID não encontrado---------");

    printf("\nFazer mais alguma alteração???");
    printf("\n|1-Sim|n2-Não\n|Opção:");
    scanf ("%d",&s_n);
}while(s_n==1);

}
//----------------------------------------------FIM DAS FUNÇÕES DE ALTERAÇÃO------------------------------------------------------

//---------------------------------------------MENU DE CONSULTA-------------------------------------------------------------------

void consCliente(FILE *file){

int tipo=1;
int opcao,s_n;
unsigned long id;
char cpf[12],prefixo[100];


do{
printf("\n|-----------------Menu de Consulta-----------------------|");
printf("\n|-----------Como deseja realizar a consulta?-------------|");
printf("\n|1-Consulta por id");
printf("\n|2-Consulta por CPF ");
printf("\n|3-Consulta por Prefixo");
printf("\n|4-Listar todos os clientes");
printf("\n|5-Voltar");
printf("\n|Opção:");
scanf("%d",&opcao);
switch (opcao){

case 1:
do{
printf("\n|-----------------Busca Por ID---------------------------|");
printf("\n|Forneça o id:");
scanf("%lu",&id);
if(id!=0)
busca_ID(file,id,tipo);
else
printf("ID NÃO ENCONTRADO");

    printf("\nFazer mais alguma consulta por ID???");
    printf("\n|1-Sim|n2-Não\n|Opção:");
    scanf ("%d",&s_n);

}while(s_n==1);

break;




case 2:


    do{
        printf("\n|-----------------Busca Por CPF---------------------------|");
         printf("\n|Forneça o CPF:");
          setbuf(stdin,NULL);
            fgets(cpf,12,stdin);
             retira_n(cpf);
             busca_cpf(file,cpf,tipo);


    printf("\nFazer mais alguma consulta por CPF???");
    printf("\n|1-Sim|n2-Não\n|Opção:");
    scanf ("%d",&s_n);

}while(s_n==1);
break;

case 3:


    do{    printf("\n|---------------Busca Por Prefixo-------------------------|");
         printf("\n|Forneça o Prefixo:");
          setbuf(stdin,NULL);
            fgets(prefixo,100,stdin);
             retira_n(prefixo);
               nome_maiusculo(prefixo);
                 busca_prefixo(file,prefixo,tipo);


    printf("\nFazer mais alguma consulta por prefixo???");
    printf("\n|1-Sim|n2-Não\n|Opção:");
    scanf ("%d",&s_n);

    }while(s_n==1);
break;


case 4:
 listagem(file,tipo);


break;
case 5:
break;
}

}while(opcao!=5);
}
//---------------------------------------------------FIM DAS FUNÇÕES DE CONSULTA--------------------------------------------------

//--------------------------------------------------------EXCLUSÃO----------------------------------------------------------------

void delCliente(FILE *file){
unsigned long id,posicao;
int achou,s_n;
t_cliente excluir;

do{
printf("\nForneça o Id do cliente que deseja excluir");
scanf("%lu",&id);

achou=0;
fseek(file,0,SEEK_SET);
while(fread(&excluir,sizeof(t_cliente),1,file)==1&&achou==0){

 if(id==excluir.id){
    achou=1;}else posicao++;
 }
  fseek(file,sizeof(t_cliente)*posicao,SEEK_SET);
    fread(&excluir,sizeof(t_cliente),1,file);
if(achou==1 && excluir.id!=0){
        printf("\n|---------------Dados atuais--------------------|");
    printf("\n|ID:%lu",excluir.id);
    printf("\n|Nome:%s",excluir.nome);
    printf("\n|CPF:%s",excluir.cpf);
    printf("\n|EMAIL:%s",excluir.email);
    printf("\n|TELEFONE:%s",excluir.telefone);
    printf("\n|-----------------------------------------------|");

    printf("\nDeseja Realmente excluir?");
    printf("\n|1-Sim|n2-Não\n|Opção:");
    scanf ("%d",&s_n);

    if(s_n==1){

        excluir.id=0;
        strcpy(excluir.cpf,"0");
        fseek(file,sizeof(t_cliente)*posicao,SEEK_SET);
        fwrite(&excluir,sizeof(t_cliente),1,file);

    }else printf("Nada foi excluido");
}else printf("ID NÃO ENCONTRADO");
    printf("\nFazer mais alguma exclusão???");
    printf("\n|1-Sim|n2-Não\n|Opção:");
    scanf ("%d",&s_n);

    }while(s_n==1);
//exclui os dados colocando o valor 0 para o id e para os campos unicos
}



