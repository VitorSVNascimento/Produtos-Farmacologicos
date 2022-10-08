#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "funcoesGerais.h"
#include "entradas.h"
#include "vendedor.h"
#include "menuVendedor.h"
#include "nomearquivos.h"
#include "validacoes.h"
void mVendedor(){
    setlocale(LC_ALL,"pt-BR");
    int sair;
    FILE *f;
    if(abrirArquivo(ARQ_VENDEDOR,&f)){

        do{
             menuInicial("Vendedores");
             scanf ("%d",&sair);


            switch(sair){

            case 1:
                cadastrarVendedor(f);
            break;
            case 2:
                if(registroValidosVendedor(f))
                    alteraVendedor(f);
                else
                    printf("\nNenhum vendedor cadastrado!");
            break;
            case 3:
                if(registroValidosVendedor(f))
                    consultaVendedor(f);
                else
                   printf("\nNenhum vendedor cadastrado!");
            break;
            case 4:
                menuExcluirVendedor(f);
            break;

            }
        }while(sair!=5);
        fclose(f);

    }else
        printf("\nImpossivel abrir o arquivo");

}

void cadastrarVendedor(FILE *f){

    TVendedor v = novoVendedor();
    if(!v){
        printf("\nImpossivel alocar memória");
        return;
    }
    char cpf[12],nome[100],email[50],telefone[15],password[20];
    int s_n,teste,repetido;
    unsigned long id;

    do{

        printf("\n-----------------Menu de Cadastro de Vendedor-----------------------");
        printf("\nForneça os campos solicitados para o cadastro:");

        id = novoIdVendedor(f);
        printf("\nID Vendedor: %lu",id);
        recebeNome(nome);
        padronizaString(nome);
        do{
            recebeCpf(cpf);
            teste = validaCpf(cpf);
            if(!teste)
                printf("\n===========CPF INVALIDO=============");
            else{
                repetido = buscaCpfVendedor(cpf,f);
                if(repetido!=-1)
                    printf("\nEste CPF já está cadastrado");
            }
        }while(!teste || repetido!=-1);
        do{
            recebeEmail(email);
            padronizaString(email);
            repetido = buscaEmailVendedor(email,f);
            if(repetido!=-1)
                printf("\nEste Email já está cadastrado");
        }while (repetido!=-1);
        recebeTelefone(telefone);
        do{
            teste = recebeString(password,20,"SENHA",0);
            if(!teste)
                printf("\nSenha não pode ser vazia");
        }while(!teste);
        padronizaString(password);

        inicializarVendedor(v,id,nome,cpf,email,telefone,password);
        inserirVendedorNaPosicao(v,f,id-1);

        printf("\nCadastro realizado com sucesso");
        printf("\nDeseja cadastrar outro Vendedor?\n1-Sim | 2-Não: ");
        scanf("%d",&s_n);
    }while(s_n==1);
    liberaVendedor(v);

}

void alteraVendedor(FILE *f){
    unsigned long id,posicao;
    char aux[100];
    int s_n,teste;


    TVendedor v = novoVendedor();
    if(!v){
        printf("\nNão foi possivel alocar memória!");
        return;
    }

    do{

        printf("\n-----------------Menu de Alteração de Vendedor-----------------------");
        id = recebeId();
        if(id>0){
            posicao = buscaIdVendedor(id,f);
            if(posicao!=-1){

                atribuirDadosVendedor(v,posicao,f);
                printf("\n|-----------------Dados atuais-------------------------|");
                printaDadosVendedor(v);
                printf("\nDeseja Realmente alterar?");
                printf("\n|1-Sim | 2-Não: ");
                scanf ("%d",&s_n);

                if(s_n==1){
                    if(perguntaAlteracao("Nome")==1){
                        recebeNome(aux);
                        padronizaString(aux);
                        setNomeVendedor(v,aux);
                    }

                    if(perguntaAlteracao("Email")==1){
                        do{
                            recebeEmail(aux);
                            padronizaString(aux);
                            teste = buscaEmailVendedor(aux,f);
                            if(teste!=-1){
                                printf("\nEste Email já está cadastrado!");
                                printf("\nDeseja sair da alteração de email?\n1-Sim | 2-Não: ");
                                scanf("%d",&s_n);
                            }else
                                setEmailVendedor(v,aux);
                        }while(teste!=-1 && s_n!=1);
                    }
                    if(perguntaAlteracao("Telefone")==1){
                        recebeTelefone(aux);
                        padronizaString(aux);
                        setTelefoneVendedor(v,aux);
                    }
                    if(perguntaAlteracao("Senha")==1){
                        if(menuAlteraSenha(f,posicao,aux)){
                            printf("\nSenha alterada com sucesso");
                            setPasswordVendedor(v,aux);
                        }else
                            printf("\nNão foi possivel alterar a senha!");
                    }

                    inserirVendedorNaPosicao(v,f,posicao);
                    printf("\n|---------------Alteração Concluida--------------------|");
                    printf("\n|-----------------Dados atuais-------------------------|");
                    printaDadosVendedor(v);
                }

            }else
                printf("\n---------ID não encontrado---------");
        }else
            printf("\n---------ID Inválido---------");

        printf("\nFazer mais alguma alteração?");
        printf("\n|1-Sim|n2-Não: ");
        scanf ("%d",&s_n);


    }while(s_n==1);
    liberaVendedor(v);

}

