#define _CRT_SECURE_NO_WARNINGS
#define NULL 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10
#define num 6

typedef struct Node {
	char key[MAX];
	float p;
	struct Node* left;
	struct Node* right;
}node;

node* createNode(float p, node* lchild, node* rchild) {
	node* newnode = (node*)malloc(sizeof(node));
	newnode->p = p;
	newnode->left = lchild;
	newnode->right = rchild;
	return newnode;
}

node* root = NULL;
node* keys[MAX];
float A[MAX+1][MAX];
int R[MAX][MAX];

void optimalBST() {
	int i, j, k, diagonal;

	for (i = 1; i <= num; i++) {
		A[i][i-1] = 0;
		A[i][i] = keys[i]->p;
		R[i][i] = i;
		R[i][i-1] = 0;
	}

	A[num+1][num] = 0;
	R[num+1][num] = 0;

	for (diagonal = 1; diagonal <= num - 1; diagonal++) {
		for (i = 1; i < num - diagonal + 1; i++) {
			float psum = 0;
			j = i + diagonal;
			for (k = i; k <= j; k++) {
				psum = psum + keys[k]->p;
			}
			for (k = i; k <= j; k++) {
				if ((A[i][k - 1] + A[k + 1][j]) + psum < A[i][j]) {
					A[i][j] = A[i][k - 1] + A[k + 1][j] + psum;
					R[i][j] = k;
				}
			}
		}
	}
}

node* tree(int i, int j) {
	int k;
	node* p;
	k = R[i][j];

	if (k == 0)
		return NULL;
	else {
		p = keys[k];
		p->left = tree(i, k - 1);
		p->right = tree(k + 1, j);
		return p;
	}
}


int main(void) {
	
	//input data
	keys[1] = createNode(0.05, NULL, NULL);
	strcpy(keys[1]->key, "CASE");
	keys[2] = createNode(0.15, NULL, NULL);
	strcpy(keys[2]->key, "ELSE");
	keys[3] = createNode(0.05, NULL, NULL);
	strcpy(keys[3]->key, "END");
	keys[4] = createNode(0.35, NULL, NULL);
	strcpy(keys[4]->key, "IF");
	keys[5] = createNode(0.05, NULL, NULL);
	strcpy(keys[5]->key, "OF");
	keys[6] = createNode(0.35, NULL, NULL);
	strcpy(keys[6]->key, "THEN");

	for (int i = 0; i <= num; i++) {
		for (int j = 0; j <= num; j++) {
			A[i][j] = 100;
		}
	}

	//print [Input]
	printf("[Input]\n");
	for (int i = 1; i <= num; i++) {
		printf("key[%d]: ", i);
		printf("%5s\t", keys[i]->key);
		printf("%5.2f\n", keys[i]->p);
	}
	printf("\n");

	//OBST
	optimalBST();

	//print [A]
	printf("[A]\n");
	for (int i = 1; i <= num; i++) {
		for (int j = 1; j <= num; j++) {
			printf("%5.2f\t", A[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	//print [R]
	printf("[R]\n");
	for (int i = 1; i <= num; i++) {
		for (int j = 1; j <= num; j++) {
			printf("%3d\t", R[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	printf("탐색최소시간 Root Node: ");
	printf("%s\n", keys[R[1][num]]->key);

	return 0;
}

