#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "produtos.h"
#include "vendedor.h"
#include "fornecedor.h"
#include "validacao.h"
#include "vendas.h"
#include "funcoesgerais.h"


 void mVendas(){
unsigned long posicaov=0,posicaoc,id;
int tipo=3,achou=0,s_n=0,teste,i=3;
char cpf[12],senha[20];
t_vendedor novo;
t_cliente novoc;

FILE *fv,*fc,*fp;

fv=fopen("vendedor.dat","rb+");
if(fv==NULL){
 printf ("=========NENHUM VENDEDOR CADASTRADO==============");
 return;}
fc=fopen("cliente.dat","rb+");
if(fc==NULL){
 printf ("=========NENHUM CLIENTE CADASTRADO==============");
 return;

}

printf("\n===========MENU DE VENDAS=============");

do{printf("\n|Forneça o cpf do vendedor:");
   setbuf(stdin,NULL);
   fgets(cpf,12,stdin);
    retira_n(cpf);
    teste=cpf_Repetido(cpf,fv,tipo);

        if(teste==1){
                do{printf("\n|Forneça a senha do vendedor:");
                         setbuf(stdin,NULL);
                          fgets(senha,20,stdin);
                            retira_n(senha);
                              nome_maiusculo(senha);
            fseek(fv,0,SEEK_SET);
        while(fread(&novo,sizeof (t_vendedor),1,fv)==1&&achou==0){

                if(strcmp(cpf,novo.cpf)==0){
                achou=1;}else posicaov ++;

     }

            if(achou==1){
                    fseek(fv,sizeof(t_vendedor)*posicaov,SEEK_SET);
                    fread(&novo,sizeof(t_vendedor),1,fv);
            }


                if(strcmp(senha,novo.password)==0){
                    //vendedor logado com sucesso

                   do{ printf("|Forneça o ID do cliente:");
                     setbuf(stdin,NULL);
                       scanf("%lu",&id);
                    achou=0;
                    posicaoc=0;
        fseek(fc,0,SEEK_SET);
        while(fread(&novoc,sizeof (t_cliente),1,fc)==1&&achou==0){

                if(id==novoc.id){
                achou=1;}else posicaoc ++;

     }
            if(achou==1){
                fp=fopen("produto.dat","rb+");
                if(fp==NULL){
                    printf("===========NÃO FOI POSSIVEL ABRIR O ARQUIVO");
                     return;  }

                menuVendas(fp,fv,fc,posicaov,posicaoc);





            }else{
            printf("\n|==========ID NÃO ENCONTRADO============");
              printf ("\n|deseja voltar ao menu principal???");
               printf("\n1-Sim|2-Não");
               printf("\n|Opção:");
               scanf("%d",&s_n);
                    if(s_n==1){
                    fclose(fc);
                    fclose(fv);
                        return;}

               }
                printf("\n|Deseja realizar mais alguma venda com esse vendedor");
                printf("\n1-Sim|2-Não");
               printf("\n|Opção:");
               scanf("%d",&s_n);
                if(s_n!=1){fclose(fc);
                    fclose(fv);
                    return;}
                   }while (s_n==1);


                }else{
                    i--;
                        printf("\nSenha incorreta!!!");
                        printf("\n%d tentativas restantes",i);

            }


        }while(i>0 );


        }else printf("\n=========CPF NÃO ENCONTRADO==============");

}while(s_n==1);
 }

 void menuVendas(FILE *fp,FILE *fv,FILE *fc,unsigned long posicaov,unsigned long posicaoc){
int opcao,achou,valida,igual;
unsigned long posicao,idv,idc;
unsigned int qtde;
t_produto buscap;
carrinho cc;
item_carrinho item;


cc=criaCarrinho();
  if(cc!=NULL){

 do{printf("\n|O que deseja fazer");
 printf("\n|1-Adicionar ou alterar quantidade");
 printf("\n|2-Remover item");
 printf("\n|3-Listar produtos do carrinho");
 printf("\n|4-Desistir da venda");
 printf("\n|5-Finalizar venda");
 printf("\nOpção:|");
 scanf("%d",&opcao);


 switch (opcao){

 case 1:
     do{printf("\nForneça id do Produto:|");
    scanf("%lu",&item.idProduto);

fseek(fp,0,SEEK_SET);
posicao=0;
achou=0;
while(fread(&buscap,sizeof (t_produto),1,fp)==1&&achou==0){

if(item.idProduto==buscap.id){
  achou=1;
  break;
  }else  posicao ++;
  }
  if(achou==1){

     busca_ID(fp,item.idProduto,2);
     fseek(fp,sizeof(t_produto)*posicao,SEEK_SET);

     do{achou=0;
            igual=0;
            igual=verifica_carrinho(cc,item.idProduto);
//verifica se o produto ja está no carrinho caso esteja altera apenas a qtde
            if(igual==1){printf("\n|Produto ja esta no carrinho");
            printf("\n|Forneça a nova quantidade que deseja:|");}else
        printf("\n|Forneça a quantidade que deseja vender:|");
     scanf("%d",&qtde);
     if(qtde>0){
            //verifica se possui a qtde em estoque
        if(qtde<=buscap.quantidadeEstoque){
         if(igual==1){
            altera_qtde(item.idProduto,qtde,cc);
            printf("=====QUANTIDADE ALTERADA=====");}
            else{
            item.quantidadeVendida=qtde;
         item.valorVenda=buscap.precoUnitario;
         insereFinal(cc,item);

         printf("\n=====ITEM INSERIDO NO CARRINHO=====");}
               valida=1;
            achou=1;


        }else
        printf("Não Temos essa quantidade em estoque");
     }else
     printf("Forneça uma quantidade valida");

     }while(valida==0);

  }else
    printf("\n------------ID invalida-----------");



     }while(achou==0);
    break;
 case 2:
     printf("\nForneça id do Produto que deseja remover:|");
     scanf("%lu",&item.idProduto);
     removeItem(cc,item.idProduto);
printf("\n=====REMOVIDO COM SUCESSO=====");
    break;
 case 3:
 printf("\n|=============Itens do carrinho=================|");
imprime(cc,fp);
       break;
 case 4:
         fclose(fp);
         terminaCarrinho(cc);
        return;
    break;

case 5:
   idv=posicaov+1;
   idc=posicaoc+1;
    finaliza_compra(idv,idc,cc,fp,fv,fc);
    return;
    break;
 }
  }while(opcao!=5);
return;
 }

//retorna caso não tenha consiguido criar o carrinho
  }


