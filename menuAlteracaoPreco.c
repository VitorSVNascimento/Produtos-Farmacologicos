#include <stdio.h>
#include <stdlib.h>
#include "menuAlteracaoPreco.h"
#include "historicoPreco.h"
#include "nomearquivos.h"
#include "funcoesGerais.h"
#include "entradas.h"
#include "produto.h"
#include "validacoes.h"
void mAlterarPreco(){

    int opcao,tipo;
    float porcentagem;
    do{
        printf("\nComo deseja alterar o preço");
        printf("\n1-Unico Produto\n2-Todos os produtos\n3-Sair");
        scanf("%d",&opcao);

        if(opcao == 3)
            return;

        do{
            printf("\nO que deseja fazer\n1-Aumentar\n2-Diminuir");
            scanf("%d",&tipo);
            if(tipo!=1 && tipo!=2 )
                printf("\nOpção inválida");
        }while(tipo!=1 && tipo!=2);
        
        do{
            printf("\nForneça o valor da porcentagem");
            scanf("%f",&porcentagem);
            if(porcentagem<=0)
                printf("\nPorcentagem inválida forneça um valor maior que 0");
        }while(porcentagem<=0);

        if(tipo==2 && porcentagem>=100)
            printf("\nNão é possivel zerar o valor de um produto");
        else
            switch (opcao){
                case 1:
                    menuUnicoProduto(porcentagem,tipo);
                break;
                case 2:
                    alteraTodosProduto(porcentagem,tipo);
                default:
                    printf("\nOpção inválida");
                break;
            }

    } while (opcao != 3);


}

void menuUnicoProduto(float porcentagem, int tipo){
    int s_n,teste;
    unsigned long idProduto;
    float novoValor,valor;
    char data[11];
    FILE *fp,*fh;
    TProduto produto;
    
    if(!abrirArquivo(ARQ_HISTORICO,&fh)){
        printf("\nImpossivel abrir o arquivo %s", ARQ_HISTORICO);
        return;
    }

    do{
        if(!abrirArquivo(ARQ_PRODUTO,&fp)){
            printf("\nImpossivel abrir o arquivo %s",ARQ_PRODUTO);
            fclose(fh);
            return;
        }

        printf("\nDados do produto:");
        idProduto = recebeId();
        novoValor = 0;
        if(buscaIdProduto(idProduto,fp)!=-1){
            produto = novoProduto();
            atribuirDadosProduto(produto,idProduto-1,fp);
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
            valor = getPrecoUnitarioProduto(produto);
            if(tipo == 2)
                novoValor = valor - (valor * porcentagem/100);
            else
                novoValor = valor + (valor * porcentagem/100);

            setPrecoUnitarioProduto(produto,novoValor);
            inserirProdutoNaPosicao(produto,fp,idProduto-1);

            THistoricoPreco historico = novoHistorico();
            inicializaHistorico(historico,idProduto,data,novoValor);
            fseek(fh,0,SEEK_END);
            fwrite(historico,tamStructHistorico(),1,fh);
            fclose(fp);
            
            liberaHistorico(historico);
            liberaProduto(produto);
            printf("\n---------Alteração concluida com sucesso---------");
        }else
            printf("\nProduto não encontrado");
        printf("\nDeseja fornecer um outro id para alteração");
        printf("\n1-Sim | 2-Não");
        scanf("%d",&s_n);    
    } while (s_n==1);
    fclose(fh);
}

void alteraTodosProduto(float porcentagem, int tipo){
    int s_n,teste;
    unsigned long posicao;
    float novoValor,valor;
    char data[11];
    FILE *fp,*fh;
    TProduto produto;   
    if(!abrirArquivo(ARQ_HISTORICO,&fh)){
        printf("\nImpossivel abrir o arquivo %s", ARQ_HISTORICO);
        return;
    }

    if(!abrirArquivo(ARQ_PRODUTO,&fp)){
        printf("\nImpossivel abrir o arquivo %s",ARQ_PRODUTO);
        fclose(fh);
        return;
    }
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

    produto = novoProduto();
    THistoricoPreco historico = novoHistorico();
    posicao = 0;
    fseek(fp,0,SEEK_SET);
    while(fread(produto,tamStructProduto(),1,fp)){
        if(getIdProduto(produto)!=0){
            valor = getPrecoUnitarioProduto(produto);
                if(tipo == 2)
                    novoValor = valor - (valor * porcentagem/100);
                else
                    novoValor = valor + (valor * porcentagem/100);
            setPrecoUnitarioProduto(produto,novoValor);
            fseek(fp,tamStructProduto()*posicao,SEEK_SET);
            fwrite(produto,tamStructProduto(),1,fp);
            inicializaHistorico(historico,getIdProduto(produto),data,novoValor);
            fseek(fh,0,SEEK_END);
            fwrite(historico,tamStructHistorico(),1,fh);
        }
        posicao++;
        fseek(fp,tamStructProduto()*posicao,SEEK_SET);
        
    }
    printf("\n----------Alterações concluidas com sucesso----------");
    liberaHistorico(historico);
    fclose(fh);
    fclose(fp);
}