#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "funcoesGerais.h"
#include "entradas.h"
#include "cliente.h"
#include "menuCliente.h"
#include "nomearquivos.h"
#include "validacoes.h"
void mCliente(){
    setlocale(LC_ALL,"pt-BR");
    int sair;
    FILE *f;
    if(abrirArquivo(ARQ_CLIENTE,&f)){

        do{
             menuInicial("Clientes");
             scanf ("%d",&sair);


            switch(sair){

            case 1:
                cadastrarCliente(f);
            break;
            case 2:
                if(registroValidos(f))
                    alteraCliente(f);
                else
                    printf("\nNenhum cliente cadastrado!");
            break;
            case 3:
                 if(registroValidos(f))
                    consultaCliente(f);
                else
                    printf("\nNenhum cliente cadastrado!");
            break;
            case 4:
                menuExcluirCliente(f);
            break;

            }
        }while(sair!=5);
        fclose(f);

    }else
        printf("\nImpossivel abrir o arquivo");
}

void cadastrarCliente(FILE *f){

    TCliente c=novoCliente();
    if(!c){
        printf("\nImpossivel alocar memória");
        return;
    }
    char cpf[12],nome[100],email[50],telefone[15];
    int s_n,teste,repetido;
    unsigned long id;

    do{

        printf("\n-----------------Menu de Cadastro de Cliente-----------------------");
        printf("\nForneça os campos solicitados para o cadastro:");

        id = novoIdCliente(f);
        printf("\nID Cliente: %lu",id);
        recebeNome(nome);
        padronizaString(nome);
        do{

            recebeCpf(cpf);
            teste = validaCpf(cpf);
            if(!teste)
                printf("\n===========CPF INVALIDO=============");
            else{
                repetido = buscaCpfCliente(cpf,f);
                if(repetido!=-1)
                    printf("\nEste CPF já está cadastrado");
            }
        }while(!teste || repetido!=-1);
        recebeEmail(email);
        padronizaString(email);
        recebeTelefone(telefone);

        inicializarCliente(c,id,nome,cpf,email,telefone);
        inserirClienteNaPosicao(c,f,id-1);


        printf("\nCadastro realizado com sucesso");
        printf("\nDeseja cadastrar outro cliente?\n1-Sim | 2-Não: ");
        scanf("%d",&s_n);
    }while(s_n==1);
    liberaCliente(c);
}

void alteraCliente(FILE *f){

    unsigned long id,posicao;
    char aux[100];
    int s_n;


    TCliente c = novoCliente();
    if(!c){
        printf("\nNão foi possivel alocar memória!");
        return;
    }

    do{

        printf("\n-----------------Menu de Alteração de Cliente-----------------------");
        id = recebeId();
        if(id>0){
            posicao = buscaIdCliente(id,f);
            if(posicao!=-1){

                atribuirDadosCliente(c,posicao,f);
                printf("\n|-----------------Dados atuais-------------------------|");
                printaDadosCliente(c);
                printf("\nDeseja Realmente alterar?");
                printf("\n|1-Sim | 2-Não: ");
                scanf ("%d",&s_n);

                if(s_n==1){
                    if(perguntaAlteracao("Nome")==1){
                        recebeNome(aux);
                        padronizaString(aux);
                        setNomeCliente(c,aux);
                    }

                    if(perguntaAlteracao("Email")==1){
                        recebeEmail(aux);
                        padronizaString(aux);
                        setEmailCliente(c,aux);
                    }
                    if(perguntaAlteracao("Telefone")==1){
                        recebeTelefone(aux);
                        padronizaString(aux);
                        setTelefoneCliente(c,aux);
                    }

                    inserirClienteNaPosicao(c,f,posicao);
                    printf("\n|---------------Alteração Concluida--------------------|");
                    printf("\n|-----------------Dados atuais-------------------------|");
                    printaDadosCliente(c);
                }

            }else
                printf("\n---------ID não encontrado---------");
        }else
            printf("\n---------ID Inválido---------");

        printf("\nFazer mais alguma alteração?");
        printf("\n|1-Sim|n2-Não: ");
        scanf ("%d",&s_n);


    }while(s_n==1);
    liberaCliente(c);
}

