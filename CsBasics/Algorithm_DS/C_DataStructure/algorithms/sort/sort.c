#include <stdio.h>

void bubble_sort(int arr[], int size) {
	for ( int i = 0; i < size - 1; ++i) {
		_Bool flag = 1;
		for ( int j = 0; j < size - 1 - i; ++j ) {
			if ( arr[j] > arr[j + 1] ) {
				flag = 0;
				int tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
		if (flag) break;
	}
}

void insertion_sort(int arr[], int size) {
	for (int i = 0; i < size; i++) {
		int inserted = arr[i], j = i;
		while (j > 0 && arr[j - 1] > inserted) {
			arr[j] = arr[j - 1];
			j--;
		}
		arr[j] = inserted;
	}
} 

void selection_sort(int arr[], int size) {
	for (int i = 0; i < size - 1; i++) {
		int min = i;
		for ( int j = i; j < size; j++) {
			if (arr[j] < arr[min]) min = j;
		int tmp = arr[min];
		arr[min] = arr[i];
		arr[i] = tmp;
	}
}

void swap(int* a, int* b) {
	int t = *a;
	*a = *b;
	*b = t;
}

void partition(int arr[], int low, int high) {
	int pivot = arr[high];
	int i = low - 1;
	for (int j = low; j <= high - 1; j++) {
		if (arr[j] <= pivot) {
			i++;
			swap(&arr[i], &arr[j]);
		}
	}

	swap(&arr[i + 1], &arr[high]);
	return i + 1;
}

void quick_sort(int arr[], int low, int high) {
	if (low < high) {
		int pi = partition(arr, low, high);

		quick_sort(arr, low, pi - 1);
		quick_sort(arr, pi + 1, high);
	}
} 	
