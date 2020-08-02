#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "Header.h"

#pragma warning(disable:4996)


/* 简单插入排序 */

void Swap(ElementType * a, ElementType * b) {   /* 位置交换函数 */

	ElementType  t;

	t = *a;
	*a = *b;
	b = t;

}


void SimpleSelectionSort(ElementType A[], int N) {  // 形参为数组A[N]

	int min;

	for (int i = 0; i < N - 1; i++) {

		min = i;

		for (int j = i + 1; j < N; j++) {

			if (A[j] < A[min]) {

				min = j;

			}

		}

		if (min != i) {  // 最小元素不是A[i]

			Swap(&A[i], &A[min]);

		}

	}

}


/* 堆排序 */

void PercDown(ElementType A[], int p, int N) {  // 下滤

	int Parent, Child;
	ElementType X;

	X = A[p];

	for (Parent = p; (Parent * 2 + 1) <= N; Parent = Child) {

		Child = Parent * 2 + 1;   /* 先指向左子树 */

		if ((Child != N - 1) && (A[Child] < A[Child + 1])) {  // 若不是最后一个元素且左子树小于右子树

			Child++;    /* 调整，指向较大子树 */

		}

		if (X >= A[Child]) {

			break;

		}
		else {

			A[Parent] = A[Child];

		}

	}

	A[Parent] = X;

}


void HeapSort(ElementType A[], int N) {

	int i;

	for (i = N / 2 - 1; i >= 0; i--) {  //  创建最大堆

		PercDown(A, i, N);

	}

	for (i = N - 1; i >= 0; i--) {   // 从顶开始下滤

		Swap(&A[0], &A[i]);  // 将每次形成的最大堆顶元素与每次调整后所对应的位置自减的尾元素交换
		PercDown(A, 0, i);

	}

}


/* 插入排序 */

void InsertionSortIDo(ElementType A[], int N) {

	int i, j, k;

	for (i = 0; i < N ; i++) {

		for (j = i + 1; j < N; j++) {

			if (A[j] < A[i]) {

				Swap(&A[i + 1], &A[j]);

				for (k = i + 1; k >= 1; k--) {

					if (A[k] < A[k - 1]) {

						Swap(&A[k], &A[k - 1]);

					}

				}

			}
			else {

				break;

			}

		}

	}

}


void InsertionSort(ElementType A[], int N) {

	int p, i;
	ElementType temp;

	for (p = 1; p < N; p++) {

		temp = A[p];  /* 取出未排序序列的第一个元素 */

		for (i = p; i > 0 && A[i - 1] > temp; i--) {  /* 依次与已排序序列中的元素比较并右移 */

			A[i] = A[i - 1];

		}

		A[i] = temp;  // 找到合适位置，插入

	}

}


/* 希尔排序 */

void ShellSort(ElementType A[], int N) {

	int Si, D, P, i;
	ElementType temp;

	// int Sedgewick[] = { 929, 505, 209, 109, 41, 19, 5, 1, 0 };

	int Sedgewick[] = {5, 3, 1};

	for (Si = 0; Sedgewick[Si] >= N; Si++);  /* 初始增量序列Sedgewick[Si]不能超过待排序序列长度 */

	for (D = Sedgewick[Si]; D > 0; D = Sedgewick[++Si]) {

		for (P = D; P < N; P++) {  /* 插入排序 */

			temp = A[P];

			for (i = P; i >= D && A[i - D] > temp; i -= D) {

				A[i] = A[i - D];

			}

			A[i] = temp;

		}

	}

}


/* 冒泡排序 */

void BubbleSortIDo(ElementType A[], int N) {   /* 第 1 次排序, 将第 1 大的元素移到下标为 N - 1 的位置上去
											      第 2 次排序, 将第 2 大的元素移到下标为 N - 2 的位置上去 
											      第 N - 1 次排序, 将第 N - 1 大的元素移到下标为 1 的位置上去 */
	int i, j;
	
	ElementType temp;

	for (i = 0; i < N - 1 ; i++) {

		for (j = i; j < N - 1 - i; j++) {

			if (A[j] > A[j + 1]) {

				temp = A[j];
				A[j] = A[j + 1];
				A[j + 1] = temp;

				/* Swap(&A[j], &A[j + 1]); */

			}

		}

	}

}


void BubbleSort(ElementType A[], int N) {

	int P, i;

	bool flag;

	for (P = N - 1; P >= 0; P--) {

		flag = False;  /* 用于判断是否在到达第 N - 1 次比较前, 就已整体有序 */

		for (i = 0; i < P; i++) {  /* 一趟冒泡 */

			if (A[i] > A[i + 1]) {

				Swap(&A[i], &A[i + 1]);
				flag = True;

			}

			if (flag == False) {  /* 若有一次整体均未发生交换, 则说明整体有序, 直接跳出 */

				break;

			}

		}

	}

}


/* 快速排序 */

ElementType Median3(ElementType A[], int left, int right) {  // 为避免最坏时间复杂度的情况, 将主元确定为左、右、中三者数值大小的中位数值

	int center;
	center = (left + right) / 2;

	if (A[left] > A[right]) {

		Swap(&A[left], &A[right]);

	}

	if (A[center] > A[right]) {

		Swap(&A[center], &A[right]);

	}

	if (A[left] > A[center]) {

		Swap(&A[left], &A[center]);

	}

	Swap(&A[center], &A[right - 1]);

	return A[right - 1];   // 返回主元

}


  /* 核心递归函数 */
