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
#include "funcoesgerais.h"

void mCompra(){
FILE *ff;
int achou,s_n;
unsigned long idv;
t_fornecedor busca;

ff=fopen("fornecedor.dat","rb+");
if(ff==NULL){
    printf("==============NENHUM FORNECEDOR CADASTRADO=========");
    return;
}

do{printf("\nForneça o id do fornecedor");
    setbuf(stdin,NULL);
    scanf("%lu",&idv);
   achou=0;
    fseek(ff,0,SEEK_SET);
while(fread(&busca,sizeof(t_fornecedor),1,ff)==1&&achou==0){
    if(idv==busca.id){
    achou=1;
    break;
    }
}

if(achou==1){


                menuCompras(ff,idv);



  }else printf("\n====ID Invalida=====");
    printf ("\n|deseja voltar ao menu principal???");
    printf("\n1-Sim|2-Não");
    printf("\n|Opção:");
    scanf("%d",&s_n);
    if(s_n==1){
        fclose(ff);
        return;}
}while(s_n!=1);



}

void menuCompras(FILE *ff ,unsigned long idf){
unsigned int qtde;
int opcao,achou,igual,valida;
t_produto buscap;
carrinho cc;
item_carrinho item;
FILE *fp;

cc=criaCarrinho();
if(cc!=NULL){
fp=fopen("produto.dat","rb+");
if(fp==NULL){
    printf("\nNenhum produto encontrado");
    return;
}

printf("\n|===============MENU DE COMPRAS================");

    do{printf("\n|O que deseja fazer");
 printf("\n|1-Adicionar ou alterar quantidade");
 printf("\n|2-Remover item");
 printf("\n|3-Listar produtos do carrinho");
 printf("\n|4-Desistir da compra");
 printf("\n|5-Finalizar Compra");
 printf("\n|Opção:|");
 scanf("%d",&opcao);

    switch(opcao){

        case 1:
            do{printf("\nForneça id do produto:|");
             scanf("%lu",&item.idProduto);

fseek(fp,0,SEEK_SET);
achou=0;
while(fread(&buscap,sizeof(t_produto),1,fp)==1&&achou==0){
  if(item.idProduto==buscap.id){
    achou=1;
    break;
  }

}
        if(achou==1 && item.idProduto!=0){
            busca_ID(fp,item.idProduto,2);
            fseek(fp,sizeof(t_produto)*(item.idProduto-1),SEEK_SET);

            igual=0;
            igual=verifica_carrinho(cc,item.idProduto);
//verifica se o item ja está no carrinho caso esteja modifica apenas a qtde
            if(igual==1){printf("\n|Produto ja esta no carrinho");
                printf("\n|Forneça a nova quantidade que deseja:|");
            }else
 printf("\n|Forneça a quantidade que deseja comprar:|");
    do{
     scanf("%d",&qtde);
     valida=0;
     if(qtde>0){valida=1;
        if(igual==1){
            altera_qtde(item.idProduto,qtde,cc);
            printf("=====QUANTIDADE ALTERADA=====");
        }else{
            item.quantidadeVendida=qtde;
                item.valorVenda=buscap.precoUnitario;
                insereFinal(cc,item);
                printf("\n=====ITEM INSERIDO NO CARRINHO=====");}
                achou=1;
     }else
     printf("\nForneça uma quantidade valida:");
            }while(valida==0);
        }else
        printf("\n========ID NÃO ENCONTRADO======");

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
    return;
    break;
case 5:
    finaliza_venda(idf,cc,ff,fp);
    return;
    break;

    }
    }while(opcao!=5);
}
//retorna se não conseguir criar o carrinho

}

void finaliza_venda(unsigned long idf,carrinho cc,FILE *ff, FILE *fp){

nota_compra nota;
item_nota_compra item;
t_nodo *p;
t_produto produto;
t_fornecedor fornecedor;
FILE *fnc,*finc;
int s_n,teste=0;
unsigned long posicaop;


if(cc->inicio!=NULL){
fnc=fopen("NotaCompra.dat","rb+");
if(fnc==NULL)
fnc=fopen("NotaCompra.dat","wb+");
if(fnc==NULL)
return;

finc=fopen("ItemNotaCompra.dat","rb+");
if(finc==NULL)
finc=fopen("ItemNotaCompra.dat","wb+");
if(finc==NULL)
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
//gera os valores da nota e dps os escrevem no arquivo
nota.id=gera_IDNC(fnc);
nota.idFornecedor=idf;
nota.valorTotal=gera_valor_total(cc);

fseek(fnc,0,SEEK_END);
fwrite(&nota,sizeof(nota_compra),1,fnc);

//imprime a nota na tela
printf("\n|------------Nota de Compra------------------");
printf("\n|ID Nota Compra|%lu|",nota.id);
printf("\n|Data:%s",nota.dataCompra);
fseek(ff,sizeof(t_fornecedor)*(idf-1),SEEK_SET);
fread(&fornecedor,sizeof(t_fornecedor),1,ff);
printf("\n|Id Fornecedor|%lu|Nome do Fornecedor:%s",idf,fornecedor.nome);
printf("\n|=============Itens da nota====================");
imprime(cc,fp);
printf("\nValor total:|R$%.2f|",nota.valorTotal);
printf("\n|---------------------------------------------");
//loop que gera cada ItemNotaCompra e os coloca no arquivo
        p=cc->inicio;
        while(p!=NULL){

            item.id=gera_IDINC(finc);
            item.idNotaCompra=nota.id;
            item.idProduto=p->info.idProduto;
            posicaop=p->info.idProduto-1;

            fseek(fp,sizeof(t_produto)*posicaop,SEEK_SET);
            fread(&produto,sizeof(t_produto),1,fp);
            produto.quantidadeEstoque=produto.quantidadeEstoque+p->info.quantidadeVendida;
            fseek(fp,sizeof(t_produto)*posicaop,SEEK_SET);
            fwrite(&produto,sizeof(t_produto),1,fp);
            item.quantidade=p->info.quantidadeVendida;
            item.valorUnitario=p->info.valorVenda;

    fseek(finc,0,SEEK_END);
    fwrite(&item,sizeof(item_nota_compra),1,finc);

            p=p->next;

        }
  terminaCarrinho(cc);
  fclose(fp);
  fclose(finc);
  fclose(fnc);
  return;


}else
    printf("\nCarrinho esta vazio!!!");


return;

}

unsigned long gera_IDNC(FILE *file){

unsigned long id;
nota_compra novo;

id=1;
fseek(file,0,SEEK_SET);
while(fread(&novo,sizeof (nota_compra),1,file)==1){

id++;

}
return id;


}

unsigned long gera_IDINC(FILE *file){

unsigned long id;
item_nota_compra novo;

id=1;
fseek(file,0,SEEK_SET);
while(fread(&novo,sizeof (item_nota_compra),1,file)==1){

id++;

}
return id;

}


