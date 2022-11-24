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

void path(int q, int r){
	if (P[q-1][r-1] != 0) {
		path(q, P[q - 1][r - 1]);
		printf("%4d", P[q - 1][r - 1]);
		path(P[q-1][r-1], r);
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
	initGraph(1, 7, 10);
	initGraph(2, 3, 1);
	initGraph(2, 4, 12);
	initGraph(3, 1, 19);
	initGraph(3, 2, 2);
	initGraph(3, 4, 15);
	initGraph(3, 5, 5);
	initGraph(3, 7, 5);
	initGraph(4, 5, 6);
	initGraph(5, 3, 18);
	initGraph(5, 6, 3);
	initGraph(6, 1, 10);
	initGraph(6, 5, 4);
	initGraph(7, 3, 8);
	

	//Q3. floyd algorithm
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


	//Q4. find path
	printf("Path (a7, a4):");
	printf("%4d", 7);
	path(7, 4);
	printf("%4d", 4);
	printf("\n");
}


