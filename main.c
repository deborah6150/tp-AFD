////
////  main.c
////  tp-ftc
////
////  Created by Deborah Caroline on 19/03/23.
////
//
//#include <stdio.h>
//
//int main(int argc, const char * argv[]) {
//    // insert code here...
//    printf("Hello, World!\n");
//    return 0;
//}
#include <stdio.h>
#include <stdlib.h>
#include "analisador_args.h"
#include "funcionalidades.h"
#include <stdlib.h>

void executar_funcionalidade(struct analise *analise);

int main(int argc, char *argv[])
{
    struct analise analise;

    if (!analisar_argumentos(argc, argv, &analise))
    {
        exit(1);
    }

    executar_funcionalidade(&analise);

    return 0;
}

void executar_funcionalidade(struct analise *analise)
{
    if (analise->funcionalidade == DOT)
    {
        visualizacao(analise->entrada1, analise->saida);
    }
    else if (analise->funcionalidade == COMPLEMENTO)
    {
        complemento(analise->entrada1, analise->saida);
    }
    else if (analise->funcionalidade == INTERCECAO)
    {
        intersecao(analise->entrada1, analise->entrada2, analise->saida);
    }
    else if (analise->funcionalidade == UNIAO)
    {
        uniao(analise->entrada1, analise->entrada2, analise->saida);
    }
    else if (analise->funcionalidade == MINIMIZACAO)
    {
        minimizacao(analise->entrada1, analise->saida);
    }
    else if (analise->funcionalidade == RECONHECER)
    {
        reconhecimento(analise->entrada1, analise->entrada2, analise->saida);
    }
}
