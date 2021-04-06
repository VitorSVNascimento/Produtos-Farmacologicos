#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "produtos.h"
#include "vendedor.h"
#include "fornecedor.h"
#include "validacao.h"
#include "vendas.h"
#include "compra.h"
#include "relatorios.h"
#include "funcoesgerais.h"


void mRelatorios(){
int opcao;

do{printf("\n|Qual relatório deseja gerar");
printf("\n|1-Dados de uma nota Fiscal e os itens associados a ela");
printf("\n|2-Dados de uma compra e os itens associados a ela");
printf("\n|3-Compras efetuadas por um cliente em uma data específica, bem como em um intervalo de datas");
printf("\n|4-Vendas efetuadas por um vendedor em um dia específico");
printf("\n|5-Vendas realizadas por um vendedor em um determinado mês");
printf("\n|6-O(os) vendedor(es) com maior valor de venda em um determinado mês");
printf("\n|7-O vendedor(es) com maior valor de venda em um intervalo de datas");
printf("\n|8-Histórico de valor de venda de um determinado produto");
printf("\n|9-Sair");
printf("\n|Opção:|");
scanf("%d",&opcao);

switch(opcao){

case 1:
 relatorio_um();

    break;


case 2:
    relatorio_dois();
    break;
case 3:
    relatorio_tres();
    break;
case 4:
    relatorio_quatro();
    break;
case 5:
    relatorio_cinco();
    break;
case 6:

    relatorio_seis();

    break;
case 7:
    relatorio_sete();
    break;
case 8:
        relatorio_oito();
    break;
}

}while(opcao!=9);


}



void relatorio_um(){
FILE *fv,*fc,*fnf,*finf,*arquivo;
char nome_arquivo[50];

t_nota_fiscal nota;
t_item_nota_fiscal item;
t_vendedor vendedor;
t_cliente cliente;
int opcao,achou,s_n,vazio;
unsigned long id,posicao;


fnf=fopen("NotaFiscal.dat","rb+");
if(fnf==NULL)
return;



fc=fopen("cliente.dat","rb+");
if(fc==NULL)
return;



fv=fopen("vendedor.dat","rb+");
if(fv==NULL)
return;


finf=fopen("ItemNotaFiscal.dat","rb+");
if(finf==NULL)
return;


do{
  printf("\nForneça o id da nota:");
  scanf("%lu",&id);
  achou=0;
  fseek(fnf,0,SEEK_SET);
  while(fread(&nota,sizeof(t_nota_fiscal),1,fnf)==1 && achou==0){
    if(id==nota.id){
    achou=1;
    break;
    }else posicao++;
  }

  if(achou==1){



        printf("\nComo deseja receber o relatorio??");
        printf("\n1-Tela|2-Arquivo de texto??");
        printf("\nComo deseja receber o relatorio??");
        printf("\nOpção:|");
        scanf("%d",&opcao);

        if(opcao==1){

            printf("\n|------------Louco Das Pedras------------------");
            printf("\n|ID Nota Fiscal|%lu|",id);
            printf("\n|Data:%s",nota.dataCompra);
            fseek(fv,sizeof(t_vendedor)*(nota.idVendedor-1),SEEK_SET);
            fread(&vendedor,sizeof(t_vendedor),1,fv);
            printf("\n|Id Vendedor|%lu|Nome do Vendedor:%s",nota.idVendedor,vendedor.nome);
            fseek(fc,sizeof(t_cliente)*(nota.idCliente-1),SEEK_SET);
            fread(&cliente,sizeof(t_cliente),1,fc);
            printf("\n|ID Cliente|%lu|Nome do cliente:%s",nota.idCliente,cliente.nome);
            printf("\n|=============Itens da nota====================");

            fseek(finf,0,SEEK_SET);
            while(fread(&item,sizeof(t_item_nota_fiscal),1,finf)==1){
              if(item.idNota==nota.id){
                printf("\nId do produto:%lu",item.idDoProduto);
                printf("\nquantidade do produto:%d",item.quantidade);
                printf("\nvalor unitario:%.2f",item.valorVenda);
            printf("\n|----------------------------------------------");

              }

                }
            printf("\nValor total:|R$%.2f|",nota.valorTotal);
            printf("\n|---------------------------------------------");



        }else{
        do{printf("\nForneça o nome do arquivo(sem extensão)");
        setbuf(stdin,NULL);
        fgets(nome_arquivo,50,stdin);
        vazio=retira_n(nome_arquivo);
        if(vazio==1){
            strcat(nome_arquivo,".txt");
            arquivo=fopen(nome_arquivo,"r+");
            if(arquivo==NULL)
            arquivo=fopen(nome_arquivo,"w+");
            if(arquivo==NULL)
            return;

            fprintf(arquivo,"\n|------------Louco Das Pedras------------------");
            fprintf(arquivo,"\n|ID Nota Fiscal|%lu|",id);
            fprintf(arquivo,"\n|Data:%s",nota.dataCompra);
            fseek(fv,sizeof(t_vendedor)*(nota.idVendedor-1),SEEK_SET);
            fread(&vendedor,sizeof(t_vendedor),1,fv);
            fprintf(arquivo,"\n|Id Vendedor|%lu|Nome do Vendedor:%s",nota.idVendedor,vendedor.nome);
            fseek(fc,sizeof(t_cliente)*(nota.idCliente-1),SEEK_SET);
            fread(&cliente,sizeof(t_cliente),1,fc);
            fprintf(arquivo,"\n|ID Cliente|%lu|Nome do cliente:%s",nota.idCliente,cliente.nome);
            fprintf(arquivo,"\n|=============Itens da nota====================");

            fseek(finf,0,SEEK_SET);
            while(fread(&item,sizeof(t_item_nota_fiscal),1,finf)==1){
              if(item.idNota==nota.id){
                fprintf(arquivo,"\nId do produto:%lu",item.idDoProduto);
                fprintf(arquivo,"\nquantidade do produto:%d",item.quantidade);
                fprintf(arquivo,"\nvalor unitario:%.2f",item.valorVenda);
            fprintf(arquivo,"\n|----------------------------------------------");
              }

                }
            fprintf(arquivo,"\nValor total:|R$%.2f|",nota.valorTotal);
            fprintf(arquivo,"\n|---------------------------------------------");

            fclose(arquivo);


        }else
        printf("\n=======NOME NÃO PODE SER VAZIO=============");
        }while(vazio==0);
        }


  }else{
printf("\n=====ID NÃO ENCONTRADO=======");

  }

  printf("\nDeseja Voltar ao menu de relatórios???");
  printf("\n1-Sim|2-Não");
  printf("\nOpção:|");
  scanf("%d",&s_n);


}while (s_n!=1);


fclose(fv);
fclose(fc);
fclose(finf);
fclose(fnf);
return;




}


