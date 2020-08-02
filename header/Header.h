#pragma once

#define MAXDATA 1e9
#define ERROR -1
#define ESIZE sizeof(ElementType)

#define CUTOFF 100

#define MAXDIGIT 2
#define RADIX 10

#define NSIZE sizeof(struct Node)

typedef int ElementType;
typedef int bool;

typedef double ResultType;

#define MAXK 10e6  /* 测试函数重复调用次数 */
clock_t start, stop;   /* 起始时间与结束时间 */
double duration;    /* 用时 */


typedef enum Status {

	False = 0,
	True

} Status;


typedef struct Node {

	int key;
	struct Node * next;

} Node, * Npointer;


typedef struct HeadNode {

	Npointer head, tail;

} Bucket[RADIX];


void Swap(ElementType * a, ElementType * b);
void SimpleSelectionSort(ElementType A[], int N);  /* 直接选择排序, 不稳定 */

void PercDown(ElementType A[], int p, int N);
void HeapSort(ElementType A[], int N);      /* 堆排序, 不稳定 */

void InsertionSortIDo(ElementType A[], int N);
void InsertionSort(ElementType A[], int N);   /* 插入排序, 稳定 */

void ShellSort(ElementType A[], int N);   /* 希尔排序, 不稳定 */

void BubbleSortIDo(ElementType A[], int N);   /* 冒泡排序, 稳定 */
void BubbleSort(ElementType A[], int N);

ElementType Median3(ElementType A[], int left, int right);
void QSort(ElementType A[], int left, int right);   /* 快速排序, 不稳定 */
void QuickSort(ElementType A[], int N);

void Merge(ElementType A[], ElementType tempA[], int left, int right, int rightEnd);
void MSort(ElementType A[], ElementType tempA[], int left, int rightEnd);    /* 归并排序, 稳定, 更适合于外部排序 */
void MergeSort(ElementType A[], int N);

int getDigit(int X, int D);
void LSDRadixSort(ElementType A[], int N);    /* 基数排序, 稳定 */

void Run(void (* Sort)(ElementType * , int),  ElementType a[], int N, char name[]);  /* 时间测试函数 */