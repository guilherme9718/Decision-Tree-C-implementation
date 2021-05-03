#include "matriz.h"
#include "arvore.h"
#include "Vetor.h"

int main() {
    matriz* m;
    m = coleta_dados();

    No* arvore=NULL;
    arvore = build_tree(m, 3, 1);
    imprimir_arvore(arvore, 0);

    return 0;
}