void relatorio_dois(){

FILE *ff,*fnc,*finc,*arquivo;
char nome_arquivo[50];

nota_compra nota;
item_nota_compra item;
t_fornecedor fornecedor;
int opcao,achou,s_n,vazio;
unsigned long id,posicao;


fnc=fopen("NotaCompra.dat","rb+");
if(fnc==NULL)
return;


ff=fopen("fornecedor.dat","rb+");
if(ff==NULL)
return;


finc=fopen("ItemNotaCompra.dat","rb+");
if(finc==NULL)
return;


do{
  printf("\nForneça o id da nota:");
  scanf("%lu",&id);
  achou=0;
  fseek(fnc,0,SEEK_SET);
  while(fread(&nota,sizeof(nota_compra),1,fnc)==1 && achou==0){
    if(id==nota.id){
    achou=1;
    break;
    }else posicao++;
  }

  if(achou==1){



        printf("\nComo deseja receber o relatorio??");
        printf("\n1-Tela|2-Arquivo de texto??");
        printf("\nComo deseja receber o relatorio??");
        printf("\nOpção:|");
        scanf("%d",&opcao);

        if(opcao==1){

            printf("\n|------------Nota De Compra------------------");
            printf("\n|ID Nota Compra|%lu|",id);
            printf("\n|Data:%s",nota.dataCompra);
            fseek(ff,sizeof(t_fornecedor)*(nota.idFornecedor-1),SEEK_SET);
            fread(&fornecedor,sizeof(t_fornecedor),1,ff);
            printf("\n|Id Fornecedor|%lu|Nome do Fornecedor:%s",nota.idFornecedor,fornecedor.nome);

            printf("\n|=============Itens da nota====================");

            fseek(finc,0,SEEK_SET);
            while(fread(&item,sizeof(item_nota_compra),1,finc)==1){
              if(item.idNotaCompra==nota.id){
                printf("\nId do produto:%lu",item.idProduto);
                printf("\nquantidade do produto:%d",item.quantidade);
                printf("\nvalor unitario:%.2f",item.valorUnitario);
            printf("\n|----------------------------------------------");

              }

                }
            printf("\nValor total:|R$%.2f|",nota.valorTotal);
            printf("\n|---------------------------------------------");



        }else{
        do{printf("\nForneça o nome do arquivo(sem extensão)");
        setbuf(stdin,NULL);
        fgets(nome_arquivo,50,stdin);
        vazio=retira_n(nome_arquivo);
        if(vazio==1){
            strcat(nome_arquivo,".txt");
            arquivo=fopen(nome_arquivo,"r+");
            if(arquivo==NULL)
            arquivo=fopen(nome_arquivo,"w+");
            if(arquivo==NULL)
            return;

            fprintf(arquivo,"\n|------------Nota Compra------------------");
            fprintf(arquivo,"\n|ID Nota Fiscal|%lu|",id);
            fprintf(arquivo,"\n|Data:%s",nota.dataCompra);
            fseek(ff,sizeof(t_fornecedor)*(nota.idFornecedor-1),SEEK_SET);
            fread(&fornecedor,sizeof(t_fornecedor),1,ff);
            fprintf(arquivo,"\n|Id Vendedor|%lu|Nome do Vendedor:%s",nota.idFornecedor,fornecedor.nome);
            fprintf(arquivo,"\n|=============Itens da nota====================");

            fseek(finc,0,SEEK_SET);
            while(fread(&item,sizeof(t_item_nota_fiscal),1,finc)==1){
              if(item.idNotaCompra==nota.id){
                fprintf(arquivo,"\nId do produto:%lu",item.idProduto);
                fprintf(arquivo,"\nquantidade do produto:%d",item.quantidade);
                fprintf(arquivo,"\nvalor unitario:%.2f",item.valorUnitario);
            fprintf(arquivo,"\n|----------------------------------------------");
              }

                }
            fprintf(arquivo,"\nValor total:|R$%.2f|",nota.valorTotal);
            fprintf(arquivo,"\n|---------------------------------------------");

            fclose(arquivo);


        }else
        printf("\n=======NOME NÃO PODE SER VAZIO=============");
        }while(vazio==0);
        }


  }else{
printf("\n=====ID NÃO ENCONTRADO=======");

  }

  printf("\nDeseja Voltar ao menu de relatórios???");
  printf("\n1-Sim|2-Não");
  printf("\nOpção:|");
  scanf("%d",&s_n);


}while (s_n!=1);


fclose(ff);
fclose(finc);
fclose(fnc);
return;
}



