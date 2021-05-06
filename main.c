#include "matriz.h"
#include "arvore.h"
#include "Vetor.h"
#include "RandomForest.h"
#include <unistd.h>

int main() {
    //nome do arquivo dos dados
    char s[50] = "data/Social_Network_Ads.csv";
    TrainTest tt;
    matriz* m, *treino, *teste;
    Grupo* g;
    int i, j;
    srand(time(NULL));

    //coleta os dados e coloca em m
    m = coleta_dados(s);
    
    //separa dados de treino e dados de teste
    tt = train_test_split(m, 0.80);
    treino = tt.train;
    teste = tt.test;

    //cria random forest com 3 árvores de decisão, com amostra minima 20 e com altura máxima 8
    RandomForest* arvore=NULL;
    arvore = cria_random_forest(3, 20, 5, treino);

    //Imprime as árvores da Random Forest
    imprimir_radomforest(arvore);

    //calcula porcentagem de acerto
    double acerto = porcentagem_acerto(teste, arvore);
    printf("\nacerto = %lf\n", acerto);

    //desaloca toda memoria alocada das arvores
    desaloca_randomforest(arvore);

    //testa várias Random Forest
    double acerto_total = 0;
    for(i=0; i < 20; i++) {
        tt = train_test_split(m, 0.80);
        arvore = cria_random_forest(10, 20, 10, tt.train);
        acerto = porcentagem_acerto(tt.test, arvore);
        acerto_total += acerto;
        //imprimir_radomforest(arvore);
        printf("acerto da Random Florest [%d] = %lf\n\n", i, acerto);

        libera_matriz(tt.test);
        libera_matriz(tt.train);
        desaloca_randomforest(arvore);
    }
    printf("media de acerto das Random Florests = %lf\n", acerto_total / (double)i);
    libera_matriz(m);
    libera_matriz(treino);
    libera_matriz(teste);

    return 0;
}
