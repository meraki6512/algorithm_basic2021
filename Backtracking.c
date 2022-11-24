#include <stdio.h>
#include <stdlib.h> //abs, rand

#define n 8 // n-Queens
#define N 6 // Sum-of-Subsets


// Monte-Carlo estimate (n-Queens problem)

int col[n] = { 0, };

bool promising1(int i) {
	bool swch = true;
	for (int k = 1; k < i && swch; k++) {
		if (col[i] == col[k] || (abs(col[i] - col[k]) == (i - k)))
			swch = false;
	}
	return swch;
}

int estimate_nQueens() {
	int i = 0, j = 1;
	int m = 1, mprod = 1, numnodes = 1; //m: promising한 child의 개수, numnodes: 노드의 총 개수 추정치
	int promisingChildSet[n] = { 0, };
	while (m != 0 && i != n) {
		mprod = mprod * m;
		numnodes = numnodes + mprod*n;
		i++;
		m = 0;
		//부모(i)가 promising하다면 promising한 child(j)
		for (j = 1; j <=n ; j++) {
			col[i] = j;
			if (promising1(i)) {
				promisingChildSet[m++] = j;
			}
		}
		//유망한 노드가 하나라도 있다면 계속하기: promising한 child(j) 집합 중에서 아무 j 선택
		if (m != 0) {
			col[i] = promisingChildSet[rand() % m];
		}
	}
	return numnodes;
}


// Sum-of-Subsets problem

int include[N] = { 0, }; // w 포함 여부
int w[N] = { 2,10,13,17,22,42 }; // weight list (w1부터)
int W = 52; // target weight

bool promising2(int i, int wsum, int total) {
	return ((wsum + total >= W) && (wsum == W || wsum + w[i + 1] <= W));
}

void sumOfSubsets(int i, int wsum, int total) { // i:index(0부터), wsum: 현재 노드까지의 w의 합
	if (promising2(i, wsum, total)) { 
		if (wsum == W) {
			printf("-> 경로: ");
			for (int k = 1; k <= i; k++) {
				if (include[k] == 1) {
					printf("%d ", w[k]);
				}
				else {
					printf("0 ");
				}
			}
			printf("\n\n");
		}
		else { //wsum + w[i + 1] <= W
			include[i + 1] = 1;
			printf("w[%d]: %d (in) \n", i + 1, w[i + 1]); //과정 출력
			sumOfSubsets(i + 1, wsum + w[i + 1], total - w[i + 1]);
			include[i + 1] = 0;
			printf("w[%d]: %d (out) \n", i + 1, w[i + 1]); //과정 출력
			sumOfSubsets(i + 1, wsum, total - w[i + 1]);
		}
	}
}


// Monte-Carlo estimate (Sum-of-Subsets problem)

int estimate_sumOfSubsets() {
	int i = 0, wsum = 0;
	int m = 1, mprod = 1, numnodes = 1; //m: promising한 child의 개수, numnodes: 노드의 총 개수 추정치
	int total = 0; // 남은 w의 합
	for (int i = 0; i < N; i++) {
		total += w[i];
	}

	while (m != 0 && i != N && wsum!= W) {
		mprod = mprod * m;
		numnodes = numnodes + mprod * 2; // (자식 수: 2)
		m = 0;
		//부모(i)가 promising하다면, promising한 child는 2 (아니면 0개)
		if (promising2(i, wsum, total)) {
			m = 2;
		}
		//부모(i)가 promising하다면, 두 개의 child 중 랜덤으로 'w[i] 추가 여부' 선택 
		if (m != 0) {
			int random = rand() % 2; // 0 또는 1
			if (random) { //rand값이 홀수일 때만 추가함.
				wsum += w[i];
			}
			total -= w[i++];
		}
	}
	return numnodes;
}



int main(void) {

	printf("\n\n[ Q11) Monte Carlo estimate for n-Queens problem ]\n\n");
	int efficiency1, sum1;
	for (int i = sum1 = 0; i < 20; i++) {
		efficiency1 = estimate_nQueens();
		printf("efficiency[%d]: %d\n", i+1, efficiency1);
		sum1 += efficiency1;
	}
	printf("\navg(efficiency): %d\n", (sum1 / 20));

	printf("\n\n[ Q14) Sum-of-Subsets problem ]\n\n");
	int total = 0; // 남은 w의 합
	for (int i = 0; i < N; i++) {
		total += w[i];
	}
	sumOfSubsets(0, 0, total);

	printf("\n\n[ Q17) Monte Carlo estimate for Sum-of-Subsets problem ]\n\n");
	int efficiency2, sum2;
	for (int i = sum2 = 0; i < 20; i++) {
		efficiency2 = estimate_sumOfSubsets();
		printf("efficiency[%d]: %d\n", i+1, efficiency2);
		sum2 += efficiency2;
	}
	printf("\navg(efficiency): %d\n", (sum2 / 20));
}