void relatorio_oito(){
unsigned long id,posicao;
historico_preco historico;
int opcao,achou,vazio;
char nome_arquivo[50];
FILE *fh,*arquivo;

fh=fopen("HistoricoPreco.dat","rb+");
if(fh==NULL)
return;


do{
  printf("\nForneça o id do produto:");
  scanf("%lu",&id);
  achou=0;
  fseek(fh,0,SEEK_SET);
  while(fread(&historico,sizeof(historico_preco),1,fh)==1 && achou==0){
    if(id==historico.idProduto){
    achou=1;
    break;
    }else posicao++;
  }

    if(achou==1){printf("\nComo deseja receber o relatorio??");
        printf("\n1-Tela|2-Arquivo de texto??");
        printf("\nComo deseja receber o relatorio??");
        printf("\nOpção:|");
        scanf("%d",&opcao);

        if(opcao==1){
                printf("\n|-------------HISTORICO-------------");
                printf("\n|ID do produto:%lu",id);
                fseek(fh,0,SEEK_SET);
                while(fread(&historico,sizeof(historico_preco),1,fh)==1){
                if(id==historico.idProduto){
                    printf("\n|Data da alteração:|%s",historico.dataAlteracao);
                    printf("\n|Valor:|%.2f",historico.valor);
                printf("\n|-----------------------------------");

                }


                }



        }else{

            do{printf("\nForneça o nome do arquivo(sem extensão)");
        setbuf(stdin,NULL);
        fgets(nome_arquivo,50,stdin);
        vazio=retira_n(nome_arquivo);
                if(vazio==1){strcat(nome_arquivo,".txt");
            arquivo=fopen(nome_arquivo,"r+");
            if(arquivo==NULL)
            arquivo=fopen(nome_arquivo,"w+");
            if(arquivo==NULL)
            return;



                                fprintf(arquivo,"\n|-------------HISTORICO-------------");
                fprintf(arquivo,"\n|ID do produto:%lu",id);
                fseek(fh,0,SEEK_SET);
                while(fread(&historico,sizeof(historico_preco),1,fh)==1){
                if(id==historico.idProduto){
                    fprintf(arquivo,"\n|Data da alteração:|%s",historico.dataAlteracao);
                    fprintf(arquivo,"\n|Valor:|%.2f",historico.valor);
                fprintf(arquivo,"\n|-----------------------------------");




                }
        }
         fclose(arquivo);
                }else printf("\n=======NOME NÃO PODE SER VAZIO=========");



        }while(vazio==0);




        }
    }else
    printf("\n===========ID INVÁLIDA==========");



}while(achou==0);

fclose(fh);




}

void relatorio_quatro(){

FILE *fv,*fc,*fnf,*finf,*arquivo;
char nome_arquivo[50],data[11];

t_nota_fiscal nota;
t_item_nota_fiscal item;
t_vendedor vendedor;
t_cliente cliente;
int opcao,achou,s_n,vazio,teste;
unsigned long id,posicao;


fnf=fopen("NotaFiscal.dat","rb+");
if(fnf==NULL)
return;



fc=fopen("cliente.dat","rb+");
if(fc==NULL)
return;



fv=fopen("vendedor.dat","rb+");
if(fv==NULL)
return;


finf=fopen("ItemNotaFiscal.dat","rb+");
if(finf==NULL)
return;


do{
  printf("\nForneça o id do Vendedor:");
  scanf("%lu",&id);
  achou=0;
  fseek(fv,0,SEEK_SET);
  while(fread(&vendedor,sizeof(t_vendedor),1,fv)==1 && achou==0){
    if(id==vendedor.id){
    achou=1;
    break;
    }else posicao++;
  }

  if(achou==1){

        do{teste=recebe_data(data);
if(teste==0){
    printf("\n====Data Invalida====");
}

}while(teste==0);



        printf("\nComo deseja receber o relatorio??");
        printf("\n1-Tela|2-Arquivo de texto??");
        printf("\nComo deseja receber o relatorio??");
        printf("\nOpção:|");
        scanf("%d",&opcao);

        if(opcao==1){
                fseek(fnf,0,SEEK_SET);
                while(fread(&nota,sizeof(t_nota_fiscal),1,fnf)==1){
                        if(id==nota.idVendedor&&strncmp(nota.dataCompra,data,strlen(nota.dataCompra))==0){
            printf("\n|------------Louco Das Pedras------------------");
            printf("\n|ID Nota Fiscal|%lu|",nota.id);
            printf("\n|Data:%s",nota.dataCompra);
            fseek(fv,sizeof(t_vendedor)*(nota.idVendedor-1),SEEK_SET);
            fread(&vendedor,sizeof(t_vendedor),1,fv);
            printf("\n|Id Vendedor|%lu|Nome do Vendedor:%s",nota.idVendedor,vendedor.nome);
            fseek(fc,sizeof(t_cliente)*(nota.idCliente-1),SEEK_SET);
            fread(&cliente,sizeof(t_cliente),1,fc);
            printf("\n|ID Cliente|%lu|Nome do cliente:%s",nota.idCliente,cliente.nome);
            printf("\n|=============Itens da nota====================");

            fseek(finf,0,SEEK_SET);
            while(fread(&item,sizeof(t_item_nota_fiscal),1,finf)==1){
              if(item.idNota==nota.id){
                printf("\nId do produto:%lu",item.idDoProduto);
                printf("\nquantidade do produto:%d",item.quantidade);
                printf("\nvalor unitario:%.2f",item.valorVenda);
            printf("\n|----------------------------------------------");

              }

                }
            printf("\nValor total:|R$%.2f|",nota.valorTotal);
            printf("\n|---------------------------------------------");
                        }
        }


        }else{
        do{printf("\nForneça o nome do arquivo(sem extensão)");
        setbuf(stdin,NULL);
        fgets(nome_arquivo,50,stdin);
        vazio=retira_n(nome_arquivo);
        if(vazio==1){
            strcat(nome_arquivo,".txt");
            arquivo=fopen(nome_arquivo,"r+");
            if(arquivo==NULL)
            arquivo=fopen(nome_arquivo,"w+");
            if(arquivo==NULL)
            return;
                fseek(fnf,0,SEEK_SET);

            while(fread(&nota,sizeof(t_nota_fiscal),1,fnf)==1){
                     if(id==nota.idVendedor&&strncmp(nota.dataCompra,data,strlen(nota.dataCompra))==0){
            fprintf(arquivo,"\n|------------Louco Das Pedras------------------");
            fprintf(arquivo,"\n|ID Nota Fiscal|%lu|",nota.id);
            fprintf(arquivo,"\n|Data:%s",nota.dataCompra);
            fseek(fv,sizeof(t_vendedor)*(nota.idVendedor-1),SEEK_SET);
            fread(&vendedor,sizeof(t_vendedor),1,fv);
            fprintf(arquivo,"\n|Id Vendedor|%lu|Nome do Vendedor:%s",nota.idVendedor,vendedor.nome);
            fseek(fc,sizeof(t_cliente)*(nota.idCliente-1),SEEK_SET);
            fread(&cliente,sizeof(t_cliente),1,fc);
            fprintf(arquivo,"\n|ID Cliente|%lu|Nome do cliente:%s",nota.idCliente,cliente.nome);
            fprintf(arquivo,"\n|=============Itens da nota====================");

            fseek(finf,0,SEEK_SET);
            while(fread(&item,sizeof(t_item_nota_fiscal),1,finf)==1){
              if(item.idNota==nota.id){
                fprintf(arquivo,"\nId do produto:%lu",item.idDoProduto);
                fprintf(arquivo,"\nquantidade do produto:%d",item.quantidade);
                fprintf(arquivo,"\nvalor unitario:%.2f",item.valorVenda);
            fprintf(arquivo,"\n|----------------------------------------------");
              }

                }
            fprintf(arquivo,"\nValor total:|R$%.2f|",nota.valorTotal);
            fprintf(arquivo,"\n|---------------------------------------------");
                     }
                }
            fclose(arquivo);


        }else
        printf("\n=======NOME NÃO PODE SER VAZIO=============");
        }while(vazio==0);
        }


  }else{
printf("\n=====ID NÃO ENCONTRADO=======");

  }

  printf("\nDeseja Voltar ao menu de relatórios???");
  printf("\n1-Sim|2-Não");
  printf("\nOpção:|");
  scanf("%d",&s_n);


}while (s_n!=1);


fclose(fv);
fclose(fc);
fclose(finf);
fclose(fnf);
return;
}

