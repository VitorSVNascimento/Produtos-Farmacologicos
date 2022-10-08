#include <string.h>
#include "relatorios.h"
#include "nomearquivos.h"
#include "fornecedor.h"
#include "vendedor.h"
#include "cliente.h"
#include "produto.h"
#include "funcoesGerais.h"
#include "venda.h"
#include "entradas.h"
#include "validacoes.h"
#include "historicoPreco.h"
#include "menuVendedor.h"
void mRelatorio(){
    int opcao;
    do{
        printf("\n|Qual relatório deseja gerar");
        printf("\n|1-Dados de uma nota Fiscal e os itens associados a ela");
        printf("\n|2-Dados de uma compra e os itens associados a ela");
        printf("\n|3-Compras efetuadas por um cliente em uma data específica, bem como em um intervalo de datas");
        printf("\n|4-Vendas efetuadas por um vendedor em um dia específico");
        printf("\n|5-Vendas realizadas por um vendedor em um determinado mês");
        printf("\n|6-O(os) vendedor(es) com maior valor de venda em um determinado mês");
        printf("\n|7-O vendedor(es) com maior valor de venda em um intervalo de datas");
        printf("\n|8-Histórico de valor de venda de um determinado produto");
        printf("\n|9-Sair");
        printf("\n|Opção:|");
        scanf("%d",&opcao);
        switch(opcao){
            case 1:
                relatorioUm();
            break;
            case 2:
                relatorioDois();
            break;
            case 3:
                relatorioTres();
            break;
            case 4:
                relatorioQuatro();
            break;
            case 5:
                relatorioCinco();
            break;
            case 6:
                relatorioSeis();
            break;
            case 7:
                relatorioSete();
            break;
            case 8:
                relatorioOito();
            break;

        }


    }while(opcao!=9);


}
void relatorioUm(){
    FILE *fv,*fnf,*finf,*fc,*fp,*arqTxt;

    if(!abrirArquivo(ARQ_NOTA_FISCAL,&fnf)){
        printf("\nImpossivel abrir o arquivo %s",ARQ_NOTA_FISCAL);
        return;
    }

    if(!ftell(fnf) / tamStructNotaFiscal()){
        printf("\nNenhuma nota fiscal cadastrada");
        fclose(fnf);
        return;
    }

    if(!abrirArquivo(ARQ_VENDEDOR,&fv)){
        printf("\nImpossivel abrir o arquivo %s",ARQ_VENDEDOR);
        return;       
    }
    if(!abrirArquivo(ARQ_PRODUTO,&fp)){
        printf("\nImpossivel abrir o arquivo %s",ARQ_PRODUTO);
    return;
    }

    if(!abrirArquivo(ARQ_CLIENTE,&fc)){
        printf("\nImpossivel abrir o arquivo %s",ARQ_CLIENTE);
    }
    if(!abrirArquivo(ARQ_ITEM_NOTA_FISCAL,&finf)){
        printf("\nImpossivel abrir o arquivo %s",ARQ_ITEM_NOTA_FISCAL);
    }

    int opcao,s_n=0;
    unsigned long id,posicao;
    TNotaFiscal nota;
    char nomeArquivo[50];
    do{
        printf("\nForneça o id da nota:");
        scanf("%lu",&id);
        posicao = buscaIdNotaFiscal(id,fnf);
        if(posicao!=-1){
            nota = novoNotaFiscal();
            atribuirDadosNotaFiscal(nota,posicao,fnf);

            opcao = perguntaRelatorio();
            if(opcao==1){
                recebeNomeTXT(nomeArquivo);
                if(!abrirArquivo(nomeArquivo,&arqTxt)){
                    printf("\nImpossivel gerar o arquivo txt!");
                    return;
                }else{
                    printaNotaFiscalTexto(nota,arqTxt,fp,fv,finf,fc);
                    fclose(arqTxt);
                }
            }

            else
                printaNotaFiscalTela(nota,fp,fv,finf,fc);

            liberaNotaFiscal(nota);
        }else
            printf("\n|------------NOTA FISCAL NÃO ENCONTRADA------------|");

    } while (s_n==1);
    


}
void relatorioDois(){
    FILE *ff,*fnc,*finc,*fp,*arqTxt;

    if(!abrirArquivo(ARQ_NOTA_COMPRA,&fnc)){
        printf("\nImpossivel abrir o arquivo %s",ARQ_NOTA_COMPRA);
        return;
    }
    if(ftell(fnc) / tamStructNotaCompra()){
        printf("\nNenhuma nota de compra registrada");
        fclose(fnc);
        return;
    }

    if(!abrirArquivo(ARQ_FORNECEDOR,&ff)){
        printf("\nImpossivel abrir o arquivo %s",ARQ_FORNECEDOR);
        return;
    }

    if(!abrirArquivo(ARQ_ITEM_NOTA_COMPRA,&finc)){
        printf("\nImpossivel abrir o arquivo %s",ARQ_ITEM_NOTA_COMPRA);
        return;
    }
    if(!abrirArquivo(ARQ_PRODUTO,&fp)){
        printf("\nImpossivel abrir o arquivo %s",ARQ_PRODUTO);
        return;
    }
    
    int opcao,s_n=0;
    unsigned long id,posicao;
    TNotaCompra nota;
    char nomeArquivo[50];

    do{
        printf("\nForneça o id da nota:");
        scanf("%lu",&id);
        posicao = buscaIdNotaCompra(id,fnc);
        if(posicao!=-1){
            nota = novoNotaCompra();
            atribuirDadosNotaCompra(nota,posicao,fnc);

            opcao = perguntaRelatorio();
            if(opcao==1){
                recebeNomeTXT(nomeArquivo);
                if(!abrirArquivo(nomeArquivo,&arqTxt)){
                    printf("\nImpossivel gerar o arquivo txt!");
                    return;
                }else{
                    printaNotaCompraTexto(nota,arqTxt,fp,ff,finc);
                    fclose(arqTxt);
                }
            }else
                printaNotaCompraTela(nota,fp,ff,finc);

            liberaNotaCompra(nota);
        }else
            printf("\n|------------NOTA DE COMPRA NÃO ENCONTRADA------------|");

        printf("\nDeseja consultar outra compra?");
        printf("\n1-Sim | 2-Não");
        scanf("%d",&s_n);
    }while(s_n==1);

    fclose(ff);
    fclose(finc);
    fclose(fnc);
    fclose(fp);
}

