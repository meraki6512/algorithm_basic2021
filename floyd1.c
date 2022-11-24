#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MaxNode 7
#define Inf 999

int D[MaxNode][MaxNode] = { 0, };
int P[MaxNode][MaxNode] = { 0, };

void initGraph(int i, int j, int w) {
	D[i - 1][j - 1] = w;
}

void printGraph(int Matrix[][MaxNode]) {
	printf("\n");
	for (int i = 0; i < MaxNode; i++) {
		for (int j = 0; j < MaxNode; j++) {
			printf("%3d ", Matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void path(int q, int r) {
	if (P[q - 1][r - 1] != 0) {
		path(q, P[q - 1][r - 1]);
		printf("%4d", P[q - 1][r - 1]);
		path(P[q - 1][r - 1], r);
	}
}

void floyd() {
	printf("[플로이드 알고리즘]\n(진행과정)");
	for (int k = 0; k < MaxNode; k++) {
		for (int i = 0; i < MaxNode; i++) {
			for (int j = 0; j < MaxNode; j++) {
				if (D[i][k] + D[k][j] < D[i][j]) {
					P[i][j] = k + 1;
					printf("\nD[%d][%d] + D[%d][%d] : %d\n", i, k, k, j, D[i][k] + D[k][j]);
					printf("D[%d][%d] : %d\n", i, j, D[i][j]);
					printf("P[%d][%d] = %d\n", i, j, P[i][j]);
					D[i][j] = D[i][k] + D[k][j];
				}
			}
		}
	}
	printf("\n");
}

int main(void) {

	//initGraph
	for (int i = 0; i < MaxNode; i++) {
		for (int j = 0; j < MaxNode; j++) {
			if (i != j) {
				D[i][j] = Inf;
			}
		}
	}
	initGraph(1, 2, 4);
	initGraph(1, 6, 10);
	initGraph(2, 1, 3);
	initGraph(2, 4, 18);
	initGraph(3, 2, 6);
	initGraph(4, 2, 5);
	initGraph(4, 3, 15);
	initGraph(4, 5, 2);
	initGraph(4, 6, 19);
	initGraph(4, 7, 5);
	initGraph(5, 3, 12);
	initGraph(5, 4, 1);
	initGraph(6, 7, 10);
	initGraph(7, 4, 8);


	//Q1. floyd algorithm
	printf("[알고리즘 실행 전]\n");
	printf("[D]");
	printGraph(D);
	printf("[P]");
	printGraph(P);
	floyd();
	printf("[알고리즘 실행 후]\n");
	printf("[D]");
	printGraph(D);
	printf("[P]");
	printGraph(P);


	//Q2. find path
	printf("Path (v7, v3):");
	printf("%4d", 7);
	path(7, 3);
	printf("%4d", 3);
	printf("\n");
}


