#ifndef TIPOS_H
#define TIPOS_H

/**
 * Neste arquivo estão os tipos principais do programa, como transições, AFD, Grupos
*/


/**
 * Tipos necessários para armazenar um AFD na memória
*/
struct transicao {
    char* estado_partida;
    char simbolo;
    char* estado_destino;
};

struct afd {
    // Alfabeto
    int tamanho_do_alfabeto;
    char* simbolos;

    // Número de estados
    int numero_de_estados;
    char** estados;

    // Transições de estado
    int numero_de_transicoes;
    struct transicao* transicoes;

    // Estado inicial do AFD
    char *estado_inicial;

    // Conjunto de estados finais
    int numero_de_estados_finais;
    char** estados_finais;
};


/**
 * Tipos usados pela função de minimização de AFD
*/
struct grupo {
    int numero_maximo_de_estados;
    int numero_de_estados;
    char** estados;
};

struct particao {
    int numero_de_grupos;
    struct grupo* grupos;
};

struct analise_estado {
    int indice_novo_grupo;
    int quantidade_grupos_resultantes;
    int* grupos_resultantes_dos_simbolos;
};


#endif // TIPOS_H
