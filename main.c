#include <stdio.h>
#include <stdlib.h>

typedef struct vetor_double {
    double* v;
    size_t n;
} Vetor;

typedef struct grupo_vetor {
    Vetor* v;
    size_t n;
} Grupo;

typedef struct grupos_grupo {
    Grupo* v;
    size_t n;
} Grupos;

unsigned int contar(Vetor vet, double a) {
    unsigned int n, i;
    n=0;
    for(i=0; i < vet.n; i++) {
        if(vet.v[i] == a) {
            n++;
        }
    }
    return n;
}

double gini_index(Grupos grupos, Vetor classes) {
    double gini, score, p;
    unsigned int i, j, n_instances, tam;

    //Contar o numero de instâncias nos grupos
    n_instances = 0;
    for(i = 0; i < grupos.n; i++) {
        n_instances += grupos.v[i].n;
    }
    //Calcular o Gini index
    gini = 0;
    for(i = 0; i < grupos.n; i++) {
        tam = grupos.v[i].n;
        if(tam == 0)
            continue;

        //Atribuir um score para grupo baseado na classe
        score = 0.0;
        for(j = 0; j < classes.n; j++) {
            unsigned int k, linhas = grupos.v[i].n;

            Vetor aux;
            aux.v = (double*)malloc(linhas * sizeof(double));
            aux.n = linhas;

            for(k = 0; k < linhas; k++) {
                unsigned int tam_linha = grupos.v[i].v[k].n;
                aux.v[k] = grupos.v[i].v[k].v[tam_linha - 1];
            }
            p = (contar(aux, classes.v[j])) / ((double)tam);
            score += p * p;
            printf("score = %lf\n", score);
            free(aux.v);
        }

        gini += (1.0 - score) * ((double)tam / n_instances);
        printf("gini = %lf\n", gini);
    }
    return gini;
}

int main()
{
    int i, j;
    //[[[1, 1], [1, 0]], [[1, 1], [1, 0]]], [0, 1]

    Grupos entrada;
    entrada.v = (Grupo*)malloc(2 * sizeof(Grupo));
    entrada.n = 2;
    for(i=0; i < entrada.n; i++) {
        entrada.v[i].v = (Vetor*)malloc(2*sizeof(Vetor));
        entrada.v[i].n = 2;
    }
    for(i=0; i < entrada.n; i++) {
        for(j=0; j < entrada.v[i].n; j++) {
            entrada.v[i].v[j].v = (double*)malloc(2*sizeof(double));
            entrada.v[i].v[j].n = 2;
        }
    }
    //[[[1, 0], [1, 0]], [[1, 1], [1, 1]]], [0, 1]
    entrada.v[0].v[0].v[0] = 1;
    entrada.v[0].v[0].v[1] = 0;
    entrada.v[0].v[1].v[0] = 1;
    entrada.v[0].v[1].v[1] = 0;
    entrada.v[1].v[0].v[0] = 1;
    entrada.v[1].v[0].v[1] = 1;
    entrada.v[1].v[1].v[0] = 1;
    entrada.v[1].v[1].v[1] = 1;

    Vetor classe;
    classe.v = (double*)malloc(2*sizeof(double));
    classe.n = 2;
    classe.v[0] = 0;
    classe.v[1] = 1;

    double gini;
    gini = gini_index(entrada, classe);
    printf("%lf", gini);
    return 0;
}
