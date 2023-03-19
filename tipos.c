#include "utils.h"

// #include <malloc.h>
#include <malloc/malloc.h>
#include <string.h>
#include <stdlib.h>

/**
 * Verifica se um elemento pertence a um conjunto
 */
int pertence_ao_conjunto(char *elemento, char **conjunto, int cardinalidade)
{
    for (int i = 0; i < cardinalidade; ++i)
    {
        if (!strcmp(elemento, conjunto[i]))
            return 1;
    }

    return 0;
}

/**
 * Verifica se duas transações têm mesma origem e destino.
 */
int tem_mesma_origem_destino(struct transicao *trasicao1, struct transicao *transicao2)
{
    return trasicao1 == transicao2 ||
           (!strcmp(trasicao1->estado_partida, transicao2->estado_partida) &&
            !strcmp(trasicao1->estado_destino, transicao2->estado_destino));
}

/**
 * Esta função é  necessária ao determianar a união e interseção entre dois conjuntos.
 * Ela verifica caĺcula o produto carteziano entre os AFDs 1 e 2.
 */
void determinar_produto_afd(struct afd *afd1, struct afd *afd2, FILE *arquivo_produto)
{
    // Determina o novo número de estados e imprime no arquivo
    int numero_de_estados_produto = afd1->numero_de_estados * afd2->numero_de_estados;
    fprintf(arquivo_produto, "%d\n", numero_de_estados_produto);
    // Escreve os novos estados no arquivo
    for (int i = 0; i < afd1->numero_de_estados; ++i)
    {
        for (int j = 0; j < afd2->numero_de_estados; ++j)
        {
            fprintf(arquivo_produto, "(%s,%s)\n", afd1->estados[i], afd2->estados[j]);
        }
    }

    // O alfabeto do AFD uniao é o mesmo que AFD1 e AFD2
    fprintf(arquivo_produto, "%d\n", afd1->tamanho_do_alfabeto);
    for (int i = 0; i < afd1->tamanho_do_alfabeto; ++i)
    {
        fprintf(arquivo_produto, "%c\n", afd1->simbolos[i]);
    }

    // O número de estados após a união depende da relaçao entre as transações de AFD1 e AFD2
    // Determina o novo número de transições
    int numero_de_transicoes_produto = 0;
    for (int i = 0; i < afd1->numero_de_transicoes; ++i)
    {
        for (int j = 0; j < afd2->numero_de_transicoes; ++j)
        {
            if (afd1->transicoes[i].simbolo == afd2->transicoes[j].simbolo)
                ++numero_de_transicoes_produto;
        }
    }

    // Escreve o novo número de transições no arquivo
    fprintf(arquivo_produto, "%d\n", numero_de_transicoes_produto);

    // Copia rerefencias dos dados do alfabeto
    int tamanho_do_alfabeto = afd1->tamanho_do_alfabeto;
    char *alfabeto = afd1->simbolos;

    for (int i = 0; i < afd1->numero_de_estados; ++i)
    {
        for (int j = 0; j < afd2->numero_de_estados; ++j)
        {
            for (int k = 0; k < tamanho_do_alfabeto; ++k)
            {

                char *estado_atual_afd1 = afd1->estados[i]; // Um estado do produto
                char *estado_atual_afd2 = afd2->estados[j]; //
                char *proximo_estado_afd1 = NULL;
                char *proximo_estado_afd2 = NULL;

                /**
                 * Os blocos a seguir buscam pelo proximo estado ao estado atual
                 */
                for (int l = 0; l < afd1->numero_de_transicoes; ++l)
                {
                    if (!strcmp(estado_atual_afd1, afd1->transicoes[l].estado_partida) && afd1->transicoes[l].simbolo == alfabeto[k])
                    {
                        proximo_estado_afd1 = afd1->transicoes[l].estado_destino;
                        break;
                    }
                }
                for (int l = 0; l < afd2->numero_de_transicoes; ++l)
                {
                    if (!strcmp(estado_atual_afd2, afd2->transicoes[l].estado_partida) && afd1->transicoes[l].simbolo == alfabeto[k])
                    {
                        proximo_estado_afd2 = afd2->transicoes[l].estado_destino;
                        break;
                    }
                }

                if (proximo_estado_afd1 && proximo_estado_afd1)
                {
                    fprintf(arquivo_produto, "(%s,%s) %c (%s,%s)\n", estado_atual_afd1, estado_atual_afd2, alfabeto[k],
                            proximo_estado_afd1, proximo_estado_afd2);
                }
            }
        }
    }

    // Escreve o estado inicial
    fprintf(arquivo_produto, "(%s,%s)\n", afd1->estado_inicial, afd2->estado_inicial);
}

