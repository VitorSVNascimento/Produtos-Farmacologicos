#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "vendedor.h"
#include "entradas.h"
#include "validacao.h"
#include "funcoesgerais.h"
void mVendedor(){

int sair;
FILE *fv;

fv=fopen("vendedor.dat","rb+");
if(fv==NULL)
fv=fopen("vendedor.dat","wb+");
if(fv!=NULL){

do{


   printf("\n|----------------Menu de Vendedor-----------------------");
 printf("\n|O que deseja Fazer");
 printf("\n|1-Cadastrar Vendedor");
 printf("\n|2-Alterar Vendedor");
 printf("\n|3-Consultar Vendedor");
 printf ("\n|4Excluir Vendedor");
 printf ("\n|5-Menu pricipal");
 printf("\n|Opção:");
 scanf ("%d",&sair);

 switch(sair){


 case 1:
     cadVendedor(fv);
 break;
 case 2:
    alterVendedor(fv);
break;
 case 3:
    consVendedor(fv);
    break;
 case 4:
    delVendedor(fv);
    break;
 }

}while(sair!=5);





fclose(fv);
}else
printf("NÃO FOI POSSIVEL ABRIR O ARQUIVO!!");
return;
}

//---------------------CADASTRO------------------------

void cadVendedor(FILE *file){

t_vendedor novo;
int menu,teste,tipo=3;
unsigned long posicao;

do{
novo.id= novo_IDV(file);
printf("\nID do vendedor:|%lu",novo.id);
recebe_nome(novo.nome);

recebe_cpf(novo.cpf,file,tipo);

do{recebe_email(novo.email);

   teste=email_repetido(novo.email,file);

if(teste==0)
    printf("\n--------Email já cadstrado------------");

}while(teste==0);

recebe_telefone(novo.telefone);

 printf("\nDefina uma senha:|");
 setbuf(stdin,NULL);
 fgets(novo.password,20,stdin);
 retira_n(novo.password);
 nome_maiusculo(novo.password);


setbuf(stdin,NULL);

posicao=novo.id-1;
fseek(file,sizeof(t_vendedor)*posicao,SEEK_SET);
    fwrite(&novo,sizeof(t_vendedor),1,file);
        printf("\n----------------------------------CADASTRO CONCLUIDO------------------------------------------------------------");


printf("\nDeseja continuar cadastrando???");
printf("\n1-Sim|2-Não");
printf("\nOpção:");
scanf("%d",&menu);

}while(menu==1);


}


//----------------------------GERA ID---------------------

unsigned long novo_IDV(FILE *file){

unsigned long id;
t_vendedor novo;

id=1;
fseek(file,0,SEEK_SET);
while(fread(&novo,sizeof (t_vendedor),1,file)==1){

if(novo.id==0)
break;

id++;

}

return id;
}
//-------------------------------FUNÇÃO DE EMAIL REPETIDO------------

int email_repetido(char *email,FILE *file){

t_vendedor novo;

fseek(file,0,SEEK_SET);
while(fread(&novo,sizeof (t_vendedor),1,file)==1){

 if(strcmp(email,novo.email)==0)
    return 0;

//verifica se email ja existe em determinado arquivo
}
return 1;

}
//--------------------------------------------------------MENU DE ALTERAÇÃO-------------------------------------------------------------------------------



