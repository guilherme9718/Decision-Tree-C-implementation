all:
	gcc -o teste1 RandomForest.h RandomForest.c stdafx.h Vetor.c Vetor.h arvore.h arvore.c matriz.h matriz.c teste1.c -lm
	gcc -o teste2 RandomForest.h RandomForest.c stdafx.h Vetor.c Vetor.h arvore.h arvore.c matriz.h matriz.c teste2.c -lm
clean:
	rm teste1 teste2