void relatorio_cinco(){

FILE *fv,*fc,*fnf,*finf,*arquivo;
char nome_arquivo[50],aux[2];

t_nota_fiscal nota;
t_item_nota_fiscal item;
t_vendedor vendedor;
t_cliente cliente;
int opcao,achou,s_n,vazio,mes;
unsigned long id,posicao;


fnf=fopen("NotaFiscal.dat","rb+");
if(fnf==NULL)
return;



fc=fopen("cliente.dat","rb+");
if(fc==NULL)
return;



fv=fopen("vendedor.dat","rb+");
if(fv==NULL)
return;


finf=fopen("ItemNotaFiscal.dat","rb+");
if(finf==NULL)
return;


do{
  printf("\nForneça o id do Vendedor:");
  scanf("%lu",&id);
  achou=0;
  fseek(fv,0,SEEK_SET);
  while(fread(&vendedor,sizeof(t_vendedor),1,fv)==1 && achou==0){
    if(id==vendedor.id){
    achou=1;
    break;
    }else posicao++;
  }

  if(achou==1){

        do{printf("\n|Forneça o mês:");
        scanf("%d",&mes);
if(mes<=0||mes>12){
    printf("\n====Mes Invalido====");
}



}while(mes<=0||mes>12);

if(mes<10){
    aux[0]='0';
    aux[1]=mes+48;


}else{
    aux[0]='1';
    aux[1]=(mes%10)+48;


}

        printf("\nComo deseja receber o relatorio??");
        printf("\n1-Tela|2-Arquivo de texto??");
        printf("\nComo deseja receber o relatorio??");
        printf("\nOpção:|");
        scanf("%d",&opcao);

        if(opcao==1){
                fseek(fnf,0,SEEK_SET);
                while(fread(&nota,sizeof(t_nota_fiscal),1,fnf)==1){
                        if(id==nota.idVendedor&&aux[0]==nota.dataCompra[3]&&aux[1]==nota.dataCompra[4]){
            printf("\n|------------Louco Das Pedras------------------");
            printf("\n|ID Nota Fiscal|%lu|",id);
            printf("\n|Data:%s",nota.dataCompra);
            fseek(fv,sizeof(t_vendedor)*(nota.idVendedor-1),SEEK_SET);
            fread(&vendedor,sizeof(t_vendedor),1,fv);
            printf("\n|Id Vendedor|%lu|Nome do Vendedor:%s",nota.idVendedor,vendedor.nome);
            fseek(fc,sizeof(t_cliente)*(nota.idCliente-1),SEEK_SET);
            fread(&cliente,sizeof(t_cliente),1,fc);
            printf("\n|ID Cliente|%lu|Nome do cliente:%s",nota.idCliente,cliente.nome);
            printf("\n|=============Itens da nota====================");

            fseek(finf,0,SEEK_SET);
            while(fread(&item,sizeof(t_item_nota_fiscal),1,finf)==1){
              if(item.idNota==nota.id){
                printf("\nId do produto:%lu",item.idDoProduto);
                printf("\nquantidade do produto:%d",item.quantidade);
                printf("\nvalor unitario:%.2f",item.valorVenda);
            printf("\n|----------------------------------------------");

              }

                }
            printf("\nValor total:|R$%.2f|",nota.valorTotal);
            printf("\n|---------------------------------------------");
                        }
        }


        }else{
        do{printf("\nForneça o nome do arquivo(sem extensão)");
        setbuf(stdin,NULL);
        fgets(nome_arquivo,50,stdin);
        vazio=retira_n(nome_arquivo);
        if(vazio==1){
            strcat(nome_arquivo,".txt");
            arquivo=fopen(nome_arquivo,"r+");
            if(arquivo==NULL)
            arquivo=fopen(nome_arquivo,"w+");
            if(arquivo==NULL)
            return;
                fseek(fnf,0,SEEK_SET);

            while(fread(&nota,sizeof(t_nota_fiscal),1,fnf)==1){
                      if(id==nota.idVendedor&&aux[0]==nota.dataCompra[3]&&aux[1]==nota.dataCompra[4]){
            fprintf(arquivo,"\n|------------Louco Das Pedras------------------");
            fprintf(arquivo,"\n|ID Nota Fiscal|%lu|",id);
            fprintf(arquivo,"\n|Data:%s",nota.dataCompra);
            fseek(fv,sizeof(t_vendedor)*(nota.idVendedor-1),SEEK_SET);
            fread(&vendedor,sizeof(t_vendedor),1,fv);
            fprintf(arquivo,"\n|Id Vendedor|%lu|Nome do Vendedor:%s",nota.idVendedor,vendedor.nome);
            fseek(fc,sizeof(t_cliente)*(nota.idCliente-1),SEEK_SET);
            fread(&cliente,sizeof(t_cliente),1,fc);
            fprintf(arquivo,"\n|ID Cliente|%lu|Nome do cliente:%s",nota.idCliente,cliente.nome);
            fprintf(arquivo,"\n|=============Itens da nota====================");

            fseek(finf,0,SEEK_SET);
            while(fread(&item,sizeof(t_item_nota_fiscal),1,finf)==1){
              if(item.idNota==nota.id){
                fprintf(arquivo,"\nId do produto:%lu",item.idDoProduto);
                fprintf(arquivo,"\nquantidade do produto:%d",item.quantidade);
                fprintf(arquivo,"\nvalor unitario:%.2f",item.valorVenda);
            fprintf(arquivo,"\n|----------------------------------------------");
              }

                }
            fprintf(arquivo,"\nValor total:|R$%.2f|",nota.valorTotal);
            fprintf(arquivo,"\n|---------------------------------------------");
                     }
                }
            fclose(arquivo);


        }else
        printf("\n=======NOME NÃO PODE SER VAZIO=============");
        }while(vazio==0);
        }


  }else{
printf("\n=====ID NÃO ENCONTRADO=======");

  }

  printf("\nDeseja Voltar ao menu de relatórios???");
  printf("\n1-Sim|2-Não");
  printf("\nOpção:|");
  scanf("%d",&s_n);


}while (s_n!=1);


fclose(fv);
fclose(fc);
fclose(finf);
fclose(fnf);
return;







}