/**
 * Esta função é auxiliar a função de reconhecimento de palavras dum AFD.
 * Ela verifica recursivamente os simbolos de uma palavra se nos levam a um estado final válido ou não.
 */
int reconhecer(char *estado_atual, char *palavra, int indice_do_simbolo, struct afd *afd)
{
    if (pertence_ao_conjunto(estado_atual, afd->estados_finais, afd->numero_de_estados_finais) && !palavra[indice_do_simbolo])
        return 1;

    if (!palavra[indice_do_simbolo])
        return 0;

    char *proximo_estado = NULL;
    for (int i = 0; i < afd->numero_de_transicoes; ++i)
    {
        if (!strcmp(estado_atual, afd->transicoes[i].estado_partida) && afd->transicoes[i].simbolo == palavra[indice_do_simbolo])
        {
            proximo_estado = afd->transicoes[i].estado_destino;
            break;
        }
    }

    if (proximo_estado)
        return reconhecer(proximo_estado, palavra, indice_do_simbolo + 1, afd);

    return 0;
}

/**
 * Esta função permite escrever um AFD num arquivo de texto.
 * O formato de escrita no arquivo é igual ao formato do arquivo de entrada.
 *
 * É útil para escrever um AFD logo depois de fazer algumas alterações.
 */
void escrever_afd_no_arquivo(struct afd *afd, FILE *arquivo)
{
    fprintf(arquivo, "%d\n", afd->numero_de_estados);
    for (int i = 0; i < afd->numero_de_estados; ++i)
    {
        fprintf(arquivo, "%s\n", afd->estados[i]);
    }

    fprintf(arquivo, "%d\n", afd->tamanho_do_alfabeto);
    for (int i = 0; i < afd->tamanho_do_alfabeto; ++i)
    {
        fprintf(arquivo, "%c\n", afd->simbolos[i]);
    }

    fprintf(arquivo, "%d\n", afd->numero_de_transicoes);
    for (int i = 0; i < afd->numero_de_transicoes; ++i)
    {
        fprintf(arquivo, "%s %c %s\n", afd->transicoes[i].estado_partida, afd->transicoes[i].simbolo, afd->transicoes[i].estado_destino);
    }

    fprintf(arquivo, "%s\n", afd->estado_inicial);

    int novo_numero_de_estados_finais = afd->numero_de_estados - afd->numero_de_estados_finais;
    fprintf(arquivo, "%d\n", novo_numero_de_estados_finais);
    for (int i = 0; i < afd->numero_de_estados_finais; ++i)
    {
        fprintf(arquivo, "%s\n", afd->estados_finais[i]); // Define como estado final
    }
}

/**
 * Esta função remove um estado de um AFD, e substitui as ocorrências desse estado nas transações por outro estado.
 * O estado substituido é o estado que se pretende remover e o estado substituto é o estado que substituirá
 * o estado removido nas transações.
 *
 * É útil na minimização de um AFD
 */