void printaDadosVendedor(TVendedor v){
    char aux[100];
    printf("\n|-----------------------------------------------|");
    printf("\n|ID:%lu",getIdVendedor(v));
    getNomeVendedor(v,aux);
    printf("\n|NOME:%s",aux);
    getCpfVendedor(v,aux);
    printf("\n|CPF:%s",aux);
    getEmailVendedor(v,aux);
    printf("\n|EMAIL:%s",aux);
    getTelefoneVendedor(v,aux);
    printf("\n|TELEFONE:%s",aux);
    printf("\n|-----------------------------------------------|");

}


void listaTodosVendedor(FILE *arq){
    TVendedor busca=novoVendedor();
    int cont=0;
    fseek(arq,0,SEEK_SET);
    while(fread(busca,tamStructVendedor(),1,arq)==1){
        if(getIdVendedor(busca)>0){
            printaDadosVendedor(busca);
            cont++;
        }

    }
    if(!cont)
        printf("\nNenhum Registro encontrado");
     liberaVendedor(busca);
}

int menuAlteraSenha(FILE *f,unsigned long pos,char *senha){
    int i,s_n=0;
    for(i=3;i>0;i--){
        printf("\nDigite a senha atual");
        printf("\nTentativas Restantes = %d\nID do vendedor = %lu",i,pos+1);
        recebeString(senha,20,"Senha",0);
        padronizaString(senha);
        if(validaSenha(f,pos,senha))
            break;
        else{
            printf("\nSenha Incorreta!");
            printf("Deseja sair da alteração de senha?\n1-Sim | 2-Não: ");
            scanf("%d",&s_n);
            if(s_n==1)
                return 0;
        }
    }
    if(!i){
        printf("\nTentativas esgotadas!");
        return 0;
    }
    do{
        printf("\nDigite a nova senha");
        i = recebeString(senha,20,"Senha",0);
        if(!i)
            printf("\nSenha não pode ser vazia!");
    }while(!i);
    padronizaString(senha);
    return 1;
}

void consultaVendedor(FILE *f){
    int opcao;
    unsigned long id,posicao,cont;
    char cpf[12],prefixo[100];
    TVendedor v = novoVendedor();
        if(!v){
            printf("\nNão foi possivel alocar memória!");
            return;
        }
    do{
        printf("\n|-----------------Menu de Consulta-----------------------|");
        printf("\n|-----------Como deseja realizar a consulta?-------------|");
        printf("\n|1-Consulta por id");
        printf("\n|2-Consulta por CPF ");
        printf("\n|3-Consulta por Prefixo");
        printf("\n|4-Listar todos os vendedores");
        printf("\n|5-Voltar");
        printf("\n|Opção:");
        scanf("%d",&opcao);
    switch (opcao){

    case 1:
            do{
                printf("\n|-----------------Busca Por ID Vendedor---------------------------|");
                id = recebeId();
                if(id>0){
                    posicao = buscaIdVendedor(id,f);
                    if(posicao!=-1){
                        atribuirDadosVendedor(v,posicao,f);
                        printaDadosVendedor(v);
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
                    posicao = buscaCpfVendedor(cpf,f);
                    if(posicao!=-1){
                        atribuirDadosVendedor(v,posicao,f);
                        printaDadosVendedor(v);
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
                    posicao = buscaPrefixoVendedor(prefixo,f,posicao + 1);

                    if(posicao!=-1){
                        atribuirDadosVendedor(v,posicao,f);
                        printaDadosVendedor(v);
                        cont++;
                    }
                }while(posicao!=-1);
                if(!cont)
                    printf("\nNenhum registro encontrado com esse prefixo!");
            }while(perguntaBusca("Prefixo")==1);
        break;


        case 4:
         listaTodosVendedor(f);


        break;
        case 5:
        break;
    }

    }while(opcao!=5);

    liberaVendedor(v);

}

void menuExcluirVendedor(FILE *f){
   unsigned long id,posicao;
   TVendedor v = novoVendedor();
    if(!v){
        printf("\nNão foi possivel alocar memória!");
        return;
    }
    do{
        if(registroValidosVendedor(f)){
            printf("\n-----------------Menu de Exclusão de Vendedor-----------------------");
            id = recebeId();
            if(id>0){
                posicao = buscaIdVendedor(id,f);
                if(posicao!=-1){
                    atribuirDadosVendedor(v,posicao,f);
                    printaDadosVendedor(v);
                    if(confirmaExclusao("vendedor")==1){
                        excluirVendedor(v,f,posicao);
                        printf("\nVendedor Excluido com sucesso!");
                    }else
                        printf("\nNada foi excluido!");

                }else
                    printf("\nNenhum registro encontrado com esse ID!");
            }else
                printf("\nID Inválido!");
        }else{
            printf("Nenhum vendedor cadastrado!");
            liberaVendedor(v);
            return;
        }


    }while(perguntaExclusao()==1);
    liberaVendedor(v);
}
