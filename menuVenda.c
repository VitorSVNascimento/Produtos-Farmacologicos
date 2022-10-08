#include <stdio.h>
#include <string.h>
#include "nomearquivos.h"
#include "funcoesGerais.h"
#include "entradas.h"
#include "validacoes.h"
#include "menuVenda.h"
#include "cliente.h"
#include "vendedor.h"
#include "produto.h"
#include "carrinho.h"
#include "menuCarrinho.h"
#include "venda.h"
#include "itemNotaFiscal.h"
void mVenda(){

    FILE *fv,*fp,*fc;
    if(!abrirArquivo(ARQ_VENDEDOR,&fv)){
        printf("\nErro ao abrir arquivo %s",ARQ_VENDEDOR);
        return;
    }

    if(!abrirArquivo(ARQ_CLIENTE,&fc)){
        printf("\nErro ao abrir arquivo %s",ARQ_CLIENTE);
        return;
    }

    if(!registroValidosVendedor(fv)){
        printf("\nNenhum vendedor cadastradro");
        return;
    }

    if(!registroValidos(fc)){
        printf("\nNenhum cliente cadastradro");
        return;
    }

    int s_n;
    unsigned long idVend,idCli;
    carrinho carrinhoVendas;
    do{
        if(!abrirArquivo(ARQ_PRODUTO,&fp)){
        printf("\nErro ao abrir arquivo %s",ARQ_PRODUTO);
        return;
        }

        if(!registroValidosProduto(fp)){
            printf("\nNenhum produto cadastradro");
            return;
        }
        printf("\n|--------------MENU DE VENDA-----------------|");
        if(autenticaVendedor(fv,&idVend)){
            do{
                s_n=0;
                printf("\nDigite o id do Cliente");
                idCli = recebeId();
                if(buscaIdCliente(idCli,fc)!=-1){
                    carrinhoVendas = criaCarrinho();
                    if(mCarrinho(carrinhoVendas,fp,TIPOVENDA)){
                        finalizaVenda(fv,fp,fc,idVend,idCli,carrinhoVendas);
                    }else
                        printf("\n|-------------VENDA ABANDONADA-------------|");

                }else{
                    printf("\nCliente não encontrado");
                    printf("\nDeseja fornecer outro ID?");
                    printf("\n1-Sim | 2-Não");
                    scanf("%d",&s_n);
                }


            } while (s_n==1);
        }
        printf("\nDeseja realizar outra venda?");
        printf("\n1-Sim | 2-Não");
        scanf("%d",&s_n);
        fclose(fp);
    }while(s_n==1);

    fclose(fv);
    fclose(fc);
}

int autenticaVendedor(FILE *fVendedor,unsigned long *idVend){
    TVendedor vendedor=NULL;
    char cpf[12],senha[20],aux[20];
    int tentativas = 3,tam;
    unsigned long posicao;
    printf("\n|--------------MENU DE AUTENTICAÇÃO VENDEDOR-----------------|");
    printf("\n|Forneça os dados necessario para autenticação|");

    recebeCpf(cpf);
    posicao = buscaCpfVendedor(cpf,fVendedor);
    if(posicao!=-1){
        do{
            do{
                vendedor = novoVendedor();
                tam = recebeString(senha,20,"Senha do vendedor ",0);
                padronizaString(senha);
                if(!tam)
                    printf("\nSenha não pode ser vazia");
            }while(!tam);

            atribuirDadosVendedor(vendedor,posicao,fVendedor);
            getPasswordVendedor(vendedor,aux);
            if(!strcmp(aux,senha))
                break;
            else{
                tentativas--;
                printf("\nSenha incorreta\nTentativas Restantes = %d",tentativas);
            }
        }while(tentativas>0);
    }else{
        printf("-----------CPF NÃO ENCONTRADO-----------");
        return FALHA_AUTENTICACAO;
    }
    liberaVendedor(vendedor);
    if(!tentativas){
        printf("\nTentativas Esgotadas!");
        return FALHA_AUTENTICACAO;
    }
    printf("\nLogin Efetuado com sucesso");
    *idVend = posicao+1;
    return SUCESSO_AUTENTICACAO;

}

