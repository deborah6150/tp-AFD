#include "manipulador_afd.h"
#include <stdlib.h>
#include <stdio.h>
// #include <malloc.h>
#include <malloc/malloc.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

/**
 * Função que lê um AFD do arquivo e armazena na memória. É na estrutura AFD onde são armazenados todos
 * os dados sobre o AFD,
*/
void ler_afd(FILE *arquivo_afd, struct afd *afd)
{
    char linha[100];

    fgets(linha, 100, arquivo_afd); // Lê o número de estados do AFD
    afd->numero_de_estados = atoi(linha);
    afd->estados = calloc(afd->numero_de_estados, sizeof(char *));
    for (int i = 0; i < afd->numero_de_estados; ++i)
    {
        fgets(linha, 100, arquivo_afd); // Lê o estado Ei
        afd->estados[i] = calloc(strlen(linha) + 1, sizeof(char));
        char *linha_sem_nova_linha = strtok(linha, "\n");
        strcpy(afd->estados[i], linha_sem_nova_linha);
    }

    fgets(linha, 100, arquivo_afd); // Lê o número de simbolos no alfabeto
    afd->tamanho_do_alfabeto = atoi(linha);
    afd->simbolos = calloc(afd->tamanho_do_alfabeto, sizeof(char));
    for (int i = 0; i < afd->tamanho_do_alfabeto; ++i)
    {
        fgets(linha, 100, arquivo_afd); // Lê o estado Ei
        afd->simbolos[i] = linha[0];
    }

    fgets(linha, 100, arquivo_afd); // Lê o número de transições do AFD
    afd->numero_de_transicoes = atoi(linha);
    afd->transicoes = calloc(afd->numero_de_transicoes, sizeof(struct transicao));
    for (int i = 0; i < afd->numero_de_transicoes; ++i)
    {
        fgets(linha, 100, arquivo_afd); // Lê o estado Ei
        char *part = strtok(linha, " ");
        afd->transicoes[i].estado_partida = calloc(strlen(part) + 1, sizeof(char));
        strcpy(afd->transicoes[i].estado_partida, part);
        part = strtok(NULL, " ");
        afd->transicoes[i].simbolo = part[0];
        part = strtok(NULL, "\n");
        afd->transicoes[i].estado_destino = calloc(strlen(part) + 1, sizeof(char));
        strcpy(afd->transicoes[i].estado_destino, part);
    }

    fgets(linha, 100, arquivo_afd); // Lê o estado inicial
    char *linha_sem_nova_linha = strtok(linha, "\n");
    afd->estado_inicial = calloc(sizeof(linha) + 1, sizeof(char));
    strcpy(afd->estado_inicial, linha_sem_nova_linha);

    fgets(linha, 100, arquivo_afd); // Lê os estados finais
    afd->numero_de_estados_finais = atoi(linha);
    afd->estados_finais = calloc(afd->numero_de_estados_finais, sizeof(char *));
    for (int i = 0; i < afd->numero_de_estados_finais; ++i)
    {
        fgets(linha, 100, arquivo_afd); // Lê o estado Ei
        afd->estados_finais[i] = calloc(strlen(linha) + 1, sizeof(char));
        char *linha_sem_nova_linha = strtok(linha, "\n");
        strcpy(afd->estados_finais[i], linha_sem_nova_linha);
    }
}


/**
 * Esta função escreve um AFD na saída padrão do programa.
 * Não tem utlidade alguma dentro deste programa, mas foi necessária para ver se tudo estava a funcionar perfeitamente
 * e bom, ajudou.
*/
void imprimir_afd(struct afd *afd)
{

    printf("\nEstados:\n    { ");
    for (int i = 0; i < afd->numero_de_estados - 1; ++i)
    {
        printf("%s, ", afd->estados[i]);
    }
    printf("%s }", afd->estados[afd->numero_de_estados - 1]);

    printf("\n\nAlfabeto:\n    { ");
    for (int i = 0; i < afd->numero_de_estados - 1; ++i)
    {
        printf("%c, ", afd->simbolos[i]);
    }
    printf("%c }", afd->simbolos[afd->numero_de_estados - 1]);

    printf("\n\nTransições\n{\n");
    for (int i = 0; i < afd->numero_de_transicoes - 1; ++i)
    {
        printf("    ( %s, %c, %s )\n", afd->transicoes[i].estado_partida, afd->transicoes[i].simbolo, afd->transicoes[i].estado_destino);
    }
    printf("    ( %s, %c, %s )\n}", afd->transicoes[afd->numero_de_transicoes - 1].estado_partida, afd->transicoes[afd->numero_de_transicoes - 1].simbolo, afd->transicoes[afd->numero_de_transicoes - 1].estado_destino);

    printf("\n\nEstado inicial: %s", afd->estado_inicial);

    printf("\n\nEstados finais:\n    {");
    for (int i = 0; i < afd->numero_de_estados_finais - 1; ++i)
    {
        printf(" %s, ", afd->estados_finais[i]);
    }
    printf(" %s }\n\n", afd->estados_finais[afd->numero_de_estados_finais - 1]);
}