void relatorioTres(){

    FILE *fv,*fnf,*finf,*fc,*fp,*arqTxt;
    if(!abrirArquivo(ARQ_NOTA_FISCAL,&fnf)){
        printf("\nImpossivel abrir o arquivo %s",ARQ_NOTA_FISCAL);
        return;
    }

    if(!ftell(fnf) / tamStructNotaFiscal()){
        printf("\nNenhuma nota fiscal cadastrada");
        fclose(fnf);
        return;
    }

    if(!abrirArquivo(ARQ_VENDEDOR,&fv)){
        printf("\nImpossivel abrir o arquivo %s",ARQ_VENDEDOR);
        return;       
    }
    if(!abrirArquivo(ARQ_PRODUTO,&fp)){
        printf("\nImpossivel abrir o arquivo %s",ARQ_PRODUTO);
        return;
    }
    if(!abrirArquivo(ARQ_CLIENTE,&fc)){
        printf("\nImpossivel abrir o arquivo %s",ARQ_CLIENTE);
        return;
    }
    if(!abrirArquivo(ARQ_ITEM_NOTA_FISCAL,&finf)){
        printf("\nImpossivel abrir o arquivo %s",ARQ_ITEM_NOTA_FISCAL);
        return;
    }
    char data1[11], data2[11], aux[11],nomeArquivo[50];
    int s_n=0,tipoDeBusca,validar,opcao;
    unsigned long idCliente;
    TNotaFiscal nota;
    do{
        printf("\nForneça o id do Cliente que deseja");
        idCliente = recebeId();
        if(buscaIdCliente(idCliente,fc)!=-1){
            tipoDeBusca = perguntaRelatorioDatas();
            do{
                printf("\nForneça a data inicial");
                recebeData(data1);
                validar = validaData(data1);
                if(!validar)
                    printf("\nData Inválida!");
            } while (!validar);
            if(tipoDeBusca == 2)
                do{
                    printf("\nForneça a data final");
                    recebeData(data2);
                    validar = validaData(data2);
                    if(!validar)
                        printf("\nData Inválida!");

                    if(dataMaior(data1,data2)){
                        strcpy(aux,data1);
                        strcpy(data1,data2);
                        strcpy(data2,aux);
                    }

                } while (!validar);
            else
                data2[0] = '\0';
            opcao = perguntaRelatorio();
            if(opcao==1){
                recebeNomeTXT(nomeArquivo);
                if(!abrirArquivo(nomeArquivo,&arqTxt)){
                    printf("\nImpossivel gerar o arquivo txt!");
                    return;
                }   
            }
            nota = novoNotaFiscal();
            fseek(fnf,0,SEEK_SET);
            while(fread(nota,tamStructNotaFiscal(),1,fnf)==1){
                if(verificaNotaFiscal(nota,data1,data2,TIPO_CLIENTE,idCliente)){
                    if(opcao==1)
                        printaNotaFiscalTexto(nota,arqTxt,fp,fv,finf,fc);
                    else
                        printaNotaFiscalTela(nota,fp,fv,finf,fc);
                    
                }

            }

            if(opcao==1)
                fclose(arqTxt);
        
        }else
            printf("\nCliente não encontrado!");
        printf("\nDeseja gerar um novo relatório deste tipo");
        printf("\n1-Sim | 2-Não");
        scanf("%d",&s_n);
    } while (s_n==1);

    liberaNotaFiscal(nota);
    fclose(fc);
    fclose(fv);
    fclose(finf);
    fclose(fnf);
    fclose(fp);
}

