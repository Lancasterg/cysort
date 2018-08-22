#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * This file is used for development.  
 *
 * Author: 	George Lancaster
 * Email: 	gl162@brighton.ac.uk
 */

void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

/* Function to print an array */
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


int main(){
	int size = 100;
	int the_arr[size];
	srand(time(NULL));   // should only be called once

	for (int i = 0; i < size; i++){
		the_arr[i] = rand() % 100;
	}

	printf("unsorted\n");
	print_array(the_arr, size);
	alg_insertionsort(the_arr, size);
	print_array(the_arr, size);


	return 0;
}