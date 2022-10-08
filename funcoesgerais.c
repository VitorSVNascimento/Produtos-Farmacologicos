#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "cliente.h"
#include "produtos.h"
#include "vendedor.h"
#include "fornecedor.h"
#include "validacao.h"
#include "funcoesgerais.h"

void busca_ID(FILE *file,unsigned long id,int tipo){
int achou;
t_cliente busca;
t_produto buscap;
t_vendedor buscav;
t_fornecedor buscaf;
unsigned long posicao;

achou =0;
posicao=0;
fseek(file,0,SEEK_SET);
switch (tipo){
//escolhe um dos tipos de struct e faz a listagem com base no id
case 1:
//------------------------------------------t_cliente-----------------------------------------------
while(fread(&busca,sizeof (t_cliente),1,file)==1&&achou==0){

if(id==busca.id){
  achou=1;}else posicao ++;

  }
    if(achou==1){


        fseek(file,sizeof(t_cliente)*posicao,SEEK_SET);
            fread(&busca,sizeof(t_cliente),1,file);




                printf("\n|---------------Resultado da busca--------------------|");
                printf("\n|ID:%lu",busca.id);
                printf("\n|Nome:%s",busca.nome);
                printf("\n|CPF:%s",busca.cpf);
                printf("\n|EMAIL:%s",busca.email);
                printf("\n|TELEFONE:%s",busca.telefone);
                printf("\n|-----------------------------------------------|");



    }else

printf("ID não encontrado");
break;

case 2:
    //--------------------------t_produto-----------------------------
while(fread(&buscap,sizeof (t_produto),1,file)==1&&achou==0){

if(id==buscap.id){
  achou=1;}else posicao ++;

  }
    if(achou==1){


        fseek(file,sizeof(t_produto)*posicao,SEEK_SET);
            fread(&buscap,sizeof(t_produto),1,file);




    printf("\n|---------------Resultado da busca--------------------|");
    printf("\n|ID:%lu",buscap.id);
    printf("\n|Nome:%s",buscap.nome);
    printf("\n|Quantidade em estoque:%d",buscap.quantidadeEstoque);
    printf("\n|Preço Unitario:R$%.2f",buscap.precoUnitario);
    printf("\n|-----------------------------------------------------|");


    }else

printf("ID não encontrado");
break;

case 3:
//-----------------------------------t_vendedor-----------------------------------------------
while(fread(&buscav,sizeof (t_vendedor),1,file)==1&&achou==0){

if(id==buscav.id){
  achou=1;}else posicao ++;

  }
    if(achou==1){


        fseek(file,sizeof(t_vendedor)*posicao,SEEK_SET);
            fread(&buscav,sizeof(t_vendedor),1,file);




                printf("\n|---------------Resultado da busca--------------------|");
                printf("\n|ID:%lu",buscav.id);
                printf("\n|Nome:%s",buscav.nome);
                printf("\n|CPF:%s",buscav.cpf);
                printf("\n|EMAIL:%s",buscav.email);
                printf("\n|TELEFONE:%s",buscav.telefone);
                printf("\n|-----------------------------------------------|");



    }else

printf("ID não encontrado");
break;

case 4:
 //----------------------------------------t_fornecedor-------------------------------------------------------------------------
while(fread(&buscaf,sizeof (t_fornecedor),1,file)==1&&achou==0){

if(id==buscaf.id){
  achou=1;}else posicao ++;

  }
    if(achou==1){


        fseek(file,sizeof(t_fornecedor)*posicao,SEEK_SET);
            fread(&buscaf,sizeof(t_fornecedor),1,file);




                printf("\n|---------------Resultado da busca--------------------|");
                printf("\n|ID:%lu",buscaf.id);
                printf("\n|Nome:%s",buscaf.nome);
                printf("\n|CPF:%s",buscaf.cnpj);
                printf("\n|EMAIL:%s",buscaf.email);
                printf("\n|-----------------------------------------------|");



    }else

printf("ID não encontrado");
break;


}
}

//-----------------------------------------------busca por cpf-----------------------------------------------------------------