void QSort(ElementType A[], int left, int right) {  /* 由于快速排序用递归实现, 所以在递归过程中检查子列的规模, 当问题规模 < 阈值, 改为采用插入排序 */

	int Pivot, Low, High;

	if (right - left >= CUTOFF) {   /* 序列元素充分多 */

		Pivot = Median3(A, left, right);
		Low = left - 1; 
		High = right - 2;

		while (1) {   /* 将序列中比基准主元小的移到基准左边, 大的移到右边 */

			while (A[Low++] < Pivot);    
			while (A[High--] < Pivot);   

			if (Low < High) {  /* 若未错位且两指针均停止移动, 则交换 */

				Swap(&A[Low], &A[High]);

			}
			else {  /* 有错位, 跳出, 重置主元 */

				break;

			}

		}

		Swap(&A[Low], &A[right - 1]);   /* 错位, 与主元交换 */
		QSort(A, left, Low - 1);   /* 递归完成左边 */
		QSort(A, Low + 1, right);   /* 递归完成右边 */

	}
	else {   /* 元素太少, 用简单排序 */

		InsertionSort(A + left, right - left + 1);

	}

}


void QuickSort(ElementType A[], int N) {   /* 对外接口一致 */

	QSort(A, 0, N -1);

}


/* 归并排序 */

void Merge(ElementType A[], ElementType tempA[], int left, int right, int rightEnd) {

	int leftEnd, NumberElements, temp;

	int i;

	leftEnd = right - 1;
	temp = left;

	NumberElements = rightEnd - left + 1;

	while (left <= leftEnd && right <= rightEnd) {

		if (A[left] <= A[right]) {

			tempA[temp++] = A[left++];

		}
		else {

			tempA[temp++] = A[right];

		}

	}

	while (left <= leftEnd) {

		tempA[temp++] = A[left++];

	}

	while (right <= rightEnd) {

		tempA[temp++] = A[right++];

	}

	for (i = 0; i < NumberElements; i++, rightEnd-- ) {

		A[rightEnd] = tempA[rightEnd];

	}

}


  /* 核心递归排序函数 */
void MSort(ElementType A[], ElementType tempA[], int left, int rightEnd) {

	int center;

	if (left < rightEnd) {

		center = (left + rightEnd) / 2;
		MSort(A, tempA, left, center);    /* 递归完成左侧 */
		MSort(A, tempA, center + 1, rightEnd);   /* 递归完成右侧 */
		MSort(A, tempA, center + 1, rightEnd);   /* 合并两段子序列 */

	}

}


  /* 归并排序 */
void MergeSort(ElementType A[], int N) {

	ElementType * tempA;
	tempA = (ElementType *)malloc(N * ESIZE);

	if (tempA != NULL) {

		MSort(A, tempA, 0, N - 1);
		free(tempA);

	} else {

		printf("\n空间不足\n");

	}

}


/* 基数排序 */

int getDigit(int X, int D) {   /* 获取数字 */

	int d, i;

	for (i = 1; i <= D; i++) {

		d = X % RADIX;
		X /= RADIX;

	}

	return d;

}


void LSDRadixSort(ElementType A[], int N) {   /* 基数排序, 次位优先 */

	int D, Di, i;

	Bucket B;

	Npointer temp, p, list = NULL;

	for (i = 0; i < RADIX; i++) {   /* 初始化每个桶为空链表 */

		B[i].head = B[i].tail = NULL;

	}
    
	for (i = 0; i < N; i++) {   /* 将初始化序列逆序存入初始链表list */

		temp = (Npointer)malloc(NSIZE);
		temp->key = A[i];
		temp->next = list;
		list = temp;

	}

	 /* 排序 */
	for (D = 1; D <= MAXDIGIT; D++) {   /* 对数据的每一位循环处理 */

		p = list;

		while (p != NULL) {

			Di = getDigit(p->key, D);

			temp = p; 
			p = p->next;
			temp->next = NULL;

			if (B[Di].head == NULL) {

				B[Di].head = B[Di].tail = temp;

			}
			else {

				B[Di].tail->next = temp;   /* 将结点接到链表上 */
				B[Di].tail = temp;         /* 将尾指针移到最后 */

			}

		}


		list = NULL;

		for (Di = RADIX - 1; Di >= 0; Di--) {

			if (B[Di].head != NULL) {  /* 不为空 */

				B[Di].tail->next = list;    /* 除第一次外, 每次将从后一个桶中的整体链表, 链接到前一个桶的尾部 */
				list = B[Di].head;     /* 将一个桶中的链表元素接到list链上 */
				B[Di].head = B[Di].tail = NULL;    /* 清空桶 */

			}

		}

	}


	for (i = 0; i < N; i++) {    /* 将list倒入A[]并释放空间 */

		temp = list;
		list = list->next;
		A[i] = temp->key;
		free(temp);

	}

}


void Run(void(*Sort)(ElementType *, int), ElementType a[], int N, char name[]) {

	int i;

	start = clock();

	for (i = 0; i < MAXK; i++) {

		(*Sort)(a, N);

	}

	stop = clock();

	duration = (double)(stop - start) / CLK_TCK;

	printf("%s 用时: %fms\n", name, duration);

}

