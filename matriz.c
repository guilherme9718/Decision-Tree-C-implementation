#include "matriz.h"

#define MAX_SIZE 1000

matriz* aloca_struct_matriz()
{
    matriz* m = (matriz*)malloc(sizeof(matriz));
    m->i = 1;
    m->j = 1;
    return m;
}

void libera_matriz(matriz* m)
{
    free(m);
}

void imprime_matriz(const matriz* m)
{
    for(int k = 0; k < m->i; k++)
    {
        for(int p = 0; p < m->j; p++)
        {
            printf("%lf ", m->M[k][p]);
        }
        printf ("\n");
    }
}

matriz* insere_matriz(matriz* m, char* arq)
{
    FILE *dados;
    int k = 0, p = 0;
    char *str, *token, linha[30];
    double numero;
    dados = fopen(arq, "rt");

    if(dados == NULL)
    {
        printf("Erro na leitura do arquivo.\n");
        exit(1);
    }

    while(!feof(dados))
    {
        p = 0;
        str = fgets(linha, 30, dados);
        token = strtok(str, ",");
        numero = atof(token);
        m->M[k][p] = numero;
        while(token != NULL)
        {
            token = strtok(NULL, ",");
            if(token != NULL) {
                numero = atof(token);
                p++;
                m->j = p;
                m->M[k][p] = numero;
            }

        }
        k++;
        m->i = k;
    }
    m->j += 1;
    fclose(dados);
    return m;
}

int* rand_sem_rep(matriz* m, int n, int* numeros){
    numeros = malloc(m->i * sizeof(int));

    for (int i = 0; i < m->i; i++) {
        numeros[i] = i;
    }

    for (int i = n; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = numeros[j];
        numeros[j] = numeros[i];
        numeros[i] = tmp;
    }

    return numeros;
}

matriz* amostra_aleatoria(int n, matriz* m, matriz* m_a){
    if(n > m->i){
        printf("Amostra muito grande.\n");
        exit(1);
    }

    int *numeros = NULL;
    numeros = rand_sem_rep(m, n, numeros);
    for(int k = 0; k < n; k++){
        for(int p = 0; p < m->j; p++){
            m_a->M[k][p] = m->M[numeros[k]][p];
        }
    }

    m_a->j = m->j;
    m_a->i = n;
    return m_a;
}

matriz* coleta_dados()
{
    matriz* m = NULL;
    m = aloca_struct_matriz();
    m = insere_matriz(m, "dadosteste.csv");
    return m;
}