void busca_cpf(FILE *file,char *cpf,int tipo){
int achou;
t_cliente busca;
t_vendedor buscav;
unsigned long posicao;

achou =0;
posicao=0;
//escolhe um dos tipos de struct e faz a listagem com base no cpf
switch(tipo){

case 1:

fseek(file,0,SEEK_SET);
while(fread(&busca,sizeof (t_cliente),1,file)==1&&achou==0){

if(strcmp(cpf,busca.cpf)==0){
  achou=1;}else posicao ++;

  }
            if(achou==1 && busca.id!=0){
                fseek(file,sizeof(t_cliente)*posicao,SEEK_SET);
                fread(&busca,sizeof(t_cliente),1,file);
                    printf("\n|---------------Resultado da busca--------------------|");
                    printf("\n|ID:%lu",busca.id);
                    printf("\n|Nome:%s",busca.nome);
                    printf("\n|CPF:%s",busca.cpf);
                    printf("\n|EMAIL:%s",busca.email);
                    printf("\n|TELEFONE:%s",busca.telefone);
                    printf("\n|-----------------------------------------------|");



        }else
        printf("CPF não encontrado");
break;
//-------------------------------------VENDEDOR-------------------------------------
case 3:

    fseek(file,0,SEEK_SET);
while(fread(&buscav,sizeof (t_vendedor),1,file)==1&&achou==0){

if(strcmp(cpf,buscav.cpf)==0){
  achou=1;}else posicao ++;

  }
            if(achou==1 && buscav.id!=0){
                fseek(file,sizeof(t_vendedor)*posicao,SEEK_SET);
                fread(&buscav,sizeof(t_vendedor),1,file);
                    printf("\n|---------------Resultado da busca--------------------|");
                    printf("\n|ID:%lu",buscav.id);
                    printf("\n|Nome:%s",buscav.nome);
                    printf("\n|CPF:%s",buscav.cpf);
                    printf("\n|EMAIL:%s",buscav.email);
                    printf("\n|TELEFONE:%s",buscav.telefone);
                    printf("\n|-----------------------------------------------|");



        }else
        printf("CPF não encontrado");


break;

}

}



//-------------------------------BUSCA POR PREFIXO-------------------------


void busca_prefixo(FILE *file,char *prefixo,int tipo){

int achou;
t_cliente busca;
t_produto buscap;
t_vendedor buscav;
t_fornecedor buscaf;
achou=0;

//escolhe um dos tipos de struct e faz a listagem com base no prefixo
fseek(file,0,SEEK_SET);
switch(tipo){
case 1:

printf("\n|---------------Resultado da busca--------------------|");
while(fread(&busca,sizeof (t_cliente),1,file)==1){

   if(strncmp(prefixo,busca.nome,strlen(prefixo))==0){

   if(busca.id!=0){

    achou=1;
                    printf("\n|ID:%lu",busca.id);
                    printf("\n|Nome:%s",busca.nome);
                    printf("\n|CPF:%s",busca.cpf);
                    printf("\n|EMAIL:%s",busca.email);
                    printf("\n|TELEFONE:%s",busca.telefone);
                    printf("\n|-----------------------------------------------|");
   }

   }




}
if (achou==0)
printf("Nenhum Cliente Encontrado");
break;

case 2:
printf("\n|---------------Resultado da busca--------------------|");
while(fread(&buscap,sizeof (t_produto),1,file)==1){

   if(strncmp(prefixo,buscap.nome,strlen(prefixo))==0){
    if(buscap.id!=0){
    achou=1;
    printf("\n|-----------------------------------------------|");
    printf("\n|ID:%lu",buscap.id);
    printf("\n|Nome:%s",buscap.nome);
    printf("\n|Quantidade em Estoque:%d",buscap.quantidadeEstoque);
    printf("\n|Preço Unitario:R$%.2f",buscap.precoUnitario);
    printf("\n|-----------------------------------------------|");
    }

   }




}
if (achou==0)
printf("Nenhum Produto Encontrado");
break;

case 3:

printf("\n|---------------Resultado da busca--------------------|");
while(fread(&buscav,sizeof (t_vendedor),1,file)==1){

   if(strncmp(prefixo,buscav.nome,strlen(prefixo))==0){
        if(buscav.id!=0){
    achou=1;
                    printf("\n|ID:%lu",buscav.id);
                    printf("\n|Nome:%s",buscav.nome);
                    printf("\n|CPF:%s",buscav.cpf);
                    printf("\n|EMAIL:%s",buscav.email);
                    printf("\n|TELEFONE:%s",buscav.telefone);
                    printf("\n|-----------------------------------------------|");
        }

   }




}
if (achou==0)
printf("Nenhum Cliente Encontrado");
break;

case 4:
printf("\n|---------------Resultado da busca--------------------|");
while(fread(&buscaf,sizeof (t_fornecedor),1,file)==1){

   if(strncmp(prefixo,buscaf.nome,strlen(prefixo))==0){
    if(buscaf.id!=0){
    achou=1;
                    printf("\n|ID:%lu",buscaf.id);
                    printf("\n|Nome:%s",buscaf.nome);
                    printf("\n|CNPJ:%s",buscaf.cnpj);
                    printf("\n|EMAIL:%s",buscaf.email);
                    printf("\n|-----------------------------------------------|");

    }
   }




}
if (achou==0)
printf("Nenhum Cliente Encontrado");

break;


}

}

