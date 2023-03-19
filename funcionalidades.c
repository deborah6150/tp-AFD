#include "funcionalidades.h"
#include "manipulador_afd.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Funcionalidade visualização
 */
void visualizacao(char *afd, char *afd_dot)
{
    FILE *arquivo_afd = fopen(afd, "r");         // Abre o arquivo com o AFD de entrada para leitura
    FILE *arquivo_afd_dot = fopen(afd_dot, "w"); // Abre o arquivo do AFD de saída (dot) para escrita

    if (arquivo_afd == NULL || arquivo_afd_dot == NULL)
    {
        perror("Arquivo do AFD de entrada não existe ou não foi possível criar o arquivo do AFD dot.\n");
        return;
    }

    struct afd afd_struct;
    ler_afd(arquivo_afd, &afd_struct);
    tranformar_afd_para_dot(&afd_struct, arquivo_afd_dot);

    fclose(arquivo_afd);
    fclose(arquivo_afd_dot);
}

/**
 * Funcionalidade complemento
 */
void complemento(char *afd, char *afd_complemento)
{
    FILE *arquivo_afd = fopen(afd, "r");                         // Abre o arquivo com o AFD de entrada para leitura
    FILE *arquivo_afd_complemento = fopen(afd_complemento, "w"); // Abre o arquivo do AFD de saída (complemento) para escrita

    if (arquivo_afd == NULL || arquivo_afd_complemento == NULL)
    {
        perror("Arquivo do AFD de entrada não existe ou não foi possível criar o arquivo do AFD complemento.\n");
        return;
    }

    struct afd afd_struct;
    ler_afd(arquivo_afd, &afd_struct);
    determinar_complemento_afd(&afd_struct, arquivo_afd_complemento);

    fclose(arquivo_afd);
    fclose(arquivo_afd_complemento);
}

/**
 * Funcionalidade interseção
 */
void intersecao(char *afd1, char *afd2, char *afd_intersecao)
{
    FILE *arquivo_afd1 = fopen(afd1, "r");                     // Abre o arquivo com o AFD1 de entrada para leitura
    FILE *arquivo_afd2 = fopen(afd2, "r");                     // Abre o arquivo com o AFD2 de entrada para leitura
    FILE *arquivo_afd_intersecao = fopen(afd_intersecao, "w"); // Abre o arquivo do AFD de saída (interseção) para escrita

    if (arquivo_afd1 == NULL || arquivo_afd2 == NULL || arquivo_afd_intersecao == NULL)
    {
        perror("Arquivo do AFD1 ou AFD2 de entrada não existe ou não foi possível criar o arquivo do AFD interseção.\n");
        return;
    }

    struct afd afd1_struct, afd2_struct;
    ler_afd(arquivo_afd1, &afd1_struct);
    ler_afd(arquivo_afd2, &afd2_struct);
    determinar_intersecao_afd(&afd1_struct, &afd2_struct, arquivo_afd_intersecao);

    fclose(arquivo_afd1);
    fclose(arquivo_afd2);
    fclose(arquivo_afd_intersecao);
}

/**
 * Funcionalidade união
 */
void uniao(char *afd1, char *afd2, char *afd_uniao)
{
    FILE *arquivo_afd1 = fopen(afd1, "r");           // Abre o arquivo com o AFD1 de entrada para leitura
    FILE *arquivo_afd2 = fopen(afd2, "r");           // Abre o arquivo com o AFD2 de entrada para leitura
    FILE *arquivo_afd_uniao = fopen(afd_uniao, "w"); // Abre o arquivo do AFD de saída (união) para escrita

    if (arquivo_afd1 == NULL || arquivo_afd2 == NULL || arquivo_afd_uniao == NULL)
    {
        perror("Arquivo do AFD1 ou AFD2 de entrada não existe ou não foi possível criar o arquivo do AFD união.\n");
        return;
    }

    struct afd afd1_struct, afd2_struct;
    ler_afd(arquivo_afd1, &afd1_struct);
    ler_afd(arquivo_afd2, &afd2_struct);
    determinar_uniao_afd(&afd1_struct, &afd2_struct, arquivo_afd_uniao);

    fclose(arquivo_afd1);
    fclose(arquivo_afd2);
    fclose(arquivo_afd_uniao);
}

/**
 * Funcionalidade minimização
 */
void minimizacao(char *afd, char *afd_minimo)
{
    FILE *arquivo_afd = fopen(afd, "r");               // Abre o arquivo com o AFD de entrada para leitura
    FILE *arquivo_afd_minimo = fopen(afd_minimo, "w"); // Abre o arquivo do AFD de saída (dot) para escrita

    if (arquivo_afd == NULL || arquivo_afd_minimo == NULL)
    {
        perror("Arquivo do AFD de entrada não existe ou não foi possível criar o arquivo do AFD complemento.\n");
        return;
    }

    struct afd afd_struct;
    ler_afd(arquivo_afd, &afd_struct);
    minimizar_afd(&afd_struct, arquivo_afd_minimo);

    fclose(arquivo_afd);
    fclose(arquivo_afd_minimo);
}

/**
 * Funcionalidade reconhecimento
 */
void reconhecimento(char *afd, char *palavras, char *palvras_reconhecidas)
{
    FILE *arquivo_afd = fopen(afd, "r");                                        // Abre o arquivo com o AFD1 de entrada para leitura
    FILE *arquivo_palavras = fopen(palavras, "r");                              // Abre o arquivo com o AFD2 de entrada para leitura
    FILE *arquivo_afd_palavras_reconhecidas = fopen(palvras_reconhecidas, "w"); // Abre o arquivo do AFD de saída (dot) para escrita

    if (arquivo_afd == NULL || arquivo_palavras == NULL || arquivo_afd_palavras_reconhecidas == NULL)
    {
        perror("Arquivo do AFD ou Palavras de entrada não existe ou não foi possível criar o arquivo de palavras reconhecidas.\n");
        return;
    }

    struct afd afd_struct;
    ler_afd(arquivo_afd, &afd_struct);

    char linha[100];
    while (fgets(linha, 100, arquivo_palavras))
    {
        char *palavra = strtok(linha, "\n");
        reconher_palavra_afd(&afd_struct, palavra, arquivo_afd_palavras_reconhecidas);
    }

    fclose(arquivo_afd);
    fclose(arquivo_palavras);
    fclose(arquivo_afd_palavras_reconhecidas);
}