carrinho criaCarrinho(){
carrinho c;
    c=(carrinho) malloc(sizeof(t_carrinho));
    if(c!=NULL){
        c->inicio = NULL;
        c->fim = NULL;
        c->tamanho = 0;
        return c;
    }
//cria um espaço de memoria para servir como carrinho caso não consiga retorna NULL
return NULL;
}

void terminaCarrinho(carrinho cc){
t_nodo *p;


while(cc->inicio!=NULL){
    p=cc->inicio;
    cc->inicio=cc->inicio->next;
    free(p);


}
//libera a memoria alocada
free(cc);
}

int insereFinal(carrinho cc,item_carrinho item){
//cria uma nova possição no fim do carrinho
t_nodo *p;
    p=(t_nodo*)malloc(sizeof(t_nodo));
    if(p!=NULL){
    p->next=NULL;
    p->info= item;
      if(cc->inicio==NULL)
       cc->inicio=p;
         else
            cc->fim->next=p;

         cc->fim=p;
         cc->tamanho++;
         return 1;
    }else
        return 0;

}

void imprime(carrinho cc,FILE *fp){
t_produto nome;
t_nodo *p;
unsigned long posicao;
    if(cc->inicio!=NULL){

        p=cc->inicio;
        while(p!=NULL){

           posicao=p->info.idProduto-1;
           fseek(fp,sizeof(t_produto)*posicao,SEEK_SET);
            fread(&nome,sizeof(t_produto),1,fp);

        printf("\n|ID:%lu",p->info.idProduto);
        printf("\n|Nome:%s",nome.nome);
        printf("\n|qtde:%d",p->info.quantidadeVendida);
        printf("\n|valor:%.2f",p->info.valorVenda);
        printf("\n|===============================================|");
            p=p->next;
        }

    }else
        printf("\nCarrinho Vazio!!!");
}

int removeItem(carrinho cc, unsigned long id){
t_nodo *p,*ant;
p= cc->inicio;

while(p!=NULL){
    if(p->info.idProduto==id){
        if(p==cc->inicio){
            cc->inicio=cc->inicio->next;
        }else if(p==cc->fim){
         cc->fim=ant;
         cc->fim->next=NULL;
        }else{
        ant->next=p->next;
        }
        free(p);
        cc->tamanho--;
        return 1;
    }else{
    ant=p;
    p=p->next;
    }



}
return 0;
}

int verifica_carrinho(carrinho cc,unsigned long id){
t_nodo *p;
//retorna 1 se encontrar alguem item igual no carrinho
p= cc->inicio;

            while(p!=NULL){
                if(p->info.idProduto==id)

                   return 1;
                else
                  p=p->next;

            }


return 0;
}

