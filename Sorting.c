# define SIZE 8
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

/*
 * 프로그램 설명
 * 선택정렬, 버블정렬, 삽입정렬, 병합정렬, 퀵정렬, 힙정렬 구현
 * rand(seed) 함수를 이용하여 n=8개의 –1 ~ 1 사이의 값 출력
 * 1)의 값을 이용해 정렬 알고리즘별로 결과 출력
 * n=1000, 2000, ...... , 20,000까지 1000씩 증가시키면서 정렬하는 입력 값의 개수를 변경하면서 각 정렬 알고리즘의 수행 시간을 msec 까지 측정
 * 알고리즘 비교
*/

// 0-0) 정렬된 배열 출력
void printArray(double array[]) {
	for (int i = 0; i < SIZE; i++) {
		printf("%.3f ", array[i]);
	}
	printf("\n");
}

// 0-1) 배열 되돌리기
double original[SIZE];
double array[SIZE];
void copyArr(void){
	int i;
	for (i = 0; i < SIZE; i++) {
		array[i] = original[i];
	}
}

// 1) 선택정렬
void selectionSort(double array[]) {
	printf("[ 선택정렬 ]\n");
	printf("정렬 전: ");
	printArray(array);
	int max;
	for (int i = 0; i < SIZE; i++) {
		max = 0;
		for (int j = 1; j < SIZE - i; j++) {
			if (array[max] < array[j]) {
				max = j;
			}
		}
		double tmp = array[max];
		array[max] = array[SIZE - i - 1];
		array[SIZE - i - 1] = tmp;
		//출력
		if (i < 2) {
			printf("\tstep%d) (max 위치:%d, 값:%.3f) ", i + 1, max + 1, tmp);
			printArray(array);
		}
	}
	printf("정렬 후: ");
	printArray(array);
	printf("\n");
	return;
}

// 2) 버블정렬
void bubbleSort(double array[]) {
	printf("[ 버블정렬 ]\n");
	printf("정렬 전: ");
	printArray(array);
	for (int i = 0; i < SIZE; i++) {
		for (int j = 1; j < SIZE - i; j++) {
			if (array[j - 1] > array[j]) {
				double tmp = array[j];
				array[j] = array[j - 1];
				array[j - 1] = tmp;
			}
		}
		//출력
		if (i < 2) {
			printf("\tstep %d) ", i + 1);
			printArray(array);
		}
	}
	printf("정렬 후: ");
	printArray(array);
	printf("\n");
	return;
}

// 3) 삽입정렬
void insertionSort(double array[]) {
	printf("[ 삽입정렬 ]\n");
	printf("정렬 전: ");
	printArray(array);
	for (int i = 0; i < SIZE - 1; i++) {
		for (int j = i + 1; j > 0; j--) {
			if (array[j] < array[j - 1]) {
				double tmp = array[j];
				array[j] = array[j - 1];
				array[j - 1] = tmp;
			}
		}
		//출력
		if (i < 2) {
			printf("\tstep %d) ", i + 1);
			printArray(array);
		}
	}
	printf("정렬 후: ");
	printArray(array);
	printf("\n");
	return;
}

// 4) 병합정렬
double tmpArray[SIZE];
int tmpCount1 = 0;
void merge(double array[], int from, int mid, int to) {
	int i = from;
	int j = mid + 1;
	int k = from;
	//순차적으로 선택된 경우
	while (i <= mid && j <= to) {
		if (array[i] <= array[j]) {
			tmpArray[k++] = array[i++]; //i선택
		}
		else {
			tmpArray[k++] = array[j++]; //j선택
		}
	}
	//남은 경우
	if (i > mid) { //왼쪽 배열이 먼저 다 선택된 경우
		for (int t = j; t <= to; t++) {
			tmpArray[k++] = array[t];
		}
	}
	else { //오른쪽 배열이 먼저 다 선택된 경우
		for (int t = i; t <= mid; t++) {
			tmpArray[k++] = array[t];
		}
	}
	//임시 배열 저장
	for (int t = from; t <= to; t++) {
		array[t] = tmpArray[t];
	}
	//출력
	if (tmpCount1 < 5) {
		printf("\tstep %d) ", ++tmpCount1);
		printArray(array);
	}
}
void mergeSort(double array[], int from, int to) {
	if (from < to) {
		int mid = (from + to) / 2;
		mergeSort(array, from, mid);
		mergeSort(array, mid + 1, to);
		merge(array, from, mid, to);
	}
}