void relatorioQuatro(){

    FILE *fv,*fnf,*finf,*fc,*fp,*arqTxt;
    if(!abrirArquivo(ARQ_NOTA_FISCAL,&fnf)){
        printf("\nImpossivel abrir o arquivo %s",ARQ_NOTA_FISCAL);
        return;
    }

    if(!ftell(fnf) / tamStructNotaFiscal()){
        printf("\nNenhuma nota fiscal cadastrada");
        fclose(fnf);
        return;
    }
    if(!abrirArquivo(ARQ_VENDEDOR,&fv)){
        printf("\nImpossivel abrir o arquivo %s",ARQ_VENDEDOR);
        return;       
    }
    if(!abrirArquivo(ARQ_PRODUTO,&fp)){
        printf("\nImpossivel abrir o arquivo %s",ARQ_PRODUTO);
        return;
    }

    if(!abrirArquivo(ARQ_CLIENTE,&fc)){
        printf("\nImpossivel abrir o arquivo %s",ARQ_CLIENTE);
        return;
    }
    if(!abrirArquivo(ARQ_ITEM_NOTA_FISCAL,&finf)){
        printf("\nImpossivel abrir o arquivo %s",ARQ_ITEM_NOTA_FISCAL);
        return;
    }

    char data[11],nomeArquivo[50];
    int s_n=0,validar,opcao;
    unsigned long idVendedor;
    TNotaFiscal nota;
    //4-Vendas efetuadas por um vendedor em um dia específico
    do{
    
        printf("\nForneça o id do Vendedor que deseja");
        idVendedor = recebeId();
        if(buscaIdVendedor(idVendedor,fv)!=-1){
            do{
                printf("\nForneça a data inicial");
                recebeData(data);
                validar = validaData(data);
                if(!validar)
                    printf("\nData Inválida!");
            } while (!validar);
            opcao = perguntaRelatorio();
            if(opcao==1){
                recebeNomeTXT(nomeArquivo);
                if(!abrirArquivo(nomeArquivo,&arqTxt)){
                    printf("\nImpossivel gerar o arquivo txt!");
                    return;
                }   
            }
            nota = novoNotaFiscal();
            fseek(fnf,0,SEEK_SET);
            while(fread(nota,tamStructNotaFiscal(),1,fnf)==1){
                if(verificaNotaFiscal(nota,data,data,TIPO_VENDEDOR,idVendedor)){
                    if(opcao==1)
                        printaNotaFiscalTexto(nota,arqTxt,fp,fv,finf,fc);
                    else
                        printaNotaFiscalTela(nota,fp,fv,finf,fc);
                    
                }

            }

            if(opcao==1)
                fclose(arqTxt);

        }else
            printf("\nCliente não encontrado!");   
        printf("\nDeseja gerar um novo relatório deste tipo");
        printf("\n1-Sim | 2-Não");
        scanf("%d",&s_n);    
    } while (s_n==1);

    liberaNotaFiscal(nota);
    fclose(fc);
    fclose(fv);
    fclose(finf);
    fclose(fnf);
    fclose(fp);  

}


