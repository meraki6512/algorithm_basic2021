#include <stdio.h>
#include<stdlib.h>
#define MAX_VERTICES 10 
#define INF 999

void prim(int start, int connected[], int minDist[], int weight[][MAX_VERTICES]) {
	minDist[start] = 0;
	for (int i = 0; i < MAX_VERTICES; i++) {
		
		// find nearest vertex
		int nearest = 0;
		for (int j = 0; j < MAX_VERTICES; j++) { // nearest 임의 설정
			if (connected[j] == 0) {
				nearest = j;
			}
		}
		for (int j = 0; j < MAX_VERTICES; j++) { // minDist비교하며, nearest 변경
			if (connected[j] == 0 && (minDist[j] < minDist[nearest]))
				nearest = j;
		}
		printf("%d ", nearest + 1);
		connected[nearest] = 1;
		
		// update minDist
		for (int j = 0; j < MAX_VERTICES; j++) {
			if (weight[nearest][j] < minDist[j] && connected[j] == 0) {
				minDist[j] = weight[nearest][j];
			}
		}
	}
}

typedef struct {
	int src;
	int dest;
	int weight;
}Node;

int compare(const void* a, const void* b) {
	const Node* m1 = (const Node*)a;
	const Node* m2 = (const Node*)b;
	return m1->weight - m2->weight;
}

int find_set(int parent[], int child) {
	int i, wp;
	for (i = child; (wp = parent[i]) >= 0; i = wp);
	int p = i; 
	for (int k = child; (wp=parent[k]) >= 0; k=wp) {
		parent[k] = p;
	}
	return p;
}

void kruskal(int parent[], int num[], int weight[][MAX_VERTICES]) {
	Node array[MAX_VERTICES] = { 0 };
	int index = 0;
	for (int i = 0; i < MAX_VERTICES; i++) {
		printf("\n%d", i);
		for (int j = 0; j < MAX_VERTICES; j++) {
			printf("%d", j);
			if (weight[i][j] != 0) {
				array[index].weight = weight[i][j];
				weight[j][i] = 0;
				array[index].src = i;
				array[index].dest = j;
				index++;
			}
		}
	}
	qsort(array, index, sizeof(Node), compare); //stdlib.h
	for (int i = 0; i < index; i++) {
		printf("%d\n", array[i].weight);
	}
	
	int connected = 0;
	for (int i = 0; connected < MAX_VERTICES - 1; i++) {
		if (i < index) {
			int min = array[i].weight;
			int u = find_set(parent, array[i].src);
			int v = find_set(parent, array[i].dest);
			if (u != v) {
				connected++;
				if (num[u] < num[v]) {
					parent[u] = v;
					num[v] += num[u];
				}
				else {
					parent[v] = u;
					num[u] += num[v];
				}
				printf("%d) 선택한 가중치: %d\n", connected, min);
			}
		}
	}
}

int main(void) {

	//init
	int weight[MAX_VERTICES][MAX_VERTICES] = {
	{0, 32, INF, 17, INF, INF, INF, INF, INF, INF},
	{32, 0, INF, INF, 45, INF, INF, INF, INF, INF},
	{INF, INF, 0, 18, INF, INF, 5, INF, INF, INF},
	{17, INF, 18, 0, 10, INF, INF, 3, INF, INF},
	{INF, 45, INF, 10, 0, 28, INF, INF, 25, INF},
	{INF, INF, INF, INF, 28, 0, INF, INF, INF, 6},
	{INF, INF, 5, INF, INF, INF, 0, 59, INF, INF},
	{INF, INF, INF, 3, INF, INF, 59, 0, 4, INF},
	{INF, INF, INF, INF, 25, INF, INF, 4, 0, 12},
	{INF, INF, INF, INF, INF, 6, INF, INF, 12, 0}
	};

	//Q1
	int connected[MAX_VERTICES] = { 0,0,0,0,0,0,0,0,0,0 };
	int minDist[MAX_VERTICES] = { INF, INF, INF, INF, INF, INF, INF, INF, INF, INF };
	printf("[Prim: v1부터]\n");
	prim(0, connected, minDist, weight);
	printf("\n\n");

	//Q2
	int connected2 [MAX_VERTICES] = { 0,0,0,0,0,0,0,0,0,0 };
	int minDist2 [MAX_VERTICES] = { INF, INF, INF, INF, INF, INF, INF, INF, INF, INF };
	printf("[Prim: v8부터]\n");
	prim(7, connected2, minDist2, weight);
	printf("\n\n");

	//Q3
	int parent[MAX_VERTICES] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	int num[MAX_VERTICES] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	printf("[Kruskal]\n");
	//kruskal(parent, num, weight);
	printf("\n");

	return 0;
}
