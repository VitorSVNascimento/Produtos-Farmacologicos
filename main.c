#include <stdio.h>
#include <locale.h>
#include "menuCliente.h"
#include "menuVendedor.h"
#include "menuFornecedor.h"
#include "menuProduto.h"
#include "menuCompra.h"
#include "menuVenda.h"
#include "menuAlteracaoPreco.h"
#include "relatorios.h"



int menuPrincipal(){
    int opcao;

    setlocale(LC_ALL,"portuguese");

    do{
        printf("--------------------------------------------------------------------------------------------------------------------");
        printf("\nO que deseja fazer?");
        printf("\n1-Menu de Cliente|\n2-Menu de Vendedor|\n3-Menu de Fornecedor|\n4-Menu de Produto|\n5-Fazer Compra|\n6-Fazer Venda|\n7-Modificar Preços|\n8-Relatórios|\n9-Finalizar|");
        scanf("%d",&opcao);

        switch (opcao){

            case 1:
                mCliente();
            break;
            case 2:
                mVendedor();
            break;
            case 3:
                mFornecedor();
            break;
            case 4:
                mProduto();
            break;
            case 5:
                mCompra();
            break;
            case 6:
                mVenda();
            break;
            case 7:
                mAlterarPreco();
            break;
            case 8:
                mRelatorio();
            break;

        }
    }while(opcao!=9);

    return 0;
}

int main(){
    return menuPrincipal();
}
