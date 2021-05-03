all:
	gcc -o decisionTree stdafx.h Vetor.c Vetor.h arvore.h arvore.c matriz.h matriz.c main.c
clean:
	rm decisionTree
