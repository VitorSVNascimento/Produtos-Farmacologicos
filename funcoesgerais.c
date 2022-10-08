#include "funcoesGerais.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

int abrirArquivo(char *nomeArq,FILE **arq){

    *arq=fopen(nomeArq,"rb+");
    if(*arq==NULL)
        *arq=fopen(nomeArq,"wb+");
    if(*arq==NULL)
        return 0;
    return 1;
}

void retiraN(char *str){

    int tam = strlen(str);
    if(str[tam-1]=='\n')
        str[tam-1]='\0';
    return ;
}

void padronizaString(char *str){

    int i;
    for(i=0;i<strlen(str);i++){

        switch (str[i]){

            case 'á':
            case 'à':
            case 'â':
            case 'ã':
            case 'ä':
            case 'Ä':
            case 'Å':
            case 'Á':
            case 'Â':
            case 'À':
            case 'Ã':

                str[i]='A';
        break;
            case 'É':
            case 'Ê':
            case 'Ë':
            case 'È':
            case 'é':
            case 'ê':
            case 'ë':
            case 'è':
                str[i]='E';
        break;
            case 'Í':
            case 'Î':
            case 'Ï':
            case 'Ì':
            case 'í':
            case 'î':
            case 'ï':
            case 'ì':
                str[i]='I';
        break;


            case 'ô':
            case 'ó':
            case 'ò':
            case 'õ':
            case 'ö':
            case 'Ó':
            case 'Ò':
            case 'Õ':
            case 'Ö':
                str[i]='O';
        break;

            case 'Ü':
            case 'Ú':
            case 'Û':
            case 'ü':
            case 'ú':
            case 'û':
            case 'ù':
                str[i]='U';
        break;
            case 'Ç':
            case 'ç':
                str[i]='C';
        break;
            case 'ñ':
            case 'Ñ':
                str[i]='N';
        break;
            default:
        break;
        }

    }
    for(i=0;i<strlen(str);i++)
        if(str[i]>'Z')
            str[i]=str[i]-32;
    return;
}

void dataSistema(char *str){

 time_t t = time(NULL);
  struct tm tm = *localtime(&t);
//tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

str[0]=tm.tm_mday/10+'0';
str[1]=tm.tm_mday%10+'0';
str[2]='/';
str[3]=(tm.tm_mon+1)/10+'0';
str[4]=(tm.tm_mon+1)%10+'0';
str[5]='/';
str[6]=(tm.tm_year+1900)/1000+'0';
str[7]=(tm.tm_year+1900)%1000/100+'0';
str[8]=(tm.tm_year+1900)%1000%100/10+'0';
str[9]=(tm.tm_year+1900)%1000%100%10+'0';
str[10]='\0';

}

int dataMaior(char *data1, char *data2){
    char dataAux[11];
    int dat1[3],dat2[3],i;
    char *tokens;
    strcpy(dataAux,data1);
    tokens = strtok(dataAux,"/");
    i=0;
    while(tokens!=NULL){
        dat1[i]=atoi(tokens);
        i++;
        tokens = strtok(NULL,"/");
    }
    strcpy(dataAux,data2);
    tokens = strtok(dataAux,"/");
    i=0;
    while(tokens!=NULL){
        dat2[i]=atoi(tokens);
        i++;
        tokens = strtok(NULL,"/");
    }

    if(dat1[2]>dat2[2] || (dat1[2] == dat2[2] && dat1[1]>dat2[1]) || (dat1[2] == dat2[2] && dat1[1] == dat2[1] && dat1[0]>dat2[0]))
        return 1;
    return 0;
}
