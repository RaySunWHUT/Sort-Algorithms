#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include "Header.h"

#pragma warning(disable:4996)


int main() {

	int i;
	
	ElementType a[10] = {23, 19, 42, 33, 57, 12, 8, 66, 81, 99};
	
	int N = 10;

	char * names[] = {"简单选择排序", "堆排序", "插入排序", "希尔排序", "冒泡排序", "快速排序", "归并排序", "基数排序"};

	Run(SimpleSelectionSort, a, N, names[0]);
	Run(HeapSort, a, N, names[1]);
	Run(InsertionSort, a, N, names[2]);
	Run(ShellSort, a, N, names[3]);  
	Run(BubbleSort, a, N, names[4]);
	Run(QuickSort, a, N, names[5]);
	Run(MergeSort, a, N, names[6]);
	Run(LSDRadixSort, a, N, names[7]);

	return 0;

}