void substituir_estado_do_afd(char *estado_substituido, char *estado_substituto, struct afd *afd)
{

    for (int i = 0; i < afd->numero_de_estados; ++i)
    {
        if (!strcmp(estado_substituido, afd->estados[i]))
        {
            afd->estados[i] = NULL;
            for (int j = i + 1; j < afd->numero_de_estados; ++j)
            {
                afd->estados[j - 1] = afd->estados[j];
            }
            afd->numero_de_estados--;
        }
    }

    for (int i = 0; i < afd->numero_de_estados_finais; ++i)
    {
        if (!strcmp(estado_substituido, afd->estados_finais[i]))
        {
            afd->estados_finais[i] = NULL;
            for (int j = i + 1; j < afd->numero_de_estados_finais; ++j)
            {
                afd->estados_finais[j - 1] = afd->estados_finais[j];
            }
            afd->numero_de_estados_finais--;
        }
    }

    for (int i = 0; i < afd->numero_de_transicoes; ++i)
    {
        if (!strcmp(estado_substituido, afd->transicoes[i].estado_partida))
        {
            afd->transicoes[i].estado_partida = estado_substituto;
        }

        if (!strcmp(estado_substituido, afd->transicoes[i].estado_partida))
        {
            afd->transicoes[i].estado_destino = estado_substituto;
        }
    }
}

/**
 * O método que utilizei para minimizar um AFD, é o metodo das partições assim posso chamar.
 * Esta função verifica se duas partições são iguais ou não.
 *
 * Duas partições são iguais se tiverem o mesmo número de grupos.
 */
int sao_particoes_iguais(struct particao *particao1, struct particao *particao2)
{
    if (particao1 == NULL && particao2 == NULL) // Se ambas as partições são nulas.
        return 1;

    if (particao1 == NULL || particao2 == NULL) // Se uma das partições for nula
        return 0;

    // Duas partições são iguais se tiverem o mesmo número de grupos.
    return particao1->numero_de_grupos == particao2->numero_de_grupos;
}

/**
 * Esta função analisa um grupo de uma dada partição e verifica se o grupo pode ser quebrado
 * em partes ou não.
 * A função retorna uma partição falsa contento os novos grupos ou o mesmo grupo passado, caso
 * o grupo não possa ser mais dividido.
 *
 * @return Os novos grupos obtidos ou o mesmo passado como argumento.
 */
struct particao *analisar(struct particao *particao, int indice_grupo, struct afd *afd)
{
    char **estados_do_grupo_atual = particao->grupos[indice_grupo].estados;
    int numero_de_estados_no_grupo = particao->grupos[indice_grupo].numero_de_estados;
    int numero_de_novos_grupos = 0;

    // Análise dos grupos para os proximos estados para cada simbolo do alfabeto
    struct analise_estado *analise_dos_estados = calloc(numero_de_estados_no_grupo, sizeof(struct analise_estado));

    for (int i = 0; i < numero_de_estados_no_grupo; ++i)
    {
        analise_dos_estados[i].grupos_resultantes_dos_simbolos = calloc(afd->tamanho_do_alfabeto, sizeof(int));
        analise_dos_estados[i].indice_novo_grupo = -1;
        analise_dos_estados[i].quantidade_grupos_resultantes = afd->tamanho_do_alfabeto;

        for (int j = 0; j < analise_dos_estados[i].quantidade_grupos_resultantes; ++j)
        {
            analise_dos_estados[i].grupos_resultantes_dos_simbolos[j] = -1;

            for (int k = 0; k < afd->numero_de_transicoes; ++k)
            {
                if (!strcmp(estados_do_grupo_atual[i], afd->transicoes[k].estado_partida) && afd->transicoes[k].simbolo == afd->simbolos[j])
                {
                    analise_dos_estados[i].grupos_resultantes_dos_simbolos[j] = encontrar_grupo(afd->transicoes[k].estado_destino, particao);
                    break;
                }
            }
        }

        int novo_grupo = tupla_existe(&analise_dos_estados[i], analise_dos_estados, // Verifica se existe um outro
                                      i);

        if (novo_grupo < 0)
        {
            analise_dos_estados[i].indice_novo_grupo = numero_de_novos_grupos++;
        }
        else
        {
            analise_dos_estados[i].indice_novo_grupo = novo_grupo;
        }
    }