// 5) 퀵정렬
int tmpCount2 = 0;
int partition(double array[], int from, int to) {
	int i = from + 1;
	int j = to;
	int pivot = from;
	while (i <= j) {
		while (i <= to && array[i] <= array[pivot]) {
			i++;
		}
		while (j > from && array[j] > array[pivot]) {
			j--;
		}
		if (i <= j) {
			double tmp = array[i];
			array[i] = array[j];
			array[j] = tmp;
		}
	}
	double tmp = array[j];
	array[j] = array[pivot];
	array[pivot] = tmp;
	//출력
	if (tmpCount2 < 5) {
		printf("\tstep %d) (pivot 위치:%d, 값:%.3f) ", ++tmpCount2, j + 1, array[j]);
		printArray(array);
	}
	return j;
}
void quickSort(double array[], int from, int to) {
	if (from < to) {
		int pivot = partition(array, from, to);
		quickSort(array, from, pivot - 1);
		quickSort(array, pivot + 1, to);
	}
}

// 6) 힙정렬
int tmpCount3 = 0;
void buildHeap(double array[], int num) {
	for (int i = 1; i < num; i++) {
		int child = i;
		while (child > 0) {
			int root = (child - 1) / 2;
			if (array[root] < array[child]) {
				double tmp = array[root];
				array[root] = array[child];
				array[child] = tmp;
			}
			child = root;
		}
	}
}
void heapSort(double array[], int num) {
	buildHeap(array, num);
	for (int i = num - 1; i >= 0; i--) {
		double tmp = array[i];
		array[i] = array[0];
		array[0] = tmp;
		buildHeap(array, i);
		//출력
		if (tmpCount3 < 5) {
			printf("\tstep %d) ", ++tmpCount3);
			printArray(array);
		}
	}
}

// 7) 결과 출력
void printSelectionSort() {
	copyArr();
	selectionSort(array);
}
void printBubbleSort() {
	copyArr();
	bubbleSort(array);
}
void printInsertionSort() {
	copyArr();
	insertionSort(array);
}
void printMergeSort() {
	copyArr();
	printf("[ 병합정렬 ]\n");
	printf("정렬 전: ");
	printArray(array);
	mergeSort(array, 0, SIZE - 1);
	printf("정렬 후: ");
	printArray(array);
	printf("\n");
}
void printQuickSort() {
	copyArr();
	printf("[ 퀵정렬 ]\n");
	printf("정렬 전: ");
	printArray(array);
	quickSort(array, 0, SIZE - 1);
	printf("정렬 후: ");
	printArray(array);
	printf("\n");
}
void printHeapSort() {
	copyArr();
	printf("[ 힙정렬 ]\n");
	printf("정렬 전: ");
	printArray(array);
	heapSort(array, SIZE);
	printf("정렬 후: ");
	printArray(array);
	printf("\n");
}

int main(void) {

	printf("[랜덤 배열]: ");
	double m = 32767 / 2;
	double array[8];
	for (int i = 0; i < 8; i++) {
		double r = rand() / m - 1;
		printf("%.3f ", r);
		original[i] = r;
	}
	printf("\n");

	printf("[정렬 결과]\n");
	printSelectionSort();
	printBubbleSort();
	printInsertionSort();
	printMergeSort();
	printQuickSort();
	printHeapSort();

}


