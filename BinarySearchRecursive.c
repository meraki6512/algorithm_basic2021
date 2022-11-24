#define _CRT_SECURE_NO_WARNINGS //scanf 에러 방지
#include <stdio.h> // 입출력
#include <malloc.h> // 동적할당

int binarySearchRecurse(int i, int n, int array[], int key) { //재귀를 활용해 이진탐색하는 함수
	int mid = (i + n) / 2; //mid: 시작i와 끝n의 중간 지점 (재귀하며 바뀐 i값 또는 n값에 따라 mid값 변경) 
	if (i > n) { //1) key값을 찾지 못한 경우, -1 리턴 (실패)
		return -1;
	}
	if (key == array[mid]) { //2) key와 mid인덱스의 array가 일치하는 경우, 리턴
		return mid;
	}
	else { //3) key와 mid인덱스의 array가 서로 다른 경우:
		if (key < array[mid]) { //(1) key가 mid인덱스의 array보다 작을 경우, 끝값을 mid-1로 지정
			n = mid - 1;
		}
		else if (key > array[mid]) { //(2) key가 mid인덱스의 array보다 클 경우, 시작값을 mid+1로 지정
			i = mid + 1;
		}
		return binarySearchRecurse(i, n, array, key); //(3) 재귀
	}
}

int main(void) {

	//1. 입력
	int n, key; //n:정렬된배열의숫자개수, key:찾고자하는값
	scanf("%d", &n); //n 입력
	int* array = (int*)malloc((sizeof(int) * n) + 1); //array: 크기(n)를 자유롭게 입력받기 위해 동적할당하고 배열처럼 사용
	for (int i = 0; i < n; i++) { //array 입력
		scanf("%d", &array[i]);
	}
	scanf("%d", &key); //key 입력

	//2. 출력
	int result = binarySearchRecurse(0, n-1, array, key) + 1; //배열인덱스를 고려해 탐색끝을 n-1로, result를 리턴값+1로 지정
	if (result != 0) { //인덱스가 0이 아닌 경우, result 출력 (result: key와 일치하는 배열의 인덱스)
		printf("%d", result);
	}
	else { //인덱스가 0인 경우, "실패" 출력 (key와 일치하는 수가 없는 경우)
		printf("실패");
	}

	//3. 끝
	free(array); //array 메모리 해제
	return 0;

}