void consultaCliente(FILE *f){
    int opcao;
    unsigned long id,posicao,cont;
    char cpf[12],prefixo[100];
    TCliente c = novoCliente();
        if(!c){
            printf("\nNão foi possivel alocar memória!");
            return;
        }
    do{
        printf("\n|-----------------Menu de Consulta-----------------------|");
        printf("\n|-----------Como deseja realizar a consulta?-------------|");
        printf("\n|1-Consulta por id");
        printf("\n|2-Consulta por CPF ");
        printf("\n|3-Consulta por Prefixo");
        printf("\n|4-Listar todos os clientes");
        printf("\n|5-Voltar");
        printf("\n|Opção:");
        scanf("%d",&opcao);
    switch (opcao){

    case 1:
            do{
                printf("\n|-----------------Busca Por ID Cliente---------------------------|");
                id = recebeId();
                if(id>0){
                    posicao = buscaIdCliente(id,f);
                    if(posicao!=-1){
                        atribuirDadosCliente(c,posicao,f);
                        printaDadosCliente(c);
                    }else
                        printf("\nID Não Encontrado");
                }
                else
                    printf("\nID Inválido!");
            }while(perguntaBusca("ID")==1);

        break;
        case 2:


            do{
                printf("\n|-----------------Busca Por CPF---------------------------|");
                recebeCpf(cpf);
                if(validaCpf(cpf)){
                    posicao = buscaCpfCliente(cpf,f);
                    if(posicao!=-1){
                        atribuirDadosCliente(c,posicao,f);
                        printaDadosCliente(c);
                    }else
                        printf("\nCPF Não Encontrado!");

                }else
                    printf("\nCPF Inválido!");
            }while(perguntaBusca("CPF")==1);
        break;

        case 3:

            do{
                printf("\n|---------------Busca Por Prefixo-------------------------|");
                recebePrefixo(prefixo);
                padronizaString(prefixo);
                posicao = -1;
                cont = 0;
                do{
                    posicao = buscaPrefixoCliente(prefixo,f,posicao + 1);

                    if(posicao!=-1){
                        atribuirDadosCliente(c,posicao,f);
                        printaDadosCliente(c);
                        cont++;
                    }
                }while(posicao!=-1);
                if(!cont)
                    printf("\nNenhum registro encontrado com esse prefixo!");
            }while(perguntaBusca("Prefixo")==1);
        break;


        case 4:
         listaTodos(f);


        break;
        case 5:
        break;
    }

    }while(opcao!=5);

    liberaCliente(c);
}

void printaDadosCliente(TCliente c){
    char aux[100];
    printf("\n|-----------------------------------------------|");
    printf("\n|ID:%lu",getIdCliente(c));
    getNomeCliente(c,aux);
    printf("\n|NOME:%s",aux);
    getCpfCliente(c,aux);
    printf("\n|CPF:%s",aux);
    getEmailCliente(c,aux);
    printf("\n|EMAIL:%s",aux);
    getTelefoneCliente(c,aux);
    printf("\n|TELEFONE:%s",aux);
    printf("\n|-----------------------------------------------|");

}

void listaTodos(FILE *arq){
    TCliente busca=novoCliente();
    int cont=0;
    fseek(arq,0,SEEK_SET);
    while(fread(busca,tamStruct(),1,arq)==1){
        if(getIdCliente(busca)>0){
            printaDadosCliente(busca);
            cont++;
        }

    }
    if(!cont)
        printf("\nNenhum Registro encontrado");
     liberaCliente(busca);
}

void menuExcluirCliente(FILE *f){
    unsigned long id,posicao;
   TCliente c = novoCliente();
    if(!c){
        printf("\nNão foi possivel alocar memória!");
        return;
    }
    do{
        if(registroValidos(f)){
            printf("\n-----------------Menu de Exclusão de Cliente-----------------------");
            id = recebeId();
            if(id>0){
                posicao = buscaIdCliente(id,f);
                if(posicao!=-1){
                    atribuirDadosCliente(c,posicao,f);
                    printaDadosCliente(c);
                    if(confirmaExclusao("cliente")==1){
                        excluirCliente(c,f,posicao);
                        printf("\nCliente Excluido com sucesso!");
                    }else
                        printf("\nNada foi excluido!");

                }else
                    printf("\nNenhum registro encontrado com esse ID!");
            }else
                printf("\nID Inválido!");
        }else{
            printf("Nenhum cliente cadastrado!");
            liberaCliente(c);
            return;
        }
    }while(perguntaExclusao()==1);
    liberaCliente(c);
}