void alterVendedor(FILE *file){

unsigned long id,posicao;
int achou,s_n,teste,altsenha=0,i;
char senha[20];

t_vendedor novo;

do{

   printf("\n----------------------Menu de Alteração de vendedor--------");

   printf("\nForneça o Id que deseja alterar");
   scanf("%lu",&id);
   if(id!=0){
    achou=0;
    posicao=0;
    fseek(file,0,SEEK_SET);
        while(fread(&novo,sizeof (t_vendedor),1,file)==1&&achou==0){

                if(id==novo.id){
                achou=1;}else posicao ++;

     }
            if(achou==1){


                fseek(file,sizeof(t_vendedor)*posicao,SEEK_SET);
                    fread(&novo,sizeof(t_vendedor),1,file);

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

                            if(s_n==1){
                                    do{recebe_email(novo.email);

                                    teste=email_repetido(novo.email,file);

                                            if(teste==0)
                                                printf("\n--------Email já cadstrado------------");

}while(teste==0);

        }

    printf("\nDeseja alterar o telefone???");

    printf("\n|1-Sim|n2-Não\n|Opção:");
    scanf("%d",&s_n);

        if(s_n==1)
        recebe_telefone(novo.telefone);
    printf("\nDeseja alterar a senha???");
    printf("\n|1-Sim|n2-Não\n|Opção:");
    scanf("%d",&s_n);

    if(s_n==1){
        i=3;


            do{
        teste=0;
        printf("Digite a senha antiga:");
        setbuf(stdin,NULL);
        fgets(senha,20,stdin);
        retira_n(senha);
        nome_maiusculo(senha);
                teste=verifica_senha(file,senha,posicao);
                    printf("\nTeste %d",teste);
                        if(teste==1){
                            altsenha=1;
                                printf("Digite a nova senha:");
                                    setbuf(stdin,NULL);
                                        fgets(novo.password,20,stdin);
                                          retira_n(novo.password);
                            nome_maiusculo(novo.password);
                                break;


                }else{
                    i--;
                        printf("\nSenha incorreta!!!");
                            printf("\n%d tentativas restantes",i);

        }
     }while(i>0);

    }


fseek(file,sizeof(t_vendedor)*posicao,SEEK_SET);
fwrite(&novo,sizeof(t_vendedor),1,file);

    }
    printf("\n|---------------Alteração Concluida--------------------|");
    printf("\n|-----------------Dados atuais-------------------------|");
    printf("\n|ID:%lu",novo.id);
    printf("\n|Nome:%s",novo.nome);
    printf("\n|CPF:%s",novo.cpf);
    printf("\n|EMAIL:%s",novo.email);
    printf("\n|TELEFONE:%s",novo.telefone);
    if(altsenha==1)
    printf("\n|Nova Senha:%s",novo.password);
    printf("\n|------------------------------------------------------|");




    }else
    printf("\nID Não Encontrado");
   }else
   printf("\nID Não Encontrado");

       printf("\nFazer mais alguma alteração???");
    printf("\n|1-Sim|n2-Não\n|Opção:");
    scanf ("%d",&s_n);

}while(s_n==1);
}

//===========================================================MENU DE CONSULTA===============================================================================

void consVendedor(FILE *file){

int tipo=3;
int opcao,s_n;
unsigned long id;
char cpf[12],prefixo[100];

do{
printf("\n|-----------------Menu de Consulta-----------------------|");
printf("\n|-----------Como deseja realizar a consulta?-------------|");
printf("\n|1-Consulta por id");
printf("\n|2-Consulta por CPF ");
printf("\n|3-Consulta por Prefixo");
printf("\n|4-Listar todos os vendedores");
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
printf("ID não encontrado");

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
        do{printf("\n|---------------Busca Por Prefixo-------------------------|");
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

void delVendedor(FILE *file){
unsigned long id,posicao;
int achou,s_n;
t_vendedor excluir;

do{
printf("\nForneça o Id do vendedor que deseja excluir");
scanf("%lu",&id);

achou=0;
fseek(file,0,SEEK_SET);
posicao=0;
while(fread(&excluir,sizeof(t_vendedor),1,file)==1&&achou==0){

 if(id==excluir.id){
    achou=1;}else posicao++;
 }
  fseek(file,sizeof(t_vendedor)*posicao,SEEK_SET);
    fread(&excluir,sizeof(t_vendedor),1,file);
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
        strcpy(excluir.email,"0");
        fseek(file,sizeof(t_vendedor)*posicao,SEEK_SET);
        fwrite(&excluir,sizeof(t_vendedor),1,file);

    }else printf("Nada foi excluido");
}else printf("ID NÃO ENCONTRADO");
    printf("\nFazer mais alguma exclusão???");
    printf("\n|1-Sim|n2-Não\n|Opção:");
    scanf ("%d",&s_n);

    }while(s_n==1);


}
