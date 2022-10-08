#include "menuCompra.h"
#include "funcoesGerais.h"
#include "fornecedor.h"
#include "produto.h"
#include "carrinho.h"
#include "nomearquivos.h"
#include "entradas.h"
#include "menuCarrinho.h"
#include "compra.h"
#include "itemNotaCompra.h"
#include "validacoes.h"

void mCompra(){

    FILE *ff,*fp;
    
    if(!abrirArquivo(ARQ_FORNECEDOR,&ff)){
        printf("\nErro ao abrir arquivo %s",ARQ_FORNECEDOR);
        return;
    }
    if(!abrirArquivo(ARQ_PRODUTO,&fp)){
        printf("\nErro ao abrir arquivo %s",ARQ_PRODUTO);
        return;
    }

    if(!registroValidosFornecedor(ff)){
        printf("\nNenhum fornecedor cadastradro");
        return;
    }
    if(!registroValidosProduto(fp)){
        printf("\nNenhum produto cadastradro");
        return;
    }  
    int s_n;
    unsigned long id;
    carrinho carrinhoCompras;
    do{
        printf("\n|--------------MENU DE COMPRA-----------------|");
        printf("\nDigite o id do fornecedor");
        id = recebeId();
        if(buscaIdFornecedor(id,ff)!=-1){
            carrinhoCompras = criaCarrinho();
            if(mCarrinho(carrinhoCompras,fp,TIPOCOMPRA)){
                if(carrinhoCompras->tamanho)
                    finalizaCompra(ff,fp,carrinhoCompras,id);
            terminaCarrinho(carrinhoCompras);
            }else
                printf("\n|-------------COMPRA ABANDONADA-------------|");
        }else
            printf("\n-------------FORNECEDOR NÃO ENCONTRADO-------------");
        printf("\nDeseja realizar outra compra?\n1-Sim | 2-Não: ");
        scanf("%d",&s_n);

    }while(s_n==1);

    fclose(ff);
    fclose(fp);

}

void finalizaCompra(FILE *arqForn,FILE *arqProduto,carrinho carrinhoCompra,unsigned long idForn){

    FILE *fnc,*finc;
    if(!abrirArquivo(ARQ_ITEM_NOTA_COMPRA,&finc)){
        printf("\nErro ao abrir arquivo %s",ARQ_ITEM_NOTA_COMPRA);
        return;
    }
    if(!abrirArquivo(ARQ_NOTA_COMPRA,&fnc)){
        printf("\nErro ao abrir arquivo %s",ARQ_NOTA_COMPRA);
        return;
    }
    char data[11],aux[100];
    int s_n=0,teste=0;
    unsigned long idNota = novoIdNotaCompra(fnc);
    TNotaCompra nota = novoNotaCompra();
    TFornecedor forn = novoFornecedor();
    atribuirDadosFornecedor(forn,idForn-1,arqForn);
    float valorTotal = geraValorTotal(carrinhoCompra);

    printf("\n|=========FINALIZANDO COMPRA============|");
    dataSistema(data);
    printf("\n|Data do sistema:%s",data);
    printf("\n|Deseja manter a data do sistema?");
    printf("\n1-Sim | 2-Não");
    printf("\nOpção:|");
    scanf("%d",&s_n);
    if(s_n!=1)
        do{
            recebeData(data);
            teste = validaData(data);
            if(!teste)
                printf("\n====Data Invalida====");
        }while(!teste);
    getNomeFornecedor(forn,aux);
    printf("\n|------------%s------------|",aux);
    printf("\n|ID Fornecedor|%lu||",getIdFornecedor(forn));
    printf("\n|ID Nota Compra|%lu|",idNota);
    printf("\n|Data:%s",data);
    printf("\n|=============Itens da nota====================");
    imprime(carrinhoCompra,arqProduto);
    printf("\nValor total:|R$%.2f|",valorTotal);
    printf("\n|---------------------------------------------");

    printf("\n\nDeseja realmente efetuar esta compra?");
    printf("\n1-Sim | 2-Não");
    scanf("%d",&s_n);
    if(s_n!=1){
        printf("|-----------COMPRA ABANDONADA-----------|");
        liberaFornecedor(forn);
        liberaNotaCompra(nota);
        fclose(fnc);
        fclose(finc);
        return;
    }
    inicializarNotaCompra(nota,idNota,idForn,data,valorTotal);
    fseek(fnc,0,SEEK_END);
    fwrite(nota,tamStructNotaCompra(),1,fnc);


    criaItensNotaCompra(carrinhoCompra,idNota,finc,arqProduto);
    liberaFornecedor(forn);
    liberaNotaCompra(nota);
    fclose(fnc);
    fclose(finc);
    printf("|-----------COMPRA CONCLUIDA COM SUCESSO-----------|");
    return;
}

void criaItensNotaCompra(carrinho carrinhoCompra,unsigned long idNotaCompra,FILE *arqItemNotaCompra,FILE *fproduto){
    TNodo *p;
    TItemNotaCompra item = novoItemNotaCompra();
    TProduto produto = novoProduto();
    unsigned long pos;
    unsigned int qtde;
    p=carrinhoCompra->inicio;
    setIdNotaCompraItem(item,idNotaCompra);
    while(p!=NULL){
        setIdItemNotaCompra(item,novoIdItemNotaCompra(arqItemNotaCompra));
        setIdProdutoItem(item,p->info.idProduto);

        pos = getIdProdutoItem(item)-1;
        atribuirDadosProduto(produto,pos,fproduto);
        qtde = getQtdeEstoqueProduto(produto) + p->info.quantidadeVendida;
        setQtdeEstoqueProduto(produto,qtde);
        inserirProdutoNaPosicao(produto,fproduto,pos);

        setQuantidadeItemNotaCompra(item,p->info.quantidadeVendida);
        setValorUnitarioItemNotaCompra(item,p->info.valorVenda);

        fseek(arqItemNotaCompra,0,SEEK_END);
        fwrite(item,tamStructItemNotaCompra(),1,arqItemNotaCompra);

        p=p->next;
    }

    liberaItemNotaCompra(item);
    liberaProduto(produto);
    return;
}
