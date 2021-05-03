#ifndef MATRIZ_H_INCLUDED
#define MATRIZ_H_INCLUDED

#include "stdafx.h"

#define MAX_SIZE 1000

typedef struct matriz{
    double M[MAX_SIZE][MAX_SIZE];
    int i;
    int j;
}matriz;

matriz* aloca_struct_matriz();

void libera_matriz(matriz* m);
void imprime_matriz(const matriz* m);

matriz* insere_matriz(matriz* m, char* arq);

matriz* coleta_dados();


#endif // MATRIZ_H_INCLUDED
