#include "analisador_args.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MENOR_NUMERO_DE_ARGUMENTOS 5

Funcionalidade identificar_funcionalidade(char* fun_str);

int analisar_argumentos(int argc, char *argv[], struct analise* analise) {

    if(argc == 1) {
        printf("\n%% A execução do programa exige passagem de argumentos obrigatorios, como mostrado abaixo.\n\n");
        printf("$ afdtool nome-funcionalidade arquivo-entrada.txt [arquivo-entrada2.txt] --output arquivo-saida.(txt | dot)\n");
        printf("    * O arquivo-entrada2.txt é um argumento opcional, e é necessário somente se a funcionalidade for União ou Interseção ou Reconehecer.\n");
        printf("    * No arquivo de saída, a extensão varia de .dot ou .txt dependendo da funcionalidade.\n");
        perror("\n");
        return 0;
    }

    if( argc < MENOR_NUMERO_DE_ARGUMENTOS ) {
        perror("ERRO NOS ARGUMENTOS. O número de argumentos passados é inferior ao número mínimo de argumentos necessários.\n");
        return 0;
    }

    int indice_do_argumento_atual = 1;
    Funcionalidade funcionalidade = identificar_funcionalidade(argv[indice_do_argumento_atual++]);

    if(funcionalidade == NENHUMA) {
        perror("ERRO DE FUNCIONALIDADE. A funcionalidade passada é inválida, tente uma outra.\n");
        return 0;
    }

    analise->funcionalidade = funcionalidade;
    strcpy(analise->entrada1, argv[indice_do_argumento_atual++]);

    if(funcionalidade == UNIAO || funcionalidade == INTERCECAO || funcionalidade == RECONHECER) {
        if(argc < MENOR_NUMERO_DE_ARGUMENTOS + 1) {
            perror("ERRO NOS ARGUMENTOS. O número de argumentos passados é inferior ao número de argumentos necessários.\n");
            return 0;
        }

        strcpy(analise->entrada2, argv[indice_do_argumento_atual++]);
    }

    if( strcmp(argv[indice_do_argumento_atual++], "--output") && strcmp(argv[indice_do_argumento_atual - 1], "-o") ) {
        printf("%s\n", argv[indice_do_argumento_atual - 1]);
        perror("ERRO DE SAIDA. Arquivo de saída não foi especificado.\n");
        return 0;
    }

    strcpy(analise->saida, argv[indice_do_argumento_atual]);
    return 1;
}

Funcionalidade identificar_funcionalidade(char* fun_str) {
    if(!strcmp(fun_str, "--dot") || !strcmp(fun_str, "-d"))
        return DOT;
    
    if(!strcmp(fun_str, "--complemento") || !strcmp(fun_str, "-c"))
        return COMPLEMENTO;

    if(!strcmp(fun_str, "--intersecao") || !strcmp(fun_str, "-i"))
        return INTERCECAO;

    if(!strcmp(fun_str, "--uniao") || !strcmp(fun_str, "-u"))
        return UNIAO;

    if(!strcmp(fun_str, "--minimizacao") || !strcmp(fun_str, "-m"))
        return MINIMIZACAO;

    if(!strcmp(fun_str, "--reconhecer") || !strcmp(fun_str, "-r"))
        return RECONHECER;

    printf("%s\n", fun_str);
    return NENHUMA;
}
