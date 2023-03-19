#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include "tipos.h"

/**
 * Neste arquivo estão algumas funções auxiliares as funções que realizam as funcionailidades principais do programa
*/

int pertence_ao_conjunto(char *elemento, char **conjunto, int cardinalidade);
int tem_mesma_origem_destino(struct transicao* trasicao1, struct transicao* transicao2);
void determinar_produto_afd(struct afd *afd1, struct afd *afd2, FILE *arquio_produto);
int reconhecer(char *estado_atual, char *palavra, int indice_do_simbolo, struct afd *afd);
struct particao *analisar(struct particao *particao, int indice_grupo, struct afd *afd);
int encontrar_grupo(char *estado, struct particao *particao);
int tupla_existe(struct analise_estado *tupla, struct analise_estado *tuplas, int numero_de_tuplas);
struct particao *criar_pseudo_particao(char **estados_do_grupo_atual, int numero_de_estados_no_grupo, int numero_de_novos_grupos,
                                       struct analise_estado *analise_dos_estados);
int sao_particoes_iguais(struct particao *particao1, struct particao *particao2);
void substituir_estado_do_afd(char* estado_substituido, char* estado_substituto, struct afd* afd);
void escrever_afd_no_arquivo( struct afd* afd, FILE* arquivo_manimizacao  );

#endif // UTILS