void relatorioCinco(){
    FILE *fv,*fnf,*finf,*fc,*fp,*arqTxt;
    if(!abrirArquivo(ARQ_NOTA_FISCAL,&fnf)){
        printf("\nImpossivel abrir o arquivo %s",ARQ_NOTA_FISCAL);
        return;
    }

    if(!ftell(fnf) / tamStructNotaFiscal()){
        printf("\nNenhuma nota fiscal cadastrada");
        fclose(fnf);
        return;
    }
    if(!abrirArquivo(ARQ_VENDEDOR,&fv)){
        printf("\nImpossivel abrir o arquivo %s",ARQ_VENDEDOR);
        return;       
    }
    if(!abrirArquivo(ARQ_PRODUTO,&fp)){
        printf("\nImpossivel abrir o arquivo %s",ARQ_PRODUTO);
    return;
    }
    if(!abrirArquivo(ARQ_CLIENTE,&fc)){
        printf("\nImpossivel abrir o arquivo %s",ARQ_CLIENTE);
        return;
    }
    if(!abrirArquivo(ARQ_ITEM_NOTA_FISCAL,&finf)){
        printf("\nImpossivel abrir o arquivo %s",ARQ_ITEM_NOTA_FISCAL);
        return;
    }
    
    char nomeArquivo[50];
    int s_n=0,opcao,mes;
    unsigned long idVendedor;
    TNotaFiscal nota;
    do{
    
        printf("\nForneça o id do Vendedor que deseja");
        idVendedor = recebeId();
        if(buscaIdVendedor(idVendedor,fv)!=-1){
            do{
                printf("\nForneça o mês que deseja consultar");
                scanf("%d",&mes);
                if(mes < 1 || mes > 12)
                    printf("\nMes inválido");
            } while (mes < 1 || mes > 12);
            opcao = perguntaRelatorio();
            if(opcao==1){
                recebeNomeTXT(nomeArquivo);
                if(!abrirArquivo(nomeArquivo,&arqTxt)){
                    printf("\nImpossivel gerar o arquivo txt!");
                    return;
                }   
            }
            nota = novoNotaFiscal();
            fseek(fnf,0,SEEK_SET);
            while(fread(nota,tamStructNotaFiscal(),1,fnf)==1){
                if(verificaMesVendedorNotaFiscal(nota,mes,idVendedor)){
                    if(opcao==1)
                        printaNotaFiscalTexto(nota,arqTxt,fp,fv,finf,fc);
                    else
                        printaNotaFiscalTela(nota,fp,fv,finf,fc);
                    
                }

            }

            if(opcao==1)
                fclose(arqTxt);
            liberaNotaFiscal(nota);
        }else
            printf("\nVendedor não encontrado!");   
        printf("\nDeseja gerar um novo relatório deste tipo");
        printf("\n1-Sim | 2-Não");
        scanf("%d",&s_n);    
    } while (s_n==1);

    
    fclose(fc);
    fclose(fv);
    fclose(finf);
    fclose(fnf);
    fclose(fp);  

}

void relatorioSeis(){
FILE *fv,*fnf,*arqTxt;

    if(!abrirArquivo(ARQ_NOTA_FISCAL,&fnf)){
    printf("\nImpossivel abrir o arquivo %s",ARQ_NOTA_FISCAL);
    return;       
    }
    if(!ftell(fnf) / tamStructNotaFiscal()){
        printf("\nNenhuma nota fiscal encontrada");
        fclose(fnf);
        return;
    }

    if(!abrirArquivo(ARQ_VENDEDOR,&fv)){
        printf("\nImpossivel abrir o arquivo %s",ARQ_VENDEDOR);
        return;       
    }

    int opcao,mes;
    float maiorValor ;
    char nomeArquivo[50];
    do{
        printf("\nForneça o mês que deseja consultar");
        scanf("%d",&mes);
        if(mes < 1 || mes > 12)
            printf("\nMes inválido");
    } while (mes < 1 || mes > 12);
    maiorValor = calculaMaiorValorVenda(fv,fnf,"","",mes);
    if(maiorValor>0){
        opcao = perguntaRelatorio();
        if(opcao==1){
            recebeNomeTXT(nomeArquivo);
            if(!abrirArquivo(nomeArquivo,&arqTxt)){
                printf("\nImpossivel gerar o arquivo txt!");
                return;
            }   
        }
        if(opcao==1){
            fprintf(arqTxt,"\n|Maior valor de Venda = R$ %.2f|",maiorValor);
            fprintf(arqTxt,"\n--------------------------------------------");
            fprintf(arqTxt,"\nVendedores com esse valor de venda:");
        }else{
            printf("\nMaior valor de Venda = R$ %.2f",maiorValor);
            printf("\n--------------------------------------------");
            printf("\nVendedores com esse valor de venda:");
        }
        TVendedor vendedor = novoVendedor();
        fseek(fv,0,SEEK_SET);
        while (fread(vendedor,tamStructVendedor(),1,fv)){
            if(calculaValorVendaVendedor(fv,fnf,"","",getIdVendedor(vendedor),mes)==maiorValor){
                if(opcao==1)
                    printaDadosVendedorTexto(vendedor,arqTxt);
                else
                    printaDadosVendedor(vendedor);       
            }
        }
        if(opcao==1)
            fclose(arqTxt);
        liberaVendedor(vendedor);
    }else 
        printf("\nNenhum valor encontrado nesse mes!");
    fclose(fv);
    fclose(fnf);
}

