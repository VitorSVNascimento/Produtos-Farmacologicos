#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "validacao.h"
#include "vendedor.h"
#include "fornecedor.h"
#include "entradas.h"
#include "funcoesgerais.h"





void mFornecedor(){
int sair;
FILE *ff;

ff=fopen("fornecedor.dat","rb+");
if(ff==NULL)
ff=fopen("fornecedor.dat","wb+");
if(ff!=NULL){

do{
 printf("\n|----------------Menu de Fornecedor-----------------------");
 printf("\n|O que deseja Fazer");
 printf("\n|1-Cadastrar Fornecedor");
 printf("\n|2-Alterar Fornecedor");
 printf("\n|3-Consultar Fornecedor");
 printf ("\n|4Excluir Fornecedor");
 printf ("\n|5-Menu pricipal");
 printf("\n|Opção:");
 scanf ("%d",&sair);


switch(sair){

case 1:

cadFornecedor(ff);
break;

case 2:
alterFornecedor(ff);


break;
case 3:
consFornecedor(ff);

break;


}


}while(sair!=5);


fclose(ff);





}else
printf("NÃO FOI POSSIVEL ABRIR O ARQUIVO");
 return;
}

//=============================FUNÇÃO DE CADASTRO=======================

void cadFornecedor(FILE *file){
t_fornecedor novo;
int menu,teste;
unsigned long posicao;

do{


novo.id=novo_IDV(file);
printf("\nID do fornecedor:|%lu",novo.id);

recebe_cnpj(novo.cnpj,file);

do{recebe_nome(novo.nome);
  teste=nome_repetido(novo.nome,file);
        if(teste==0)
            printf("\nNome Não Pode ser repetido");


}while(teste==0);

recebe_email(novo.email);

setbuf(stdin,NULL);

posicao=novo.id-1;

fseek(file,sizeof(t_vendedor)*posicao,SEEK_SET);
    fwrite(&novo,sizeof(t_fornecedor),1,file);
        printf("\n----------------------------------CADASTRO CONCLUIDO------------------------------------------------------------");
printf("\nDeseja continuar cadastrando???");
printf("\n1-Sim|2-Não");
printf("\nOpção:");
scanf("%d",&menu);


}while(menu==1);
}

//================================FUNÇÃO DE ID=======================

unsigned long novo_IDF(FILE *file){

unsigned long id;
t_fornecedor novo;

id=1;
fseek(file,0,SEEK_SET);
while(fread(&novo,sizeof (t_vendedor),1,file)==1){
if(novo.id==0)
    break;
id++;

}

return id;
}

//=================================CNPJ REPETIDO===============================

int cnpj_Repetido(char *cnpj,FILE *file){
//retorna 0 se for repetido
t_fornecedor novo;

fseek(file,0,SEEK_SET);
while(fread(&novo,sizeof(t_fornecedor),1,file)==1){

    if(strcmp(cnpj,novo.cnpj)==0)
    return 0;
}
return 1;
}
//================================NOME REPETIDO=======================
int nome_repetido(char *nome,FILE *file){
    //retorna 0 se for repetido
t_fornecedor novo;
fseek(file,0,SEEK_SET);
while(fread(&novo,sizeof(t_fornecedor),1,file)==1){

    if(strcmp(nome,novo.nome)==0)
    return 0;
}
return 1;
}
//================================ALTERAÇÃO===========================