//-----------------------------LISTAGEM------------------------------

void listagem(FILE *file,int tipo){

t_cliente busca;
t_produto buscap;
t_vendedor buscav;
t_fornecedor buscaf;
//escolhe um dos tipos de struct e faz a listagem percorrendo todo o arquivo
fseek(file,0,SEEK_SET);
switch (tipo){
 case 1:
 while(fread(&busca,sizeof (t_cliente),1,file)==1){
if(busca.id!=0){
    printf("\n|-----------------------------------------------|");
    printf("\n|ID:%lu",busca.id);
    printf("\n|Nome:%s",busca.nome);
    printf("\n|CPF:%s",busca.cpf);
    printf("\n|EMAIL:%s",busca.email);
    printf("\n|TELEFONE:%s",busca.telefone);
    printf("\n|-----------------------------------------------|");
}

 }
break;
 case 2:
    while(fread(&buscap,sizeof (t_produto),1,file)==1){
if(buscap.id!=0){
    printf("\n|-----------------------------------------------|");
    printf("\n|ID:%lu",buscap.id);
    printf("\n|Nome:%s",buscap.nome);
    printf("\n|Quantidade em Estoque:%d",buscap.quantidadeEstoque);
    printf("\n|Preço Unitario:R$%.2f",buscap.precoUnitario);
    printf("\n|-----------------------------------------------|");

}
 }

    break;

 case 3:

    while(fread(&buscav,sizeof (t_vendedor),1,file)==1){
if(buscav.id!=0){
    printf("\n|-----------------------------------------------|");
    printf("\n|ID:%lu",buscav.id);
    printf("\n|Nome:%s",buscav.nome);
    printf("\n|CPF:%s",buscav.cpf);
    printf("\n|EMAIL:%s",buscav.email);
    printf("\n|TELEFONE:%s",buscav.telefone);
    printf("\n|SENHA:%s",buscav.password);
    printf("\n|-----------------------------------------------|");
}

 }

  break;

 case 4:
       while(fread(&buscaf,sizeof (t_fornecedor),1,file)==1){
if(buscaf.id!=0){
    printf("\n|-----------------------------------------------|");
    printf("\n|ID:%lu",buscaf.id);
    printf("\n|Nome:%s",buscaf.nome);
    printf("\n|CNPJ:%s",buscaf.cnpj);
    printf("\n|EMAIL:%s",buscaf.email);
    printf("\n|-----------------------------------------------|");
}

 }
break;

}
}

void busca_cnpj(FILE *file,char *cnpj){
int achou;
t_fornecedor busca;
unsigned long posicao;

achou =0;
posicao=0;
fseek(file,0,SEEK_SET);
while(fread(&busca,sizeof (t_fornecedor),1,file)==1&&achou==0){

if(strcmp(cnpj,busca.cnpj)==0){
  achou=1;}else posicao ++;

  }
            if(achou==1 && busca.id!=0){
                fseek(file,sizeof(t_fornecedor)*posicao,SEEK_SET);
                fread(&busca,sizeof(t_fornecedor),1,file);
                    printf("\n|---------------Resultado da busca--------------------|");
                    printf("\n|ID:%lu",busca.id);
                    printf("\n|Nome:%s",busca.nome);
                    printf("\n|CNPJ:%s",busca.cnpj);
                    printf("\n|EMAIL:%s",busca.email);
                    printf("\n|-----------------------------------------------|");



        }else
        printf("CNPJ não encontrado");







}

//----------------------------------VERIFICA SENHA-----------------------------

int verifica_senha(FILE *file,char *senha,unsigned long posicao){
//recebe a posição do vendedor e confere se a senha fornecida bate com a da posição
t_vendedor busca;

                fseek(file,sizeof(t_vendedor)*posicao,SEEK_SET);
                fread(&busca,sizeof(t_vendedor),1,file);

if(strcmp(senha,busca.password)==0){
    return 1;

}else
return 0;

}


void separa_data(char *data,int *dia,int *mes ,int *ano){
//tranforma um char data em int separando dia mes e ano

*dia=(data[0]-48)*10+(data[1]-48);
*mes=(data[3]-48)*10+(data[4]-48);
*ano=(data[6]-48)*1000+(data[7]-48)*100+(data[8]-48)*10+(data[9]-48);
}

