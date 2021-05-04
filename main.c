#include "matriz.h"
#include "arvore.h"
#include "Vetor.h"
#include "RandomForest.h"

int main() {
    //nome do arquivo dos dados
    char s[50] = "Social_Network_Ads.csv";
    matriz* m;
    Grupo* g;
    int i, j;

    //coleta os dados e coloca em m
    m = coleta_dados(s);

    //cria random forest
    RandomForest* arvore=NULL;
    arvore = cria_random_forest(10, 50, 3, m);

    //calcula porcentagem de acerto
    double acerto = porcentagem_acerto(m, arvore);
    printf("\nacerto = %lf", acerto);

    //desaloca toda memoria alocada das arvores
    desaloca_randomforest(arvore);

    //testa diferentes argumentos para a random forest
    for(i=1; i < 100; i++) {
        arvore = cria_random_forest(i, 50, 3, m);
        acerto = porcentagem_acerto(m, arvore);
        printf("\nacerto com %d de altura = %lf", i, acerto);
        desaloca_randomforest(arvore);
    }
    return 0;
}
