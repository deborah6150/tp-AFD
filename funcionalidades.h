#ifndef FUNCIONALIDADES_H
#define FUNCIONALIDADES_H
/**
 * @name Funcionalidades - Neste módulo estão as funções que executam cada uma das
 * funcionalidades do programa.
*/

//
//

/**
 * Função que executa a funcionalidade de conversão de um AFD num arquivo txt
 * para a linguagem DOT.
 * @param afd - Nome do arquivo com o AFD de entrada
 * @param afd_dot - Nome do arquivo que conterá o AFD na linguagem DOT do AFD em afd
*/
void visualizacao(char* afd, char* afd_dot);

/**
 * Função que determina o complemento de um AFD
 * @param afd - Nome do arquivo com o AFD de entrada
 * @param afd_complemento - Nome do arquivo que conterá o AFD complementar do AFD em afd
*/
void complemento(char* afd, char* afd_complemento);

/**
 * Função que determina o complemento de um AFD
 * @param afd1 - Nome do arquivo com o primeiro AFD de entrada
 * @param afd2 - Nome do arquivo com o segundo AFD de entrada
 * @param afd_intersecao - Nome do arquivo que conterá o AFD interseção entre o AFD em afd1 e o AFD em afd2
*/
void intersecao(char* afd1, char* afd2, char* afd_intersecao);


/**
 * Função que determina o complemento de um AFD
 * @param afd1 - Nome do arquivo com o primeiro AFD de entrada
 * @param afd2 - Nome do arquivo com o segundo AFD de entrada
 * @param afd_uniao - Nome do arquivo que conterá o AFD união entre o AFD em afd1 e o AFD em afd2
*/
void uniao(char* afd1, char* afd2, char* afd_uniao);


/**
 * Função que determina o complemento de um AFD
 * @param afd - Nome do arquivo com o AFD de entrada
 * @param afd_minimo - Nome do arquivo que conterá o AFD mínimo do AFD em afd
*/
void minimizacao(char* afd, char* afd_minimo);

/**
 * Função que determina o complemento de um AFD
 * @param afd - Nome do arquivo com o primeiro AFD de entrada
 * @param palavras - Nome do arquivo com a lista de palavras a serem reconhecidadas | validadas
 * @param palvras_reconhecidas - Nome do arquivo que conterá as palavras reconhecidas pelo AFD em afd
*/
void reconhecimento(char* afd, char* palavras, char* palvras_reconhecidas);

#endif // FUNCIONALIDADES_H
