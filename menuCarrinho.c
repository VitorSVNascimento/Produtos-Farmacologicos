#include "menuCarrinho.h"
#include "produto.h"
#include "menuProduto.h"

int mCarrinho(carrinho carrinhoCompras,FILE *f,int tipo){
    unsigned int max;

    int opcao,igual;
    itemCarrinho item;
    TProduto produto = novoProduto();
    printf("\n|===============MENU DE COMPRAS================");
    do{
         printf("\n|O que deseja fazer");
         printf("\n|1-Adicionar ou alterar quantidade");
         printf("\n|2-Remover item");
         printf("\n|3-Listar produtos do carrinho");
         printf("\n|4-Listar produtos disponiveis para compra");
         printf("\n|5-Desistir da compra");
         printf("\n|6-Finalizar Compra");
         printf("\n|Opção:|");
         scanf("%d",&opcao);

         switch(opcao){
            case 1:

                    printf("\nForneça id do produto:|");
                    scanf("%lu",&item.idProduto);
                    if(buscaIdProduto(item.idProduto,f)!=-1){
                        atribuirDadosProduto(produto,item.idProduto-1,f);
                        if(tipo==TIPOVENDA)
                            if(!getQtdeEstoqueProduto(produto)){
                                printf("\nNão existe estoque deste produto!");
                                break;
                            }
                        igual = verificaCarrinho(carrinhoCompras,item.idProduto);
                        do{

                            printf("\n|Quantidade em estoque do produto: %u|",getQtdeEstoqueProduto(produto));
                            (igual) ? printf("\n|Produto ja esta no carrinho\nForneça a nova quantidade que deseja") : printf("\n|Forneça a quantidade que deseja:|");
                            scanf("%u",&item.quantidadeVendida);
                            if(tipo == TIPOVENDA)
                                max = getQtdeEstoqueProduto(produto);
                            else
                                max = item.quantidadeVendida;

                            if(max<item.quantidadeVendida)
                                printf("\nQuantidade em estoque insuficiente!!");
                        }while(max<item.quantidadeVendida);
                        if(igual){
                            alteraQtde(item.idProduto,item.quantidadeVendida,carrinhoCompras);
                            printf("\n--------------QUANTIDADE ALTERADA------------");
                        }else{
                            item.valorVenda = getPrecoUnitarioProduto(produto);
                            insereFinal(carrinhoCompras,item);
                            printf("\n----------ITEM INSERIDO NO CARRINHO------------");
                        }

                    }else
                        printf("\n--------------ID inválido!--------------");

            break;

            case 2:
                if(carrinhoCompras->tamanho){
                printf("\nForneça id do produto:|");
                scanf("%lu",&item.idProduto);
                    if(verificaCarrinho(carrinhoCompras,item.idProduto)){
                        removeItem(carrinhoCompras,item.idProduto);
                        printf("\n|-------ITEM REMOVIDO COM SUCESSO-------|");
                    }else
                        printf("\n------------ITEM NÃO ENCONTRADO------------");
                }else
                    printf("\n|----------CARRINHO VAZIO----------|");
            break;

            case 3:
                imprime(carrinhoCompras,f);
            break;
            case 4:
                if(tipo==TIPOVENDA)
                    listaProdutosEmEstoque(f);
                else
                    listaTodosProduto(f);
             break;
            case 5:
                liberaProduto(produto);
                return 0;
            break;

         }//switch

    }while(opcao!=6);
    liberaProduto(produto);
    return 1;
}

void imprime(carrinho cc,FILE *fp){
TProduto nome = novoProduto();
TNodo *p;
char aux[100];
unsigned long posicao;
    if(cc->inicio!=NULL){

        p=cc->inicio;
        while(p!=NULL){

           posicao=p->info.idProduto-1;
           fseek(fp,tamStructProduto()*posicao,SEEK_SET);
            fread(nome,tamStructProduto(),1,fp);

        printf("\n|ID:%lu",p->info.idProduto);
        getNomeProduto(nome,aux);

        printf("\n|Nome:%s",aux);
        printf("\n|qtde:%d",p->info.quantidadeVendida);
        printf("\n|valor Unitário:%.2f",p->info.valorVenda);
        printf("\n|===============================================|");
            p=p->next;
        }

    }else
        printf("\nCarrinho Vazio!!!");
    liberaProduto(nome);
}
