#include "carrinho.h"
#include <stdlib.h>
carrinho criaCarrinho(){
    carrinho c;
    c=(carrinho) malloc(sizeof(TCarrinho));
    if(c!=NULL){
        c->inicio = NULL;
        c->fim = NULL;
        c->tamanho = 0;
        return c;
    }
//cria um espaço de memoria para servir como carrinho caso não consiga retorna NULL
    return NULL;
}

int insereFinal(carrinho cc,itemCarrinho item){
//cria uma nova possição no fim do carrinho
TNodo *p;
    p=(TNodo*)malloc(sizeof(TNodo));
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

int verificaCarrinho(carrinho cc,unsigned long id){
    TNodo *p;
//retorna 1 se encontrar alguem item igual no carrinho
    p= cc->inicio;

    while(p!=NULL)
        if(p->info.idProduto==id)
           return 1;
        else
            p=p->next;

    return 0;
}


void alteraQtde(unsigned long id,unsigned int qtde,carrinho cc){
//altera a quantidade de um produto no carrinho
    TNodo *p;
    p= cc->inicio;

    while(p!=NULL)
        if(p->info.idProduto==id){
            p->info.quantidadeVendida=qtde;
           return ;
        }else
            p=p->next;
    return ;
}

int removeItem(carrinho cc, unsigned long id){
    TNodo *p,*ant=NULL;
    p= cc->inicio;

    while(p!=NULL){
        if(p->info.idProduto==id){
            if(p==cc->inicio)
                cc->inicio=cc->inicio->next;
            else if(p==cc->fim){
                cc->fim=ant;
                cc->fim->next=NULL;
            }else
                ant->next=p->next;

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

float geraValorTotal(carrinho cc){
    TNodo *p;
    float valor=0;

    p=cc->inicio;
    while(p!=NULL){

        valor+=(p->info.valorVenda*p->info.quantidadeVendida);
        p=p->next;
    }
//percorre todo o carrinho somando os valores e retorna o valor total
    return valor;
}

void terminaCarrinho(carrinho cc){
TNodo *p;


while(cc->inicio!=NULL){
    p=cc->inicio;
    cc->inicio=cc->inicio->next;
    free(p);


}
//libera a memoria alocada
free(cc);
}
