#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * This file is used for development.  
 *
 * Author: 	George Lancaster
 * Email: 	gl162@brighton.ac.uk
 */

/* Function: swap
 * -------------------
 * Swap two pointers
 *
 * *xp: first pointer
 * *xy: second pointer
 */
void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

/* Function: print_array
 * ----------------------
 * A: array to print
 * size: the number of elements in A
 */
void print_array(int A[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}
 
/*
 * Function: alg_insertionsort
 * ---------------------------
 * Implementation of insertionsort in C
 *
 * arr: unsorted array of integers
 * n: number of items in arr
 *
 */
void alg_insertionsort(int arr[], int n){
	for (int i = 0; i < n; i++){
		int j = i;
		while (j > 0 && arr[j-1] > arr[j]){
			swap(&arr[j], &arr[j-1]);
			j = j-1;
		}
	}
}


/*
 * Function: alg_selectionsort
 * ---------------------------
 * Implementation of insertionsort in C
 *
 * arr: unsorted array of integers
 * n: number of items in arr
 *
 */
void alg_selectionsort(int arr[], int n){
	for (int i = 0; i < n; i++){
		int min = i;
		for (int j = i+1; j < n; j++){
			if (arr[j] <= arr[min]){
				min = j;
			}
		}
		if (min != i){
			swap(&arr[i], &arr[min]);
		}

	}

}

int main(){
	int size = 100;
	int the_arr[size];
	srand(time(NULL));   // should only be called once
	for (int i = 0; i < size; i++){
		the_arr[i] = rand() % 100;
	}

	printf("Unsorted: \n");
	print_array(the_arr, size);
	alg_selectionsort(the_arr, size);
	printf("Sorted: \n");
	print_array(the_arr, size);


	return 0;
}