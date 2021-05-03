#include "RandomForest.h"

RandomForest* cria_random_forest(int tam, int amostra, int altura_max, matriz* dataset) {
    RandomForest* arv=NULL;
    matriz* ale = aloca_struct_matriz();
    srand(time(NULL));
    int i, j;
    arv = (RandomForest*)malloc(sizeof(RandomForest));
    arv->n = tam;
    arv->v_arv = (No**)malloc(tam *sizeof(No*));
    
    for(i=0; i < tam; i++) {
        amostra_aleatoria(amostra, dataset, ale);
        arv->v_arv[i] = build_tree(ale, altura_max, 1);
    }
    return arv;
}

double prever(RandomForest* node, Vetor row) {
    double maior=0;
    int i,j;
    Vetor pred;
    pred.v = (double*)malloc(node->n * sizeof(double));
    pred.n = node->n;
    for(i=0; i<node->n; i++) {
        pred.v[i] = predict(node->v_arv[i], row);
    }

    maior = contar_maior(pred);
    free(pred.v);
    return (double)(maior);
}