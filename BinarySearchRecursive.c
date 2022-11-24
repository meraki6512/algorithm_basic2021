#define _CRT_SECURE_NO_WARNINGS //scanf ���� ����
#include <stdio.h> // �����
#include <malloc.h> // �����Ҵ�

int binarySearchRecurse(int i, int n, int array[], int key) { //��͸� Ȱ���� ����Ž���ϴ� �Լ�
	int mid = (i + n) / 2; //mid: ����i�� ��n�� �߰� ���� (����ϸ� �ٲ� i�� �Ǵ� n���� ���� mid�� ����) 
	if (i > n) { //1) key���� ã�� ���� ���, -1 ���� (����)
		return -1;
	}
	if (key == array[mid]) { //2) key�� mid�ε����� array�� ��ġ�ϴ� ���, ����
		return mid;
	}
	else { //3) key�� mid�ε����� array�� ���� �ٸ� ���:
		if (key < array[mid]) { //(1) key�� mid�ε����� array���� ���� ���, ������ mid-1�� ����
			n = mid - 1;
		}
		else if (key > array[mid]) { //(2) key�� mid�ε����� array���� Ŭ ���, ���۰��� mid+1�� ����
			i = mid + 1;
		}
		return binarySearchRecurse(i, n, array, key); //(3) ���
	}
}

int main(void) {

	//1. �Է�
	int n, key; //n:���ĵȹ迭�Ǽ��ڰ���, key:ã�����ϴ°�
	scanf("%d", &n); //n �Է�
	int* array = (int*)malloc((sizeof(int) * n) + 1); //array: ũ��(n)�� �����Ӱ� �Է¹ޱ� ���� �����Ҵ��ϰ� �迭ó�� ���
	for (int i = 0; i < n; i++) { //array �Է�
		scanf("%d", &array[i]);
	}
	scanf("%d", &key); //key �Է�

	//2. ���
	int result = binarySearchRecurse(0, n-1, array, key) + 1; //�迭�ε����� ����� Ž������ n-1��, result�� ���ϰ�+1�� ����
	if (result != 0) { //�ε����� 0�� �ƴ� ���, result ��� (result: key�� ��ġ�ϴ� �迭�� �ε���)
		printf("%d", result);
	}
	else { //�ε����� 0�� ���, "����" ��� (key�� ��ġ�ϴ� ���� ���� ���)
		printf("����");
	}

	//3. ��
	free(array); //array �޸� ����
	return 0;

}