void relatorio_tres(){
FILE *fv,*fc,*fnf,*finf,*arquivo;
char nome_arquivo[50],data[11],dataF[11];

t_nota_fiscal nota;
t_item_nota_fiscal item;
t_vendedor vendedor;
t_cliente cliente;
int opcao,achou,s_n,vazio,teste,valido;
int diadi,mesdi,anodi,diadf,mesdf,anodf,dianota,mesnota,anonota;
unsigned long id,posicao;


fnf=fopen("NotaFiscal.dat","rb+");
if(fnf==NULL)
return;



fc=fopen("cliente.dat","rb+");
if(fc==NULL)
return;



fv=fopen("vendedor.dat","rb+");
if(fv==NULL)
return;


finf=fopen("ItemNotaFiscal.dat","rb+");
if(finf==NULL)
return;

do{printf("\nO que deseja fazer");
printf("\n1-Data especifica\n2-Intervealo de datas");
printf("\nO que deseja fazer??");
scanf("%d",&opcao);

switch(opcao){

case 1:

do{
  printf("\nForneça o id do cliente:");
  scanf("%lu",&id);
  achou=0;
  fseek(fc,0,SEEK_SET);
  while(fread(&cliente,sizeof(t_cliente),1,fc)==1 && achou==0){
    if(id==cliente.id){
    achou=1;
    break;
    }else posicao++;
  }

  if(achou==1){

        do{teste=recebe_data(data);
if(teste==0){
    printf("\n====Data Invalida====");
}

}while(teste==0);



        printf("\nComo deseja receber o relatorio??");
        printf("\n1-Tela|2-Arquivo de texto??");
        printf("\nComo deseja receber o relatorio??");
        printf("\nOpção:|");
        scanf("%d",&opcao);

        if(opcao==1){
                fseek(fnf,0,SEEK_SET);
                while(fread(&nota,sizeof(t_nota_fiscal),1,fnf)==1){
                        if(id==nota.idCliente&&strncmp(nota.dataCompra,data,strlen(nota.dataCompra))==0){
            printf("\n|------------Louco Das Pedras------------------");
            printf("\n|ID Nota Fiscal|%lu|",nota.id);
            printf("\n|Data:%s",nota.dataCompra);
            fseek(fv,sizeof(t_vendedor)*(nota.idVendedor-1),SEEK_SET);
            fread(&vendedor,sizeof(t_vendedor),1,fv);
            printf("\n|Id Vendedor|%lu|Nome do Vendedor:%s",nota.idVendedor,vendedor.nome);
            fseek(fc,sizeof(t_cliente)*(nota.idCliente-1),SEEK_SET);
            fread(&cliente,sizeof(t_cliente),1,fc);
            printf("\n|ID Cliente|%lu|Nome do cliente:%s",nota.idCliente,cliente.nome);
            printf("\n|=============Itens da nota====================");

            fseek(finf,0,SEEK_SET);
            while(fread(&item,sizeof(t_item_nota_fiscal),1,finf)==1){
              if(item.idNota==nota.id){
                printf("\nId do produto:%lu",item.idDoProduto);
                printf("\nquantidade do produto:%d",item.quantidade);
                printf("\nvalor unitario:%.2f",item.valorVenda);
            printf("\n|----------------------------------------------");

              }

                }
            printf("\nValor total:|R$%.2f|",nota.valorTotal);
            printf("\n|---------------------------------------------");
                        }
        }


        }else{
        do{printf("\nForneça o nome do arquivo(sem extensão)");
        setbuf(stdin,NULL);
        fgets(nome_arquivo,50,stdin);
        vazio=retira_n(nome_arquivo);
        if(vazio==1){
            strcat(nome_arquivo,".txt");
            arquivo=fopen(nome_arquivo,"r+");
            if(arquivo==NULL)
            arquivo=fopen(nome_arquivo,"w+");
            if(arquivo==NULL)
            return;
                fseek(fnf,0,SEEK_SET);

            while(fread(&nota,sizeof(t_nota_fiscal),1,fnf)==1){
                     if(id==nota.idCliente&&strncmp(nota.dataCompra,data,strlen(nota.dataCompra))==0){

            fprintf(arquivo,"\n|------------Louco Das Pedras------------------");
            fprintf(arquivo,"\n|ID Nota Fiscal|%lu|",nota.id);
            fprintf(arquivo,"\n|Data:%s",nota.dataCompra);
            fseek(fv,sizeof(t_vendedor)*(nota.idVendedor-1),SEEK_SET);
            fread(&vendedor,sizeof(t_vendedor),1,fv);
            fprintf(arquivo,"\n|Id Vendedor|%lu|Nome do Vendedor:%s",nota.idVendedor,vendedor.nome);
            fseek(fc,sizeof(t_cliente)*(nota.idCliente-1),SEEK_SET);
            fread(&cliente,sizeof(t_cliente),1,fc);
            fprintf(arquivo,"\n|ID Cliente|%lu|Nome do cliente:%s",nota.idCliente,cliente.nome);
            fprintf(arquivo,"\n|=============Itens da nota====================");

            fseek(finf,0,SEEK_SET);
            while(fread(&item,sizeof(t_item_nota_fiscal),1,finf)==1){
              if(item.idNota==nota.id){
                fprintf(arquivo,"\nId do produto:%lu",item.idDoProduto);
                fprintf(arquivo,"\nquantidade do produto:%d",item.quantidade);
                fprintf(arquivo,"\nvalor unitario:%.2f",item.valorVenda);
            fprintf(arquivo,"\n|----------------------------------------------");
              }

                }
            fprintf(arquivo,"\nValor total:|R$%.2f|",nota.valorTotal);
            fprintf(arquivo,"\n|---------------------------------------------");
                     }
                }
            fclose(arquivo);


        }else
        printf("\n=======NOME NÃO PODE SER VAZIO=============");
        }while(vazio==0);
        }


  }else{
printf("\n=====ID NÃO ENCONTRADO=======");

  }

  printf("\nDeseja Voltar ao menu de relatórios???");
  printf("\n1-Sim|2-Não");
  printf("\nOpção:|");
  scanf("%d",&s_n);


}while (s_n!=1);




    break;
case 2:

    do{
  printf("\nForneça o id do cliente:");
  scanf("%lu",&id);
  achou=0;
  fseek(fc,0,SEEK_SET);
  while(fread(&cliente,sizeof(t_cliente),1,fc)==1 && achou==0){
    if(id==cliente.id){
    achou=1;
    break;
    }else posicao++;
  }

  if(achou==1){

        do{printf("\nData Inicial");
teste=recebe_data(data);
if(teste==0){
    printf("\n====Data Invalida====");
}

}while(teste==0);

        do{printf("\nData Final");
    teste=recebe_data(dataF);
if(teste==0){
    printf("\n====Data Invalida====");
}

}while(teste==0);
separa_data(data,&diadi,&mesdi,&anodi);
separa_data(dataF,&diadf,&mesdf,&anodf);

        printf("\nComo deseja receber o relatorio??");
        printf("\n1-Tela|2-Arquivo de texto??");
        printf("\nComo deseja receber o relatorio??");
        printf("\nOpção:|");
        scanf("%d",&opcao);

        if(opcao==1){
                fseek(fnf,0,SEEK_SET);
                while(fread(&nota,sizeof(t_nota_fiscal),1,fnf)==1){
                        valido=0;
                        separa_data(nota.dataCompra,&dianota,&mesnota,&anonota);
                        if(id==nota.idCliente){
                            if(anonota<anodi||anonota>anodf){valido=1;}
                                if((anonota==anodi&&mesnota<mesdi)||(anonota==anodf&&mesnota>mesdf)){valido=1;}
                                if(((anonota==anodi&&mesnota==mesdi)&& dianota<diadi)||((anonota==anodf&&mesnota==mesdf)&& dianota>diadf)){valido=1;}


if(valido==0){
                            printf("\n|------------Louco Das Pedras------------------");
            printf("\n|ID Nota Fiscal|%lu|",nota.id);
            printf("\n|Data:%s",nota.dataCompra);
            fseek(fv,sizeof(t_vendedor)*(nota.idVendedor-1),SEEK_SET);
            fread(&vendedor,sizeof(t_vendedor),1,fv);
            printf("\n|Id Vendedor|%lu|Nome do Vendedor:%s",nota.idVendedor,vendedor.nome);
            fseek(fc,sizeof(t_cliente)*(nota.idCliente-1),SEEK_SET);
            fread(&cliente,sizeof(t_cliente),1,fc);
            printf("\n|ID Cliente|%lu|Nome do cliente:%s",nota.idCliente,cliente.nome);
            printf("\n|=============Itens da nota====================");

            fseek(finf,0,SEEK_SET);
            while(fread(&item,sizeof(t_item_nota_fiscal),1,finf)==1){
              if(item.idNota==nota.id){
                printf("\nId do produto:%lu",item.idDoProduto);
                printf("\nquantidade do produto:%d",item.quantidade);
                printf("\nvalor unitario:%.2f",item.valorVenda);
            printf("\n|----------------------------------------------");

              }

                }
            printf("\nValor total:|R$%.2f|",nota.valorTotal);
            printf("\n|---------------------------------------------");
}



    }


                        }



        }else{
        do{printf("\nForneça o nome do arquivo(sem extensão)");
        setbuf(stdin,NULL);
        fgets(nome_arquivo,50,stdin);
        vazio=retira_n(nome_arquivo);
        if(vazio==1){
            strcat(nome_arquivo,".txt");
            arquivo=fopen(nome_arquivo,"r+");
            if(arquivo==NULL)
            arquivo=fopen(nome_arquivo,"w+");
            if(arquivo==NULL)
            return;
 fseek(fnf,0,SEEK_SET);
                while(fread(&nota,sizeof(t_nota_fiscal),1,fnf)==1){
                       valido=0;
                        separa_data(nota.dataCompra,&dianota,&mesnota,&anonota);
                        if(id==nota.idCliente){
                            if(anonota<anodi||anonota>anodf){valido=1;}
                                if((anonota==anodi&&mesnota<mesdi)||(anonota==anodf&&mesnota>mesdf)){valido=1;}
                                if(((anonota==anodi&&mesnota==mesdi)&& dianota<diadi)||((anonota==anodf&&mesnota==mesdf)&& dianota>diadf)){valido=1;}


if(valido==0){


                            fprintf(arquivo,"\n|------------Louco Das Pedras------------------");
            fprintf(arquivo,"\n|ID Nota Fiscal|%lu|",nota.id);
            fprintf(arquivo,"\n|Data:%s",nota.dataCompra);
            fseek(fv,sizeof(t_vendedor)*(nota.idVendedor-1),SEEK_SET);
            fread(&vendedor,sizeof(t_vendedor),1,fv);
            fprintf(arquivo,"\n|Id Vendedor|%lu|Nome do Vendedor:%s",nota.idVendedor,vendedor.nome);
            fseek(fc,sizeof(t_cliente)*(nota.idCliente-1),SEEK_SET);
            fread(&cliente,sizeof(t_cliente),1,fc);
            fprintf(arquivo,"\n|ID Cliente|%lu|Nome do cliente:%s",nota.idCliente,cliente.nome);
            fprintf(arquivo,"\n|=============Itens da nota====================");

            fseek(finf,0,SEEK_SET);
            while(fread(&item,sizeof(t_item_nota_fiscal),1,finf)==1){
              if(item.idNota==nota.id){
                fprintf(arquivo,"\nId do produto:%lu",item.idDoProduto);
                fprintf(arquivo,"\nquantidade do produto:%d",item.quantidade);
                fprintf(arquivo,"\nvalor unitario:%.2f",item.valorVenda);
            fprintf(arquivo,"\n|----------------------------------------------");

              }

                }
            fprintf(arquivo,"\nValor total:|R$%.2f|",nota.valorTotal);
            fprintf(arquivo,"\n|---------------------------------------------");
                                }



    }


                        }

            fclose(arquivo);


        }else
        printf("\n=======NOME NÃO PODE SER VAZIO=============");
        }while(vazio==0);
        }


  }else{
printf("\n=====ID NÃO ENCONTRADO=======");

  }

  printf("\nDeseja Voltar ao menu de relatórios???");
  printf("\n1-Sim|2-Não");
  printf("\nOpção:|");
  scanf("%d",&s_n);


}while (s_n!=1);

    break;
default:
    printf("Forneça uma opção valida");
    break;
}


}while(opcao!=1);

fclose(fv);
fclose(fc);
fclose(finf);
fclose(fnf);

}

