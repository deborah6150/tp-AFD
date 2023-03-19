#ifndef MANIPULADOR_AFD
#define MANIPULADOR_AFD

#include <stdio.h>
#include "tipos.h"


void ler_afd(FILE* arquivo_afd, struct afd* afd);
void imprimir_afd(struct afd* afd);
void tranformar_afd_para_dot(struct afd* afd, FILE* arquivo_dot);
void determinar_complemento_afd(struct afd* afd, FILE* arquivo_complemento);
void determinar_uniao_afd(struct afd* afd1, struct afd* afd2, FILE* arquivo_uniao);
void determinar_intersecao_afd(struct afd* afd1, struct afd* afd2, FILE* arquivo_intersecao);
void minimizar_afd(struct afd* afd, FILE* arquivo_minimizacao);
void reconher_palavra_afd(struct afd* afd, char* palavra, FILE* arquivo_reconhecimento);

#endif //MANIPULADOR_AFD
