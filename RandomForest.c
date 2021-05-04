#include "RandomForest.h"

//Cria Random forest alocando várias decision trees
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

//prevê o valor esperado para cada decisionTree na random forest e pega o valor que mais aparece
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

//calcula a porcentagem de acerto da Random Forest no dataset
double porcentagem_acerto(matriz* dataset, RandomForest* arv) {
    int i, j, k=0;
    Grupo *pred = matriz_to_grupo(dataset);
    for(i = 0; i < pred->n; i++) {
        double p=0, r=0;
        p = prever(arv, pred->v[i]);
        r = pred->v[i].v[pred->v[i].n - 1];
        if(p == r) {
            k++;
        }
    }

    return ( ((double)k) / (double)dataset->i);
}

void desaloca_randomforest(RandomForest* arv) {
    int i;
    for(i=0; i < arv->n; i++) {
        desaloca_arvore(arv->v_arv[i]);
    }
    free(arv);
}