/**
 * Esta função é auxiliar a funcionalidade de visualização, e transforma um AFD
 * na estrutura AFD em um AFD em texto na linguagem DOT. O que facilita a visulaização do grafo do afd.
*/
void tranformar_afd_para_dot(struct afd *afd, FILE *arquivo_dot)
{

    // Inicializa o grafo
    fprintf(arquivo_dot, "strict digraph {\n");

    // Define a direção do grafo
    fprintf(arquivo_dot, "    rankdir = LR;\n\n");
    fprintf(arquivo_dot, "    inic [style=invis];\n");

    // Estiliza os vertices (estados)
    for (int i = 0; i < afd->numero_de_estados; ++i)
    {
        if (pertence_ao_conjunto(afd->estados[i], afd->estados_finais, afd->numero_de_estados_finais))
        { // Se o estado atual não é um estado final
            fprintf(arquivo_dot, "    \"%s\" [label=<<I>%s</I>>, peripheries=2, fill=gray, style=filled]\n", afd->estados[i], afd->estados[i]);
        }
        else
        {
            fprintf(arquivo_dot, "    \"%s\" [label=<<I>%s</I>>, fill=gray, style=filled]\n", afd->estados[i], afd->estados[i]);
        }
    }

    fprintf(arquivo_dot, "\n");

    // Desenha as atransições
    for (int i = 0; i < afd->numero_de_transicoes; ++i)
    {
        char simbolos_transicao[8];
        int indice_simbolo = 0;
        struct transicao *transicao_atual = &afd->transicoes[i];

        while (i < afd->numero_de_transicoes && tem_mesma_origem_destino(transicao_atual, &afd->transicoes[i]))
        {
            simbolos_transicao[indice_simbolo++] = afd->transicoes[i].simbolo;

            if (i < afd->numero_de_transicoes - 1 && tem_mesma_origem_destino(transicao_atual, &afd->transicoes[i + 1]))
                simbolos_transicao[indice_simbolo++] = ',';
            ++i;
        }
        --i;

        simbolos_transicao[indice_simbolo] = '\0';

        if (!strcmp(afd->estado_inicial, transicao_atual->estado_partida))
        {
            fprintf(arquivo_dot, "    \"%s\" -> \"%s\"\n", "inic",
                    transicao_atual->estado_partida);
        }

        fprintf(arquivo_dot, "    \"%s\" -> \"%s\" [label=<<I>%s</I>>]\n", transicao_atual->estado_partida,
                transicao_atual->estado_destino, simbolos_transicao);
    }

    fprintf(arquivo_dot, "}");
}

/**
 * Esta função é auxiliar a funcionalidade complemento e determina o complemento de um AFD.
 * O afd complementar ao AFD atual é armazenado no arquivo arquivo_complemento.
*/
void determinar_complemento_afd(struct afd *afd, FILE *arquivo_complemento)
{

    fprintf(arquivo_complemento, "%d\n", afd->numero_de_estados);
    for (int i = 0; i < afd->numero_de_estados; ++i)
    {
        fprintf(arquivo_complemento, "%s\n", afd->estados[i]);
    }

    fprintf(arquivo_complemento, "%d\n", afd->tamanho_do_alfabeto);
    for (int i = 0; i < afd->tamanho_do_alfabeto; ++i)
    {
        fprintf(arquivo_complemento, "%c\n", afd->simbolos[i]);
    }

    fprintf(arquivo_complemento, "%d\n", afd->numero_de_transicoes);
    for (int i = 0; i < afd->numero_de_transicoes; ++i)
    {
        fprintf(arquivo_complemento, "%s %c %s\n", afd->transicoes[i].estado_partida, afd->transicoes[i].simbolo, afd->transicoes[i].estado_destino);
    }

    fprintf(arquivo_complemento, "%s\n", afd->estado_inicial);

    // Unica parte que muda no novo AFD
    int novo_numero_de_estados_finais = afd->numero_de_estados - afd->numero_de_estados_finais;
    fprintf(arquivo_complemento, "%d\n", novo_numero_de_estados_finais);
    for (int i = 0; i < afd->numero_de_estados; ++i)
    {
        if (!pertence_ao_conjunto(afd->estados[i], afd->estados_finais, afd->numero_de_estados_finais)) // Se não é um estado final
            fprintf(arquivo_complemento, "%s\n", afd->estados[i]);                                      // Define como estado final
    }
}