void finalizaVenda(FILE *arqVend,FILE *arqProduto,FILE *arqCliente,unsigned long idVend,unsigned long idCli,carrinho carrinhoVenda){

    FILE *fnf,*finf;

    if(!abrirArquivo(ARQ_ITEM_NOTA_FISCAL,&finf)){
        printf("\nErro ao abrir arquivo %s",ARQ_ITEM_NOTA_FISCAL);
        return;
    }
    if(!abrirArquivo(ARQ_NOTA_FISCAL,&fnf)){
        printf("\nErro ao abrir arquivo %s",ARQ_NOTA_FISCAL);
        return;
    }

    char data[11],aux[100];
    int s_n=0,teste=0;
    unsigned long idNotaFiscal = novoIdNotaFiscal(fnf);
    TNotaFiscal nota = novoNotaFiscal();
    TVendedor vend = novoVendedor();
    TCliente cli = novoCliente();
    atribuirDadosCliente(cli,idCli-1,arqCliente);
    atribuirDadosVendedor(vend,idVend-1,arqVend);
    float valorTotal = geraValorTotal(carrinhoVenda);

    printf("\n|=========FINALIZANDO VENDA============|");
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
    printf("\n|------------LOUCO DAS PEDRAS------------|");
    printf("\n|ID Nota Compra|%lu|",idNotaFiscal);
    printf("\n|-------------DADOS VENDEDOR-------------|");
    getNomeVendedor(vend,aux);
    printf("\n|ID Vendedor|%lu| Nome: %s|",idVend,aux);
    printf("\n|-------------DADOS CLIENTE--------------|");
    getNomeCliente(cli,aux);
    printf("\n|ID Cliente|%lu| Nome: %s|",idCli,aux);
    printf("\n|Data:%s",data);
    printf("\n|=============Itens da nota====================");
    imprime(carrinhoVenda,arqProduto);
    printf("\nValor total:|R$%.2f|",valorTotal);
    printf("\n|---------------------------------------------");

    printf("\n\nDeseja realmente efetuar esta compra?");
    printf("\n1-Sim | 2-Não");
    scanf("%d",&s_n);

    if(s_n!=1){
        printf("|-----------COMPRA ABANDONADA-----------|");
        liberaVendedor(vend);
        liberaCliente(cli);
        liberaNotaFiscal(nota);
        fclose(fnf);
        fclose(finf);
        return;
    }

    inicializarNotaFiscal(nota,idNotaFiscal,idCli,idVend,data,valorTotal);
    fseek(fnf,0,SEEK_END);
    fwrite(nota,tamStructNotaFiscal(),1,fnf);

    criaItensNotaFiscal(carrinhoVenda,finf,arqProduto,idNotaFiscal);
    liberaVendedor(vend);
    liberaCliente(cli);
    liberaNotaFiscal(nota);
    fclose(fnf);
    fclose(finf);
    printf("|--------------VENDA CONCLUIDA COM SUCESSO--------------");
    return;
}

void criaItensNotaFiscal(carrinho carrinhoVenda,FILE *arqItemNotaFiscal,FILE *fProduto,unsigned long idVenda){
    TNodo *p;
    TItemNotaFiscal item = novoItemNotaFiscal();
    TProduto produto = novoProduto();
    unsigned long pos;
    unsigned int qtde;
    p=carrinhoVenda->inicio;
    setIdNotaFiscalItemNotaFiscal(item,idVenda);
    while (p!=NULL){
        setIdItemNotaFiscal(item,novoIdNotaFiscal(arqItemNotaFiscal));
        setIdProdutoItemNotaFiscal(item,p->info.idProduto);

        pos = p->info.idProduto-1;
        atribuirDadosProduto(produto,pos,fProduto);
        qtde = getQtdeEstoqueProduto(produto) - p->info.quantidadeVendida;
        setQtdeEstoqueProduto(produto,qtde);
        inserirProdutoNaPosicao(produto,fProduto,pos);

        setQuantidadeItemNotaFiscal(item,p->info.quantidadeVendida);
        setValorVendaItemNotaFiscal(item,p->info.valorVenda);

        fseek(arqItemNotaFiscal,0,SEEK_END);
        fwrite(item,tamStructItemNotaFiscal(),1,arqItemNotaFiscal);

        p=p->next;
    }
    liberaItemNotaFiscal(item);
    liberaProduto(produto);
    return;
}