void relatorioSete(){
    FILE *fv,*fnf,*arqTxt;

    if(!abrirArquivo(ARQ_NOTA_FISCAL,&fnf)){
    printf("\nImpossivel abrir o arquivo %s",ARQ_NOTA_FISCAL);
    return;       
    }
    if(!ftell(fnf) / tamStructNotaFiscal()){
        printf("\nNenhuma nota fiscal encontrada");
        fclose(fnf);
        return;
    }

    if(!abrirArquivo(ARQ_VENDEDOR,&fv)){
        printf("\nImpossivel abrir o arquivo %s",ARQ_VENDEDOR);
        return;       
    }

    int opcao,validar,tipoDeBusca;
    float maiorValor ;
    char nomeArquivo[50],data1[11],data2[11],aux[11];
    tipoDeBusca = perguntaRelatorioDatas();
    do{
        printf("\nForneça a data inicial");
        recebeData(data1);
        validar = validaData(data1);
        if(!validar)
            printf("\nData Inválida!");
    } while (!validar);
    if(tipoDeBusca == 2)
        do{
            printf("\nForneça a data final");
            recebeData(data2);
            validar = validaData(data2);
            if(!validar)
                printf("\nData Inválida!");

            if(dataMaior(data1,data2)){
                strcpy(aux,data1);
                strcpy(data1,data2);
                strcpy(data2,aux);
            }

        } while (!validar);
    else
        strcpy(data2,data1);
    
    maiorValor = calculaMaiorValorVenda(fv,fnf,data1,data2,0);
    if(maiorValor>0){
        opcao = perguntaRelatorio();
        if(opcao==1){
            recebeNomeTXT(nomeArquivo);
            if(!abrirArquivo(nomeArquivo,&arqTxt)){
                printf("\nImpossivel gerar o arquivo txt!");
                return;
            }   
        }
        if(opcao==1){
            fprintf(arqTxt,"\n|Maior valor de Venda = R$ %.2f|",maiorValor);
            fprintf(arqTxt,"\n--------------------------------------------");
            fprintf(arqTxt,"\nVendedores com esse valor de venda:");
        }else{
            printf("\nMaior valor de Venda = R$ %.2f",maiorValor);
            printf("\n--------------------------------------------");
            printf("\nVendedores com esse valor de venda:");
        }
        TVendedor vendedor = novoVendedor();
        fseek(fv,0,SEEK_SET);
        while (fread(vendedor,tamStructVendedor(),1,fv)){
            if(calculaValorVendaVendedor(fv,fnf,data1,data2,getIdVendedor(vendedor),0)==maiorValor){
                if(opcao==1)
                    printaDadosVendedorTexto(vendedor,arqTxt);
                else
                    printaDadosVendedor(vendedor);       
            }
        }
        if(opcao==1)
            fclose(arqTxt);
        liberaVendedor(vendedor);
    }else 
        printf("\nNenhum valor encontrado nesse periodo!");
    fclose(fv);
    fclose(fnf);
}

void relatorioOito(){
//8-Histórico de valor de venda de um determinado produto

    FILE *fp,*fh,*arqTxt;
    if(!abrirArquivo(ARQ_PRODUTO,&fp)){
    printf("\nImpossivel abrir o arquivo %s",ARQ_PRODUTO);
    return;
    }
    if(!registroValidosProduto(fp)){
        printf("\nNenhum produto encontrado");
        return;
    }
    if(!abrirArquivo(ARQ_HISTORICO,&fh)){
    printf("\nImpossivel abrir o arquivo %s",ARQ_HISTORICO);
    fclose(fp);
    return;
    }
    if(!ftell(fh) / tamStructHistorico()){
        printf("\nNenhum historico foi gerado");
        fclose(fh);
        fclose(fp);
        return;
    }

    char nomeArquivo[50],nomeProduto[100],data[11];
    unsigned long idProduto;
    int s_n,opcao;
    THistoricoPreco historico;
    TProduto produto = novoProduto();
    do{
        printf("\nDados do produto:");
        idProduto = recebeId();
        if(buscaIdProduto(idProduto,fp)!=-1){
            atribuirDadosProduto(produto,idProduto-1,fp);
            getNomeProduto(produto,nomeProduto);
            opcao = perguntaRelatorio();
            if(opcao==1){
                recebeNomeTXT(nomeArquivo);
                if(!abrirArquivo(nomeArquivo,&arqTxt)){
                    printf("\nImpossivel gerar o arquivo txt!");
                    return;
                }   
            }
            fseek(fh,0,SEEK_SET);
            historico = novoHistorico();
            while (fread(historico,tamStructHistorico(),1,fh)){
                if(getIdProdutoHistoricoPreco(historico)==idProduto){
                    if(opcao==1){
                        fprintf(arqTxt,"\n|==========================================|");
                        fprintf(arqTxt,"\n|ID produto: %lu| Nome: %s",idProduto,nomeProduto);
                        getDataAlteracao(historico,data);
                        fprintf(arqTxt,"\n|Data de alteração: %s| Valor: %.2f",data,getValorHistoricoPreco(historico));
                        fprintf(arqTxt,"\n|==========================================|");
                    }else{
                        printf("\n|==========================================|");
                        printf("\n|ID produto: %lu| Nome: %s",idProduto,nomeProduto);
                        getDataAlteracao(historico,data);
                        printf("\n|Data de alteração: %s| Valor: %.2f",data,getValorHistoricoPreco(historico));
                        printf("\n|==========================================|");
                    }
                }
                
            
            }
            if(opcao == 1)
                fclose(arqTxt);
            liberaHistorico(historico);
            

        }else
            printf("\nProduto não encontrado!");  
        printf("\nDeseja consultar mais algum produto?\n1-Sim | 2-Não: ");
        scanf("%d",&s_n);  
    } while (s_n==1);
    fclose(fp);
    fclose(fh);
    liberaProduto(produto);    


}

