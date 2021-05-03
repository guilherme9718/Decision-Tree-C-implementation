#include "matriz.h"
#include "arvore.h"
#include "Vetor.h"
#include "RandomForest.h"

int main() {
    char s[50] = "Social_Network_Ads.csv";
    matriz* m, *ale;
    Grupo* g;
    int i, j;
    m = coleta_dados(s);
    ale = aloca_struct_matriz();

    /* No* arvore=NULL;
    arvore = build_tree(m, 3, 1);
    imprimir_arvore(arvore, 0);
    g = matriz_to_grupo(m);
    int k=0;
    for(i = 0; i < g->n; i++) {
        double pred=0, real=0;
        pred = predict(arvore, g->v[i]);
        real = g->v[i].v[g->v[i].n - 1];
        printf("pred[%d] = %lf - %lf\n", i, pred, real);
        if(pred == real) {
            k++;
        }
    }
    printf("mi k = %d %d", m->i, k);
    printf("\nacerto = %lf", (((double)k) / (double)m->i)); */

    RandomForest* arvore=NULL;
    arvore = cria_random_forest(5, 3, 3, m);
    g = matriz_to_grupo(m);
    int k=0;
    for(i = 0; i < g->n; i++) {
        double pred=0, real=0;
        pred = prever(arvore, g->v[i]);
        real = g->v[i].v[g->v[i].n - 1];
        //printf("pred[%d] = %lf - %lf\n", i, pred, real);
        if(pred == real) {
            k++;
        }
    }
    printf("mi k = %d %d", m->i, k);
    printf("\nacerto = %lf", (((double)k) / (double)m->i));

    return 0;
}