void altera_qtde(unsigned long id,unsigned int qtde,carrinho cc){
//altera a quantidade de um produto no carrinho
t_nodo *p;
p= cc->inicio;

            while(p!=NULL){
                if(p->info.idProduto==id){
                    p->info.quantidadeVendida=qtde;
                   return ;}
                    else
                  p=p->next;

            }


return ;



}

void finaliza_compra(unsigned long idv,unsigned long idc,carrinho cc,FILE *fp,FILE *fv,FILE *fc){

t_nota_fiscal nota;
t_item_nota_fiscal item;
t_produto produto;
t_vendedor vendedor;
t_cliente cliente;
t_nodo *p;
int s_n,teste=0;
FILE *fnf;
FILE *finf;
unsigned long posicaop;

if(cc->inicio!=NULL){
fnf=fopen("NotaFiscal.dat","rb+");
if(fnf==NULL)
fnf=fopen("NotaFiscal.dat","wb+");
if(fnf==NULL)
return;

finf=fopen("ItemNotaFiscal.dat","rb+");
if(finf==NULL)
finf=fopen("ItemNotaFiscal.dat","wb+");
if(finf==NULL)
return;
printf("\n|=========FINALIZANDO COMPRA============|");

data_sistema(nota.dataCompra);
printf("\n|Data do sistema:%s",nota.dataCompra);
printf("\n|Deseja manter a data do sistema?");
printf("\n1-Sim|2-Não");
printf("\nOpção:|");
scanf("%d",&s_n);
if(s_n!=1){
do{teste=recebe_data(nota.dataCompra);
if(teste==0){
    printf("\n====Data Invalida====");
}

}while(teste==0);
}
nota.id=gera_IDNF(fnf);
nota.idVendedor=idv;
nota.idCliente=idc;
nota.valorTotal=gera_valor_total(cc);
fseek(fnf,0,SEEK_END);
fwrite(&nota,sizeof(t_nota_fiscal),1,fnf);


printf("\n|------------Louco Das Pedras------------------");
printf("\n|ID Nota Fiscal|%lu|",nota.id);
printf("\n|Data:%s",nota.dataCompra);
fseek(fv,sizeof(t_vendedor)*(idv-1),SEEK_SET);
fread(&vendedor,sizeof(t_vendedor),1,fv);
printf("\n|Id Vendedor|%lu|Nome do Vendedor:%s",idv,vendedor.nome);
fseek(fc,sizeof(t_cliente)*(idc-1),SEEK_SET);
fread(&cliente,sizeof(t_cliente),1,fc);
printf("\n|ID Cliente|%lu|Nome do cliente:%s",idc,cliente.nome);
printf("\n|=============Itens da nota====================");
imprime(cc,fp);
printf("\nValor total:|R$%.2f|",nota.valorTotal);
printf("\n|---------------------------------------------");



        p=cc->inicio;
        while(p!=NULL){
                item.id=gera_IDINF(finf);
                item.idNota=nota.id;
                item.idDoProduto=p->info.idProduto;
                posicaop =p->info.idProduto-1;

                fseek(fp,sizeof(t_produto)*posicaop,SEEK_SET);
                fread(&produto,sizeof(t_produto),1,fp);
                produto.quantidadeEstoque=produto.quantidadeEstoque-p->info.quantidadeVendida;
            fseek(fp,sizeof(t_produto)*posicaop,SEEK_SET);
            fwrite(&produto,sizeof(t_produto),1,fp);
                item.quantidade=p->info.quantidadeVendida;
                item.valorVenda=p->info.valorVenda;

fseek(finf,0,SEEK_END);
fwrite(&item,sizeof(t_item_nota_fiscal),1,finf);

            p=p->next;
        }

terminaCarrinho(cc);
fclose(fp);
fclose(finf);
fclose(fnf);
return;
}else
    printf("\nCarrinho esta vazio!!!");



}


unsigned long gera_IDNF(FILE *file){

unsigned long id;
t_nota_fiscal novo;

id=1;
fseek(file,0,SEEK_SET);
while(fread(&novo,sizeof (t_nota_fiscal),1,file)==1){
id++;

}
return id;
}



float gera_valor_total(carrinho cc){
t_nodo *p;
float valor=0;
    if(cc->inicio!=NULL){;
        p=cc->inicio;
        while(p!=NULL){

            valor=valor+(p->info.valorVenda*p->info.quantidadeVendida);
            p=p->next;
        }

    }else
        printf("\nCarrinho Vazio!!!");
//percorre todo o carrinho somando os valores e retorna o valor total
return valor;
}

unsigned long gera_IDINF(FILE *file){

unsigned long id;
t_item_nota_fiscal novo;

id=1;
fseek(file,0,SEEK_SET);
while(fread(&novo,sizeof (t_item_nota_fiscal),1,file)==1){

id++;

}

return id;
}
