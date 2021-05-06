all:
	gcc -o randomForest RandomForest.h RandomForest.c stdafx.h Vetor.c Vetor.h arvore.h arvore.c matriz.h matriz.c main.c -lm
clean:
	rm randomForest