void alterFornecedor(FILE *file){

unsigned long id,posicao;
int achou,s_n;

t_fornecedor novo;

do{
printf("\n-----------------Menu de Alteração de Fornecedor-----------------------");
printf("\nForneça o Id que deseja alterar:");
scanf("%lu",&id);
if(id!=0){
achou =0;
 fseek(file,0,SEEK_SET);
  while(fread(&novo,sizeof (t_fornecedor),1,file)==1&&achou==0){

if(id==novo.id){
  achou=1;}else posicao ++;

  }
  if(achou==1){
fseek(file,sizeof(t_fornecedor)*posicao,SEEK_SET);
fread(&novo,sizeof(t_fornecedor),1,file);

    printf("\n|---------------Dados atuais--------------------|");
    printf("\n|ID:%lu",novo.id);
    printf("\n|Nome:%s",novo.nome);
    printf("\n|CPF:%s",novo.cnpj);
    printf("\n|EMAIL:%s",novo.email);
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


fseek(file,sizeof(t_fornecedor)*posicao,SEEK_SET);
fwrite(&novo,sizeof(t_fornecedor),1,file);

    }
    printf("\n|---------------Alteração Concluida--------------------|");
    printf("\n|-----------------Dados atuais-------------------------|");
    printf("\n|ID:%lu",novo.id);
    printf("\n|Nome:%s",novo.nome);
    printf("\n|CPF:%s",novo.cnpj);
    printf("\n|EMAIL:%s",novo.email);
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

//==================================CONSULTA========================

void consFornecedor(FILE *file){
int tipo=4;
int opcao,s_n;
unsigned long id;
char cnpj[15],prefixo[100];

do{
 printf("\n|-----------------Menu de Consulta-----------------------|");
printf("\n|-----------Como deseja realizar a consulta?-------------|");
printf("\n|1-Consulta por id");
printf("\n|2-Consulta por CNPJ ");
printf("\n|3-Consulta por Prefixo");
printf("\n|4-Listar todos os Fornecedores");
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
printf("\nID não encontrado");

    printf("\nFazer mais alguma consulta por ID???");
    printf("\n|1-Sim|n2-Não\n|Opção:");
    scanf ("%d",&s_n);

}while(s_n==1);

break;




case 2:


    do{
        printf("\n|-----------------Busca Por CNPJ---------------------------|");
         printf("\n|Forneça o CNPJ:");
          setbuf(stdin,NULL);
            fgets(cnpj,15,stdin);
             retira_n(cnpj);
             busca_cnpj(file,cnpj);


    printf("\nFazer mais alguma consulta por CNPJ???");
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

}while (opcao!=5);
}

void delFornecedor(FILE *file){
unsigned long id,posicao;
int achou,s_n;
t_fornecedor excluir;

do{
printf("\nForneça o Id do fornecedor que deseja excluir");
scanf("%lu",&id);

achou=0;
fseek(file,0,SEEK_SET);
while(fread(&excluir,sizeof(t_fornecedor),1,file)==1&&achou==0){

 if(id==excluir.id){
    achou=1;}else posicao++;
 }
  fseek(file,sizeof(t_fornecedor)*posicao,SEEK_SET);
    fread(&excluir,sizeof(t_fornecedor),1,file);
if(achou==1 && excluir.id!=0){
        printf("\n|---------------Dados atuais--------------------|");
    printf("\n|ID:%lu",excluir.id);
    printf("\n|Nome:%s",excluir.nome);
    printf("\n|CPF:%s",excluir.cnpj);
    printf("\n|EMAIL:%s",excluir.email);
    printf("\n|-----------------------------------------------|");

    printf("\nDeseja Realmente excluir?");
    printf("\n|1-Sim|n2-Não\n|Opção:");
    scanf ("%d",&s_n);

    if(s_n==1){

        excluir.id=0;
        strcpy(excluir.cnpj,"0");
        strcpy(excluir.nome,"0");
        fseek(file,sizeof(t_fornecedor)*posicao,SEEK_SET);
        fwrite(&excluir,sizeof(t_fornecedor),1,file);

    }else printf("Nada foi excluido");
}else printf("ID NÃO ENCONTRADO");
    printf("\nFazer mais alguma exclusão???");
    printf("\n|1-Sim|n2-Não\n|Opção:");
    scanf ("%d",&s_n);

    }while(s_n==1);


}