void printaNotaCompraTela(TNotaCompra nota,FILE *arqProduto,FILE *arqForn,FILE *arqItem){
    char aux[100];
    TFornecedor forn = novoFornecedor();
    unsigned long idForn = getIdFornecedorNotaCompra(nota),idNota = getIdNotaCompra(nota);
    atribuirDadosFornecedor(forn,idForn-1,arqForn);


    getNomeFornecedor(forn,aux);
    printf("\n|------------%s------------|",aux);
    printf("\n|ID Fornecedor|%lu||",idForn);
    printf("\n|ID Nota Compra|%lu|",idNota);
    getDataCompra(nota,aux);
    printf("\n|Data:%s",aux);
    printf("\n|=============Itens da nota====================");
    printaItensNotaCompraTela(idNota,arqProduto,arqItem);
    printf("\nValor total:|R$%.2f|",getValorTotalNotaCompra(nota));
    printf("\n|---------------------------------------------");

    liberaFornecedor(forn);
}


void printaItensNotaCompraTela(unsigned long idNota,FILE *arqProduto, FILE *arqItem){
    char aux[100];
    TItemNotaCompra item = novoItemNotaCompra();
    TProduto produto = novoProduto();
    unsigned long idProd=0;

    fseek(arqItem,0,SEEK_SET);
    while(fread(item,tamStructItemNotaCompra(),1,arqItem)==1)
        if(getIdNotaCompraItem(item)==idNota){
            idProd = getIdProdutoItem(item);
            atribuirDadosProduto(produto,idProd-1,arqProduto);
            getNomeProduto(produto,aux);
            printf("\nID: %lu|Nome do produto:%s",idProd,aux);
            printf("\n|qtde:%u",getQuantidadeItemNotaCompra(item));
            printf("\n|valor Unitário:%.2f",getValorUnitarioItemNotaCompra(item));
            printf("\n|===============================================|");
        }
    liberaItemNotaCompra(item);
    liberaProduto(produto);

}

void printaNotaCompraTexto(TNotaCompra nota,FILE *arqTxt,FILE *arqProduto,FILE *arqForn,FILE *arqItem){
    char aux[100];
    TFornecedor forn = novoFornecedor();
    unsigned long idForn = getIdFornecedorNotaCompra(nota),idNota = getIdNotaCompra(nota);
    atribuirDadosFornecedor(forn,idForn-1,arqForn);


    getNomeFornecedor(forn,aux);
    fprintf(arqTxt,"\n|------------%s------------|",aux);
    fprintf(arqTxt,"\n|ID Fornecedor|%lu||",idForn);
    fprintf(arqTxt,"\n|ID Nota Compra|%lu|",idNota);
    getDataCompra(nota,aux);
    fprintf(arqTxt,"\n|Data:%s",aux);
    fprintf(arqTxt,"\n|=============Itens da nota====================");
    printaItensNotaCompraTexto(idNota,arqTxt,arqProduto,arqItem);
    fprintf(arqTxt,"\nValor total:|R$%.2f|",getValorTotalNotaCompra(nota));
    fprintf(arqTxt,"\n|---------------------------------------------");

    liberaFornecedor(forn);
}

void printaItensNotaCompraTexto(unsigned long idNota,FILE *arqTxt,FILE *arqProduto, FILE *arqItem){
    char aux[100];
    TItemNotaCompra item = novoItemNotaCompra();
    TProduto produto = novoProduto();
    unsigned long idProd=0;

    fseek(arqItem,0,SEEK_SET);
    while(fread(item,tamStructItemNotaCompra(),1,arqItem)==1)
        if(getIdNotaCompraItem(item)==idNota){
            idProd = getIdProdutoItem(item);
            atribuirDadosProduto(produto,idProd-1,arqProduto);
            getNomeProduto(produto,aux);
            fprintf(arqTxt,"\nID: %lu|Nome do produto:%s",idProd,aux);
            fprintf(arqTxt,"\n|qtde:%u",getQuantidadeItemNotaCompra(item));
            fprintf(arqTxt,"\n|valor Unitário:%.2f",getValorUnitarioItemNotaCompra(item));
            fprintf(arqTxt,"\n|===============================================|");
        }
    liberaItemNotaCompra(item);
    liberaProduto(produto);
}





