#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "funcoesGerais.h"
#include "entradas.h"
#include "nomearquivos.h"
#include "validacoes.h"
#include "produto.h"
#include "menuProduto.h"

void mProduto(){
    setlocale(LC_ALL,"pt-BR");
    int sair;
    FILE *f;
    if(abrirArquivo(ARQ_PRODUTO,&f)){

        do{
             menuInicial("Produtos");
             scanf ("%d",&sair);


            switch(sair){

            case 1:
                cadastrarProduto(f);
            break;
            case 2:
                if(registroValidosProduto(f))
                    alteraProduto(f);
                else
                    printf("\nNenhum produto cadastrado!");
            break;
            case 3:
                if(registroValidosProduto(f))
                   consultaProduto(f);
                else
                    printf("\nNenhum produto cadastrado!");

            break;
            case 4:
                menuExcluirProduto(f);
            break;

            }
        }while(sair!=5);
        fclose(f);

    }else
        printf("\nImpossivel abrir o arquivo");

}

void cadastrarProduto(FILE *f){

    TProduto produto = novoProduto();
    if(!produto){
        printf("\nImpossivel alocar memória");
        return;
    }
    const unsigned int QTDE = 0;
    char nome[100];
    float preco;
    int s_n;
    unsigned long id;

    do{

        printf("\n-----------------Menu de Cadastro de Produto-----------------------");
        printf("\nForneça os campos solicitados para o cadastro:");

        id = novoIdProduto(f);
        printf("\nID Produto: %lu",id);
        recebeNome(nome);
        padronizaString(nome);
        preco = recebePreco();


        inicializarProduto(produto,id,nome,QTDE,preco);
        inserirProdutoNaPosicao(produto,f,id-1);

        printf("\nCadastro realizado com sucesso");
        printf("\nDeseja cadastrar outro Produto?\n1-Sim | 2-Não: ");
        scanf("%d",&s_n);
    }while(s_n==1);
    liberaProduto(produto);

}

void alteraProduto(FILE *f){
    unsigned long id,posicao;
    char aux[100];
    int s_n;


    TProduto produto = novoProduto();
    if(!produto){
        printf("\nNão foi possivel alocar memória!");
        return;
    }

    do{

        printf("\n-----------------Menu de Alteração de Produto-----------------------");
        id = recebeId();
        if(id>0){
            posicao = buscaIdProduto(id,f);
            if(posicao!=-1){

                atribuirDadosProduto(produto,posicao,f);
                printf("\n|-----------------Dados atuais-------------------------|");
                printaDadosProduto(produto);
                printf("\nDeseja Realmente alterar?");
                printf("\n|1-Sim | 2-Não: ");
                scanf ("%d",&s_n);

                if(s_n==1){

                    if(perguntaAlteracao("Nome")==1){
                            recebeNome(aux);
                            padronizaString(aux);
                            setNomeProduto(produto,aux);

                    }

                    inserirProdutoNaPosicao(produto,f,posicao);
                    printf("\n|---------------Alteração Concluida--------------------|");
                    printf("\n|-----------------Dados atuais-------------------------|");
                    printaDadosProduto(produto);
                }

            }else
                printf("\n---------ID não encontrado---------");
        }else
            printf("\n---------ID Inválido---------");

        printf("\nFazer mais alguma alteração?");
        printf("\n|1-Sim|n2-Não: ");
        scanf ("%d",&s_n);


    }while(s_n==1);
    liberaProduto(produto);

}