    /**
     * Cria uma pseudo partição contendo os novos grupos
     */
    struct particao *presudo_particao = criar_pseudo_particao(estados_do_grupo_atual, numero_de_estados_no_grupo,
                                                              numero_de_novos_grupos, analise_dos_estados);

    for (int i = 0; i < numero_de_estados_no_grupo; ++i)
    {
        free(analise_dos_estados[i].grupos_resultantes_dos_simbolos);
    }
    free(analise_dos_estados);

    return presudo_particao;
}

/**
 * Cria uma pseudo-partição. Nesta partição contem os novos grupos encontrados
 * após uma análise da um dado grupo de uma outra oartição maior.
 */
struct particao *criar_pseudo_particao(char **estados_do_grupo_atual, int numero_de_estados_no_grupo, int numero_de_novos_grupos,
                                       struct analise_estado *analise_dos_estados)
{
    struct particao *particao_auxiliar = malloc(sizeof(struct particao));             // Cria uma partição auxiliar
    particao_auxiliar->grupos = calloc(numero_de_novos_grupos, sizeof(struct grupo)); // Define a quantidade de grupos na artição
    particao_auxiliar->numero_de_grupos = numero_de_novos_grupos;                     // Define a quantidade de grupos

    for (int i = 0; i < numero_de_novos_grupos; ++i)
    {
        particao_auxiliar->grupos[i].estados = calloc(10, sizeof(char *)); // Aloca memória para os estados
        particao_auxiliar->grupos[i].numero_maximo_de_estados = 10;        // Como número máximo de estados no grupo
        particao_auxiliar->grupos[i].numero_de_estados = 0;                // não tem estados ainda no grupo
    }

    for (int i = 0; i < numero_de_estados_no_grupo; ++i)
    {
        int indice_atual = particao_auxiliar->grupos[analise_dos_estados[i].indice_novo_grupo].numero_de_estados++;
        particao_auxiliar->grupos[analise_dos_estados[i].indice_novo_grupo].estados[indice_atual] = estados_do_grupo_atual[i];
    }

    return particao_auxiliar;
}

/**
 * Fução resposável por encontrar o indic do grupo a que pertence o proximo estado de um certo estado num determiando grupo de uma partição.
 * O indice é útil para se saber se haverá necessidade de se partir o grupo em partes ou nào.
 */
int encontrar_grupo(char *estado, struct particao *particao)
{
    for (int i = 0; i < particao->numero_de_grupos; ++i)
    {
        for (int j = 0; j < particao->grupos[i].numero_de_estados; ++j)
        {
            if (!strcmp(estado, particao->grupos[i].estados[j]))
                return i;
        }
    }

    return -1;
}

/**
 * Esta função verifica se o grupos dos estados seguintes (obtido através da transição pelos simbolos do alfabeto)
 * de um dado estado é igual aos grupos dos estados seguintes de um outro estado que já foi analisado.
 *
 * Caso se verifique que existe um estado cujos estados seguintes levam ao mesmo grupo que o estado atual, então
 * o indice do novo grupo desse tal estado é retornado.
 */
int tupla_existe(struct analise_estado *tupla, struct analise_estado *tuplas, int numero_de_tuplas)
{
    int existe = -1;

    if (numero_de_tuplas <= 0)
        return existe;

    for (int i = 0; i < numero_de_tuplas; ++i)
    {
        existe = tuplas[i].indice_novo_grupo;
        for (int j = 0; j < tuplas[i].quantidade_grupos_resultantes; ++j)
        {
            if (tuplas[i].grupos_resultantes_dos_simbolos[j] != tupla->grupos_resultantes_dos_simbolos[j])
            {
                existe = -1;
                break;
            }
        }

        if (existe >= 0)
            break;
    }

    return existe;
}
