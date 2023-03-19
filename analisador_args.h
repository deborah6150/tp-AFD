////
////  analisador_args.h
////  tp-ftc
////
////  Created by Deborah Caroline on 19/03/23.
////
//
//#ifndef analisador_args_h
//#define analisador_args_h
//
//#include <stdio.h>
//
//#endif /* analisador_args_h */
#ifndef ANALISADOR_ARGS_H
#define ANALISADOR_ARGS_H

/**
 *@name Analisador de argumentos. Este módulo é responsável por identicar os argumentos passados pela linha de comando
 * e verficar se são válidos. No caso de serem válidos os quebra em partes significativas .
*/

typedef enum {
    DOT,
    COMPLEMENTO,
    INTERCECAO,
    UNIAO,
    MINIMIZACAO,
    RECONHECER,
    NENHUMA
} Funcionalidade;

struct analise {
    Funcionalidade funcionalidade; // Funcionalidade a ser executada
    char entrada1[50]; // Arquivo de entrada 1
    char entrada2[50]; // Arquivo de entrada 2. Esta variável é usada somente se a
                       // funcionalidade em casua for União, Intersessão e Reconhecer.
    char saida[50]; // Arquivo de saída, com os resultados da execução
};

/***
 * @param argc - Numero de argumentos passados pela linha de comando.
 * @param argv - Lista de argumentos passados pela linha de comando
 * @param analise - Referencia de uma variável onde serào armazenados os resultados da análise dos argumentos
*/
int analisar_argumentos(int argc, char *argv[], struct analise* analise);

#endif // ANALISADOR_ARGS_H
