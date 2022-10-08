#ifndef ENTRADAS_H_INCLUDED
#define ENTRADAS_H_INCLUDED

/*
    EFETUA A LEITURA DE UMA STRING ALTERRANDO O VALOR DA VARIAVEL
    PARAMETROS:str(string á ser lida), tamStr (tamanho maximo disponivel para str), nomeCampo (nome do campo a ser exibido na mensagem),
    apenasNumeros( valor que representa a exibiçao da mensagem "UTILIZE APENAS NUMEROS" na leitura do campo (0 = falso, 1 = verdadeiro))
*/
int recebeString(char *str,int tamStr,char *nomeCampo,int apenasNumeros);
unsigned long recebeId();
unsigned int recebeQuantidade();
float recebePreco();
void menuInicial(char *nomeStruct);
void recebeNome(char *);
void recebeCpf(char *);
void recebeCnpj(char *);
void recebeEmail(char*);
void recebeTelefone(char*);
void recebePrefixo(char*);
void recebeData(char *);
void recebeNomeTXT(char *nomeArquivo);
int perguntaAlteracao(char *nomeCampo);
int perguntaBusca(char *nomeCampo);
int confirmaExclusao(char *nomeStruct);
int perguntaExclusao();
int perguntaRelatorioDatas();
int perguntaRelatorio();
#endif // ENTRADAS_H_INCLUDED