void printaNotaFiscalTexto(TNotaFiscal nota,FILE *arqTxt,FILE *arqProduto,FILE *arqVend,FILE *arqItem,FILE *arqCliente){


    char aux[100];
    TVendedor vend = novoVendedor();
    TCliente cli = novoCliente();
    unsigned long idVend = getIdVendedorNotaFiscal(nota),idNota = getIdNotaFiscal(nota),idCli = getIdClienteNotaFiscal(nota);
    
    atribuirDadosVendedor(vend,idVend-1,arqVend);
    atribuirDadosCliente(cli,idCli-1,arqCliente);
    fprintf(arqTxt,"\n|------------LOUCO DAS PEDRAS------------|");
    fprintf(arqTxt,"\n|ID Nota Compra|%lu|",idNota);
    fprintf(arqTxt,"\n|-------------DADOS VENDEDOR-------------|");
    getNomeVendedor(vend,aux);
    fprintf(arqTxt,"\n|ID Vendedor|%lu| Nome: %s|",idVend,aux);
    fprintf(arqTxt,"\n|-------------DADOS CLIENTE--------------|");
    getNomeCliente(cli,aux);
    fprintf(arqTxt,"\n|ID Cliente|%lu| Nome: %s|",idCli,aux);
    getDataCompraNotaFiscal(nota,aux);
    fprintf(arqTxt,"\n|Data:%s",aux);
    fprintf(arqTxt,"\n|=============Itens da nota====================");
    printaItensNotaFiscalTexto(arqTxt,idNota,arqProduto,arqItem);
    fprintf(arqTxt,"\nValor total:|R$%.2f|",getValorTotalNotaFiscal(nota));
    fprintf(arqTxt,"\n|---------------------------------------------");
    liberaVendedor(vend);
    liberaCliente(cli);

}

void printaItensNotaFiscalTexto(FILE *arqTxt,unsigned long idNota,FILE *arqProduto, FILE *arqItem){

    char aux[100];
    TItemNotaFiscal item = novoItemNotaFiscal();
    TProduto produto = novoProduto();
    unsigned long idProd=0;
    fseek(arqItem,0,SEEK_SET);
    while(fread(item,tamStructItemNotaFiscal(),1,arqItem)==1)
    if(getIdNotaFiscalItemNotaFiscal(item)==idNota){
        idProd = getIdProdutoItemNotaFiscal(item);
        atribuirDadosProduto(produto,idProd-1,arqProduto);
        getNomeProduto(produto,aux);
        fprintf(arqTxt,"\nID: %lu|Nome do produto:%s",idProd,aux);
        fprintf(arqTxt,"\n|qtde:%u",getQuantidadeItemNotaFiscal(item));
        fprintf(arqTxt,"\n|valor Unitário:%.2f",getValorVendaItemNotaFiscal(item));
        fprintf(arqTxt,"\n|===============================================|");
    }

}

void printaNotaFiscalTela(TNotaFiscal nota,FILE *arqProduto,FILE *arqVend,FILE *arqItem,FILE *arqCliente){
    char aux[100];
    TVendedor vend = novoVendedor();
    TCliente cli = novoCliente();
    unsigned long idVend = getIdVendedorNotaFiscal(nota),idNota = getIdNotaFiscal(nota),idCli = getIdClienteNotaFiscal(nota);
    
    atribuirDadosVendedor(vend,idVend-1,arqVend);
    atribuirDadosCliente(cli,idCli-1,arqCliente);
    printf("\n|------------LOUCO DAS PEDRAS------------|");
    printf("\n|ID Nota Compra|%lu|",idNota);
    printf("\n|-------------DADOS VENDEDOR-------------|");
    getNomeVendedor(vend,aux);
    printf("\n|ID Vendedor|%lu| Nome: %s|",idVend,aux);
    printf("\n|-------------DADOS CLIENTE--------------|");
    getNomeCliente(cli,aux);
    printf("\n|ID Cliente|%lu| Nome: %s|",idCli,aux);
    getDataCompraNotaFiscal(nota,aux);
    printf("\n|Data:%s",aux);
    printf("\n|=============Itens da nota====================");
    printaItensNotaFiscalTela(idNota,arqProduto,arqItem);
    printf("\nValor total:|R$%.2f|",getValorTotalNotaFiscal(nota));
    printf("\n|---------------------------------------------");

    liberaVendedor(vend);
    liberaCliente(cli);
}