void relatorio_seis(){

    FILE *fv,*fnf,*arquivo;
char nome_arquivo[50],aux[2];


t_nota_fiscal nota;
t_vendedor vendedor;
int opcao,s_n,vazio,mes;
float maiorvalor=0,taux=0;


fnf=fopen("NotaFiscal.dat","rb+");
if(fnf==NULL)
return;


fv=fopen("vendedor.dat","rb+");
if(fv==NULL)
return;




  do{
        do{printf("\n|Forneça o mês:");
        scanf("%d",&mes);
if(mes<=0||mes>12){
    printf("\n====Mes Invalido====");
}



}while(mes<=0||mes>12);

if(mes<10){
    aux[0]='0';
    aux[1]=mes+48;


}else{
    aux[0]='1';
    aux[1]=(mes%10)+48;}

        printf("\nComo deseja receber o relatorio??");
        printf("\n1-Tela|2-Arquivo de texto??");
        printf("\nComo deseja receber o relatorio??");
        printf("\nOpção:|");
        scanf("%d",&opcao);
                        fseek(fv,0,SEEK_SET);
                while(fread(&vendedor,sizeof(t_vendedor),1,fv)==1){
taux=0;

                fseek(fnf,0,SEEK_SET);
                while(fread(&nota,sizeof(t_nota_fiscal),1,fnf)==1){
                        if(vendedor.id==nota.idVendedor&&aux[0]==nota.dataCompra[3]&&aux[1]==nota.dataCompra[4]){

                        taux=taux+nota.valorTotal;



                        }

        }

                if(taux>maiorvalor){
                    maiorvalor=taux;


                }
        if(taux==maiorvalor){

        }



        }







        if(opcao==1){
                 printf("\n-------VENDEDORES COM MAIOR VALOR----------");
                          fseek(fv,0,SEEK_SET);
                while(fread(&vendedor,sizeof(t_vendedor),1,fv)==1){
taux=0;
                fseek(fnf,0,SEEK_SET);
                while(fread(&nota,sizeof(t_nota_fiscal),1,fnf)==1){
                        if(vendedor.id==nota.idVendedor&&aux[0]==nota.dataCompra[3]&&aux[1]==nota.dataCompra[4]){

                        taux=taux+nota.valorTotal;



                        }

        }

                if(taux==maiorvalor&&maiorvalor>0){
                    printf("\n|====================");
                    printf("\n|ID:|%lu|",vendedor.id);
                    printf("\n|Nome:|%s|",vendedor.nome);
                    printf("\n|====================");


                }

        }

printf("\n|Maior Valor:|%.2f",maiorvalor);






        }else{
        do{printf("\nForneça o nome do arquivo(sem extensão)");
        setbuf(stdin,NULL);
        fgets(nome_arquivo,50,stdin);
        vazio=retira_n(nome_arquivo);
        if(vazio==1){
            strcat(nome_arquivo,".txt");
            arquivo=fopen(nome_arquivo,"r+");
            if(arquivo==NULL)
            arquivo=fopen(nome_arquivo,"w+");
            if(arquivo==NULL)
            return;
                 printf("\n-------VENDEDORES COM MAIOR VALOR----------");
                          fseek(fv,0,SEEK_SET);
                while(fread(&vendedor,sizeof(t_vendedor),1,fv)==1){
taux=0;
                fseek(fnf,0,SEEK_SET);
                while(fread(&nota,sizeof(t_nota_fiscal),1,fnf)==1){
                        if(vendedor.id==nota.idVendedor&&aux[0]==nota.dataCompra[3]&&aux[1]==nota.dataCompra[4]){

                        taux=taux+nota.valorTotal;



                        }

        }

                if(taux==maiorvalor&&maiorvalor>0){
                    fprintf(arquivo,"\n|====================");
                    fprintf(arquivo,"\n|ID:|%lu|",vendedor.id);
                    fprintf(arquivo,"\n|Nome:|%s|",vendedor.nome);
                    fprintf(arquivo,"\n|====================");


                }

        }

fprintf(arquivo,"\n|Maior Valor:|%.2f",maiorvalor);

            fclose(arquivo);


        }else
        printf("\n=======NOME NÃO PODE SER VAZIO=============");
        }while(vazio==0);
        }




  printf("\nDeseja Voltar ao menu de relatórios???");
  printf("\n1-Sim|2-Não");
  printf("\nOpção:|");
  scanf("%d",&s_n);


}while (s_n!=1);


fclose(fv);
fclose(fnf);
return;
}