/**
 * Função auxiliar a funcionalidade união e serve para determinar a união de dois AFD
*/
void determinar_uniao_afd(struct afd *afd1, struct afd *afd2, FILE *arquivo_uniao)
{

    determinar_produto_afd(afd1, afd2, arquivo_uniao); // Determina o produto dos AFDs

    /**
     * Os estados finais são obtidos fazendo a união entre o produto arteziano entre os estados finais do AFD1 e todos os estados de AFD2
     * com o produto carteziano entre os estados finais do AFD2 e todos os estados de AFD1
     */

    int numero_de_estados_finais_uniao_previstos = afd1->numero_de_estados_finais * afd2->numero_de_estados + afd2->numero_de_estados_finais * afd1->numero_de_estados;

    char *estados[numero_de_estados_finais_uniao_previstos];
    int numero_de_estados_finais_uniao = 0;

    // Primeira produto carteziano
    for (int i = 0; i < afd1->numero_de_estados_finais; ++i)
    {
        for (int j = 0; j < afd2->numero_de_estados; ++j)
        {
            estados[numero_de_estados_finais_uniao] = calloc(100, sizeof(char));
            sprintf(estados[numero_de_estados_finais_uniao], "(%s,%s)", afd1->estados_finais[i], afd2->estados[j]);
            ++numero_de_estados_finais_uniao;
        }
    }

    // Segundo produto carteziano. Aqui existe a possibilidade de se repetir um estado que já foi encontrado
    for (int i = 0; i < afd1->numero_de_estados; ++i)
    {
        for (int j = 0; j < afd2->numero_de_estados_finais; ++j)
        {
            char estado[100];
            sprintf(estado, "(%s,%s)", afd1->estados[i], afd2->estados_finais[j]);
            if (!pertence_ao_conjunto(estado, estados, numero_de_estados_finais_uniao))
                ++numero_de_estados_finais_uniao;
        }
    }

    fprintf(arquivo_uniao, "%d\n", numero_de_estados_finais_uniao);
    // Primeira produto carteziano
    for (int i = 0; i < afd1->numero_de_estados_finais; ++i)
    {
        for (int j = 0; j < afd2->numero_de_estados; ++j)
        {
            fprintf(arquivo_uniao, "(%s,%s)\n", afd1->estados_finais[i], afd2->estados[j]);
        }
    }

    // Segunda produto carteziano
    for (int i = 0; i < afd1->numero_de_estados; ++i)
    {
        for (int j = 0; j < afd2->numero_de_estados_finais; ++j)
        {
            char estado[100];
            sprintf(estado, "(%s,%s)", afd1->estados[i], afd2->estados_finais[j]);
            if (!pertence_ao_conjunto(estado, estados, numero_de_estados_finais_uniao))
                fprintf(arquivo_uniao, estado);
        }
    }
}

/**
 * Função auxiliar a funcionalidade interseção e serve para determinar a interseção de dois AFD
*/
void determinar_intersecao_afd(struct afd *afd1, struct afd *afd2, FILE *arquivo_intersecao)
{

    determinar_produto_afd(afd1, afd2, arquivo_intersecao); // Determina o produto dos AFDs
    
    /**
     * Os estados finais são obtidos fazendo o produto carteziano entre os estados finais do AFD1 e os estados finais de AFD2
     */

    // OU

    /**
     * Os estados finais podem ser obtidos fazendo a interseção entre o produto arteziano entre os estados finais do AFD1 e todos os estados de AFD2
     * com o produto carteziano entre os estados finais do AFD2 e todos os estados de AFD1
     */

    fprintf(arquivo_intersecao, "%d\n", afd1->numero_de_estados_finais * afd2->numero_de_estados_finais);

    // Produto carteziano
    for (int i = 0; i < afd1->numero_de_estados_finais; ++i)
    {
        for (int j = 0; j < afd2->numero_de_estados_finais; ++j)
        {
            fprintf(arquivo_intersecao, "(%s,%s)\n", afd1->estados_finais[i], afd2->estados_finais[j]);
        }
    }
}