void printaItensNotaFiscalTela(unsigned long idNota,FILE *arqProduto, FILE *arqItem){

    char aux[100];
    TItemNotaFiscal item = novoItemNotaFiscal();
    TProduto produto = novoProduto();
    unsigned long idProd=0;
    fseek(arqItem,0,SEEK_SET);
    while(fread(item,tamStructItemNotaFiscal(),1,arqItem)==1)
    if(getIdNotaFiscalItemNotaFiscal(item)==idNota){
        idProd = getIdProdutoItemNotaFiscal(item);
        atribuirDadosProduto(produto,idProd-1,arqProduto);
        getNomeProduto(produto,aux);
        printf("\nID: %lu|Nome do produto:%s",idProd,aux);
        printf("\n|qtde:%u",getQuantidadeItemNotaFiscal(item));
        printf("\n|valor Unitário:%.2f",getValorVendaItemNotaFiscal(item));
        printf("\n|===============================================|");
    }

}

int verificaNotaFiscal(TNotaFiscal nota,char *data1,char *data2,int tipo,unsigned long idTipo){

    unsigned long idBusca;
    char aux[11];
    if(tipo!=TIPO_VENDEDOR)
        idBusca = getIdClienteNotaFiscal(nota);
    else
        idBusca = getIdVendedorNotaFiscal(nota);
    
    if(idBusca!=idTipo)
        return 0;

    getDataCompraNotaFiscal(nota,aux);
    if(!strcmp(data1,aux) || !strcmp(data2,aux))
        return 1;
    
    if(data2[0]=='\0')
        return 0;
    
    if(dataMaior(aux,data1) && dataMaior(data2,aux))
        return 1;
    
    return 0;

}

int verificaMesVendedorNotaFiscal(TNotaFiscal nota,int mes,int idVendedor){

    unsigned long idBusca = getIdVendedorNotaFiscal(nota);
    char aux[11];
    int mesNota;

    if(idBusca!=idVendedor)
        return 0;

    getDataCompraNotaFiscal(nota,aux);
    mesNota=(aux[3]-48)*10+(aux[4]-48);
    if(mesNota == mes)
        return 1;
    return 0;
}

float calculaMaiorValorVenda(FILE *arqVendedor,FILE *arqNotaFiscal,char *data1,char *data2,int mes){
float maiorValor=0,valorVendedor=0;
TVendedor vendedor = novoVendedor();
    fseek(arqVendedor,0,SEEK_SET);
    while (fread(vendedor,tamStructVendedor(),1,arqVendedor)){
        valorVendedor=calculaValorVendaVendedor(arqVendedor,arqNotaFiscal,data1,data2,getIdVendedor(vendedor),mes);
        if(valorVendedor>maiorValor)
            maiorValor = valorVendedor;
    }
    
    liberaVendedor(vendedor);
    return maiorValor;
}

float calculaValorVendaVendedor(FILE *arqVendedor,FILE *arqNotaFiscal,char *data1,char *data2,unsigned long idVendedor,int mes){

    TNotaFiscal nota = novoNotaFiscal();
    float valorVendedor=0;
    fseek(arqNotaFiscal,0,SEEK_SET);
    while (fread(nota,tamStructNotaFiscal(),1,arqNotaFiscal)){
        if(getIdVendedorNotaFiscal(nota)==idVendedor){

            if(strcmp(data1,"")&& strcmp(data2,"")){
                if(verificaMesVendedorNotaFiscal(nota,mes,idVendedor))
                    valorVendedor+=getValorTotalNotaFiscal(nota);    
            }else{
                if(verificaNotaFiscal(nota,data1,data2,TIPO_VENDEDOR,idVendedor))
                    valorVendedor+=getValorTotalNotaFiscal(nota);
            }
        }
    }
    liberaNotaFiscal(nota);
    return valorVendedor;
}

void printaDadosVendedorTexto(TVendedor v, FILE *arqTxt){
    char aux[100];
    fprintf(arqTxt,"\n|-----------------------------------------------|");
    fprintf(arqTxt,"\n|ID:%lu",getIdVendedor(v));
    getNomeVendedor(v,aux);
    fprintf(arqTxt,"\n|NOME:%s",aux);
    getCpfVendedor(v,aux);
    fprintf(arqTxt,"\n|CPF:%s",aux);
    getEmailVendedor(v,aux);
    fprintf(arqTxt,"\n|EMAIL:%s",aux);
    getTelefoneVendedor(v,aux);
    fprintf(arqTxt,"\n|TELEFONE:%s",aux);
    fprintf(arqTxt,"\n|-----------------------------------------------|");

}