void relatorio_sete(){

   FILE *fv,*fnf,*arquivo;
char nome_arquivo[50],data[11],dataF[11];


t_nota_fiscal nota;
t_vendedor vendedor;
int opcao,s_n,vazio,teste,valido;
int diadi,mesdi,anodi,diadf,mesdf,anodf,dianota,mesnota,anonota;
float maiorvalor=0,taux=0;


fnf=fopen("NotaFiscal.dat","rb+");
if(fnf==NULL)
return;


fv=fopen("vendedor.dat","rb+");
if(fv==NULL)
return;




  do{
        do{printf("\nData Inicial");
teste=recebe_data(data);
if(teste==0){
    printf("\n====Data Invalida====");
}

}while(teste==0);

        do{printf("\nData Final");
    teste=recebe_data(dataF);
if(teste==0){
    printf("\n====Data Invalida====");
}

}while(teste==0);
separa_data(data,&diadi,&mesdi,&anodi);
separa_data(dataF,&diadf,&mesdf,&anodf);


        printf("\nComo deseja receber o relatorio??");
        printf("\n1-Tela|2-Arquivo de texto??");
        printf("\nComo deseja receber o relatorio??");
        printf("\nOpção:|");
        scanf("%d",&opcao);
                        fseek(fv,0,SEEK_SET);
                while(fread(&vendedor,sizeof(t_vendedor),1,fv)==1){
taux=0;

                fseek(fnf,0,SEEK_SET);
                while(fread(&nota,sizeof(t_nota_fiscal),1,fnf)==1){
                    valido=0;
                        separa_data(nota.dataCompra,&dianota,&mesnota,&anonota);
                        if(vendedor.id==nota.idVendedor){
                            if(anonota<anodi||anonota>anodf){valido=1;}
                                if((anonota==anodi&&mesnota<mesdi)||(anonota==anodf&&mesnota>mesdf)){valido=1;}
                                if(((anonota==anodi&&mesnota==mesdi)&& dianota<diadi)||((anonota==anodf&&mesnota==mesdf)&& dianota>diadf)){valido=1;}


if(valido==0){
                        taux=taux+nota.valorTotal;
                                }



                        }

        }

                if(taux>maiorvalor){
                    maiorvalor=taux;


                }
        if(taux==maiorvalor){

        }



        }







        if(opcao==1){
                 printf("\n-------VENDEDORES COM MAIOR VALOR----------");
                          fseek(fv,0,SEEK_SET);
                while(fread(&vendedor,sizeof(t_vendedor),1,fv)==1){

taux=0;
                fseek(fnf,0,SEEK_SET);
                while(fread(&nota,sizeof(t_nota_fiscal),1,fnf)==1){
                        valido=0;
                        separa_data(nota.dataCompra,&dianota,&mesnota,&anonota);
                        if(vendedor.id==nota.idVendedor){
                            if(anonota<anodi||anonota>anodf){valido=1;}
                                if((anonota==anodi&&mesnota<mesdi)||(anonota==anodf&&mesnota>mesdf)){valido=1;}
                                if(((anonota==anodi&&mesnota==mesdi)&& dianota<diadi)||((anonota==anodf&&mesnota==mesdf)&& dianota>diadf)){valido=1;}


if(valido==0){
                        taux=taux+nota.valorTotal;
                         }


                        }

        }

                if(taux==maiorvalor&&maiorvalor>0){
                    printf("\n|====================");
                    printf("\n|ID:|%lu|",vendedor.id);
                    printf("\n|Nome:|%s|",vendedor.nome);
                    printf("\n|====================");


                }

        }

printf("\n|Maior Valor:|%.2f",maiorvalor);






        }else{
        do{printf("\nForneça o nome do arquivo(sem extensão)");
        setbuf(stdin,NULL);
        fgets(nome_arquivo,50,stdin);
        vazio=retira_n(nome_arquivo);
        if(vazio==1){
            strcat(nome_arquivo,".txt");
            arquivo=fopen(nome_arquivo,"r+");
            if(arquivo==NULL)
            arquivo=fopen(nome_arquivo,"w+");
            if(arquivo==NULL)
            return;
                 printf("\n-------VENDEDORES COM MAIOR VALOR----------");
                          fseek(fv,0,SEEK_SET);
                while(fread(&vendedor,sizeof(t_vendedor),1,fv)==1){
taux=0;
                fseek(fnf,0,SEEK_SET);
                while(fread(&nota,sizeof(t_nota_fiscal),1,fnf)==1){
                        valido=0;
                        separa_data(nota.dataCompra,&dianota,&mesnota,&anonota);
                        if(vendedor.id==nota.idVendedor){
                            if(anonota<anodi||anonota>anodf){valido=1;}
                                if((anonota==anodi&&mesnota<mesdi)||(anonota==anodf&&mesnota>mesdf)){valido=1;}
                                if(((anonota==anodi&&mesnota==mesdi)&& dianota<diadi)||((anonota==anodf&&mesnota==mesdf)&& dianota>diadf)){valido=1;}


if(valido==0){
                        taux=taux+nota.valorTotal;
                         }


                        }

        }

                if(taux==maiorvalor&&maiorvalor>0){
                    fprintf(arquivo,"\n|====================");
                    fprintf(arquivo,"\n|ID:|%lu|",vendedor.id);
                    fprintf(arquivo,"\n|Nome:|%s|",vendedor.nome);
                    fprintf(arquivo,"\n|====================");


                }

        }

fprintf(arquivo,"\n|Maior Valor:|%.2f",maiorvalor);

            fclose(arquivo);


        }else
        printf("\n=======NOME NÃO PODE SER VAZIO=============");
        }while(vazio==0);
        }




  printf("\nDeseja Voltar ao menu de relatórios???");
  printf("\n1-Sim|2-Não");
  printf("\nOpção:|");
  scanf("%d",&s_n);


}while (s_n!=1);


fclose(fv);
fclose(fnf);
return;




}
