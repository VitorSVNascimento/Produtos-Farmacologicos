//Aluno:Vitor Samuel de Viveiros Nascimento


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "cliente.h"
#include "produtos.h"
#include "vendedor.h"
#include "fornecedor.h"
#include "validacao.h"
#include "vendas.h"
#include "compra.h"
#include "relatorios.h"
#include "funcoesgerais.h"


int main()
{
int finalizar;

setlocale(LC_ALL,"portuguese");




    do{
    printf("--------------------------------------------------------------------------------------------------------------------");
    printf("\nO que deseja fazer?");
    printf("\n1-Menu de Cliente|\n2-Menu de Produto|\n3-Menu de Vendedor|\n4-Menu de Fornecedor|\n5-Fazer Venda|\n6-Fazer Compra|\n7-Modificar Preços|\n8-Relatórios|\n9-Finalizar|");
    scanf("%d",&finalizar);

    switch (finalizar){

        case 1:

mCliente();


break;
 case 2:

mProduto();
   break;

 case 3:
 mVendedor();
            break;
 case 4:

 mFornecedor();
    break;
 case 5:
  mVendas();

    break;
 case 6:

           mCompra();
    break;
 case 7:

         mAlteraPreco();
    break;
 case 8:

            mRelatorios();
    break;
 case 9:

    break;
    }
    }while(finalizar!=9);



    return 0;
}