/**
 * Esta função determina o AFD mínimo do AFD passado como argumento.
 * O processo é longo e usa o método de partições para achar o AFD mínimo
*/
void minimizar_afd(struct afd *afd, FILE *arquivo_minimizacao)
{

    struct particao *particao_antiga = NULL; // Antiga partição. Esta partição incialmente é nula. Pois ainda não se
                                             // realizou qualquer processo até agora
    struct particao *particao_atual = malloc(sizeof(struct particao)); // Partição atual
    particao_atual->numero_de_grupos = 2; // A partição atual inica com dois grupos
    particao_atual->grupos = calloc(2, sizeof(struct grupo));
    int j = 0;

    /**
     * O primeiro grupo é o grupo dos estados não finais.
    */
    particao_atual->grupos[0].numero_de_estados = afd->numero_de_estados - afd->numero_de_estados_finais;
    particao_atual->grupos[0].estados = calloc(afd->numero_de_estados - afd->numero_de_estados_finais, sizeof(char *));
    for (int i = 0; i < afd->numero_de_estados; ++i)
    {
        if (!pertence_ao_conjunto(afd->estados[i], afd->estados_finais, afd->numero_de_estados_finais)) // Se não é um estado final
            particao_atual->grupos[0].estados[j++] = afd->estados[i];
    }
    j = 0;

    /**
     * O segundo grupo é o grupo dos estados finais
    */
    particao_atual->grupos[1].numero_de_estados = afd->numero_de_estados_finais;
    particao_atual->grupos[1].estados = calloc(afd->numero_de_estados_finais, sizeof(char *));
    for (int i = 0; i < afd->numero_de_estados_finais; ++i)
    {
        particao_atual->grupos[1].estados[j++] = afd->estados_finais[i];
    }

    do // Enquanto a partição atual for diferentes da partição antiga.
    {
        struct particao *particao_auxiliar = malloc(sizeof(struct particao)); // Cria uma partição auxiliar
        particao_auxiliar->grupos = calloc(afd->numero_de_estados, sizeof(struct grupo)); // Com espaço para um número de grupos
                                                                                         // igual ao número de estados.
        int numero_de_grupo_na_particao_auxiliar = 0; // O número de grupos inseridos na partição auxiliar é inicialmente zero.

        for (int i = 0; i < particao_atual->numero_de_grupos; ++i) // Para cada um dos grupos da partiçao atual
        {
            struct particao *pseudo_particao = analisar(particao_atual, i, afd); // É feita uma análise. O objetivo da análise é
                                                                                // verificar se um grupo pode ser quebrado em partes.
            for (int j = 0; j < pseudo_particao->numero_de_grupos; ++j) // Os novos grupos btidos após a análise do grupo atual
            {
                particao_auxiliar->grupos[numero_de_grupo_na_particao_auxiliar++] = pseudo_particao->grupos[j]; // são copiados para a partição auxiliar
            }
        }

        particao_auxiliar->numero_de_grupos = numero_de_grupo_na_particao_auxiliar;

        if(particao_antiga != NULL)
            free(particao_antiga);

        particao_antiga = particao_atual;
        particao_atual = particao_auxiliar;

    } while( !sao_particoes_iguais(particao_antiga, particao_atual) ); // Particiona os grupos de estados até que não seja mais possível

    free(particao_antiga); // Apago a partição antiga, pois já não é mais necessária

    for(int i=0; i < particao_atual->numero_de_grupos; ++i) {
        if( particao_atual->grupos[i].numero_de_estados > 1 ) {
            for(int  j=1; j < particao_atual->grupos[i].numero_de_estados; ++j) {
                // Remove o estado na posição i da lista de estados e substitui as transações pelo estado na posição 0
                substituir_estado_do_afd( particao_atual->grupos[i].estados[j], particao_atual->grupos[i].estados[0],  afd );
            }
        }
    }

    escrever_afd_no_arquivo( afd, arquivo_minimizacao ); // Escreve o AFD novo no arquivo.
}

/**
 * Esta função é responsável pelo reconhecimento de palavras. Ela verifica se uma palavra
 * pertence ao AFD ou não.
*/
void reconher_palavra_afd(struct afd *afd, char *palavra, FILE *arquivo_reconhecimento)
{
    int resultado = reconhecer(afd->estado_inicial, palavra, 0, afd);
    fprintf(arquivo_reconhecimento, "%d\n", resultado);
}