void consultaProduto(FILE *f){
    int opcao;
    unsigned long id,posicao,cont;
    char prefixo[100];
    TProduto produto = novoProduto();
        if(!produto){
            printf("\nNão foi possivel alocar memória!");
            return;
        }
    do{
        printf("\n|-----------------Menu de Consulta-----------------------|");
        printf("\n|-----------Como deseja realizar a consulta?-------------|");
        printf("\n|1-Consulta por id");
        printf("\n|2-Consulta por Prefixo");
        printf("\n|3-Listar todos os produtoes");
        printf("\n|4-Voltar");
        printf("\n|Opção:");
        scanf("%d",&opcao);
    switch (opcao){

    case 1:
            do{
                printf("\n|-----------------Busca Por ID Produto---------------------------|");
                id = recebeId();
                if(id>0){
                    posicao = buscaIdProduto(id,f);
                    if(posicao!=-1){
                        atribuirDadosProduto(produto,posicao,f);
                        printaDadosProduto(produto);
                    }else
                        printf("\nID Não Encontrado");
                }
                else
                    printf("\nID Inválido!");
            }while(perguntaBusca("ID")==1);

        break;

        case 2:

            do{
                printf("\n|---------------Busca Por Prefixo-------------------------|");
                recebePrefixo(prefixo);
                padronizaString(prefixo);
                posicao = -1;
                cont = 0;
                do{
                    posicao = buscaPrefixoProduto(prefixo,f,posicao + 1);

                    if(posicao!=-1){
                        atribuirDadosProduto(produto,posicao,f);
                        printaDadosProduto(produto);
                        cont++;
                    }
                }while(posicao!=-1);
                if(!cont)
                    printf("\nNenhum registro encontrado com esse prefixo!");
            }while(perguntaBusca("Prefixo")==1);
        break;


        case 3:
         listaTodosProduto(f);


        break;
        case 4:
        break;
    }

    }while(opcao!=4);

    liberaProduto(produto);

}

void menuExcluirProduto(FILE *f){
   unsigned long id,posicao;
   TProduto produto = novoProduto();
    if(!produto){
        printf("\nNão foi possivel alocar memória!");
        return;
    }
    do{
        if(registroValidosProduto(f)){
            printf("\n-----------------Menu de Exclusão de Produto-----------------------");
            id = recebeId();
            if(id>0){
                posicao = buscaIdProduto(id,f);
                if(posicao!=-1){
                    atribuirDadosProduto(produto,posicao,f);
                    printaDadosProduto(produto);
                    if(confirmaExclusao("produto")==1){
                        excluirProduto(produto,f,posicao);
                        printf("\nProduto Excluido com sucesso!");
                    }else
                        printf("\nNada foi excluido!");

                }else
                    printf("\nNenhum registro encontrado com esse ID!");
            }else
                printf("\nID Inválido!");
        }else{
            printf("Nenhum produto cadastrado!");
            liberaProduto(produto);
            return;
        }


    }while(perguntaExclusao()==1);
    liberaProduto(produto);
}

void printaDadosProduto(TProduto produto){
    char aux[100];
    printf("\n|-----------------------------------------------|");
    printf("\n|ID:%lu",getIdProduto(produto));
    getNomeProduto(produto,aux);
    printf("\n|NOME:%s",aux);
    printf("\n|QUANTIDADE EM ESTOQUE: %u",getQtdeEstoqueProduto(produto));
    printf("\n|PREÇO UNITÁRIO = R$ %.2f",getPrecoUnitarioProduto(produto));
    printf("\n|-----------------------------------------------|");

}

void listaTodosProduto(FILE *arq){
    TProduto busca=novoProduto();
    int cont=0;
    fseek(arq,0,SEEK_SET);
    while(fread(busca,tamStructProduto(),1,arq)==1){
        if(getIdProduto(busca)>0){
            printaDadosProduto(busca);
            cont++;
        }

    }
    if(!cont)
        printf("\nNenhum Registro encontrado");
     liberaProduto(busca);
}

void listaProdutosEmEstoque(FILE *arq){
    TProduto busca=novoProduto();
    int cont=0;
    fseek(arq,0,SEEK_SET);
    while(fread(busca,tamStructProduto(),1,arq)==1){
        if(getIdProduto(busca)>0 && getQtdeEstoqueProduto(busca)){
            printaDadosProduto(busca);
            cont++;
        }

    }
    if(!cont)
        printf("\nNenhum Registro encontrado");
     liberaProduto(busca);
    return;
}
