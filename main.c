#include "matriz.h"
#include "arvore.h"
#include "Vetor.h"
#include "RandomForest.h"
#include <math.h>

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
    int qtd_randomforest = 30;
    double acerto_total = 0;
    double acertos[60];
    for(i=0; i < qtd_randomforest; i++) {
        tt = train_test_split(m, 0.80);
        arvore = cria_random_forest(10, 20, 10, tt.train);
        acerto = porcentagem_acerto(tt.test, arvore);
        acerto_total += acerto;
        acertos[i] = acerto;
        //imprimir_radomforest(arvore);
        printf("acerto da Random Florest [%d] = %lf\n\n", i, acerto);

        libera_matriz(tt.test);
        libera_matriz(tt.train);
        desaloca_randomforest(arvore);
    }

    double media = acerto_total / (double)qtd_randomforest;
    //cálculo do desvio padrão
    double aux, desvio=0;
    for(i = 0; i < qtd_randomforest; i++) {
        aux = (acertos[i] - media);
        desvio += aux*aux;
    }
    desvio = desvio / (double)(qtd_randomforest - 1);
    desvio = sqrt(desvio);

    //t de student para 95% de confiança e grau de liberdade = 29
    double t_student = 2.046;

    //Intervalo de confiança
    double intv_1, intv_2;
    intv_1 = media - ((t_student * desvio) / sqrt(qtd_randomforest));
    intv_2 = media + ((t_student * desvio) / sqrt(qtd_randomforest));

    printf("media de acerto das Random Florests = %lf\n", media);
    printf("desvio padrao de acerto das Random Florests = %lf\n", desvio);
    printf("intervalo de confiança = %lf <= media <= %lf\n", intv_1, intv_2);

    libera_matriz(m);
    libera_matriz(treino);
    libera_matriz(teste);

    return 0;
}
