#ifndef RANDOMFOREST_H_INCLUDED
#define RANDOMFOREST_H_INCLUDED

#include "stdafx.h"
#include "arvore.h"
#include "matriz.h"
#include "Vetor.h"

typedef struct RandomForest {
    No** v_arv;
    size_t n; 
} RandomForest;

RandomForest* cria_random_forest(int tam, int amostra, int altura_max, matriz* dataset);
double prever(RandomForest* node, Vetor row);

#endif