#include <stdio.h>
#include<stdlib.h>


struct list {
    int size;
    int array[];
};


// Memory allocation and initialisation of structure
struct list *create_list(struct list *l, int arr_size, int arr[])
{
    // Allocating memory according to user provided
    // array of characters
    l = malloc( sizeof(*l) + sizeof(int) * arr_size);
    l->size = arr_size;
    return l;
}
 





void function(int the_array[], int n){
	for (int j = 0; j < n; j++){
		the_array[j] = 1;
	}
}








int main(){

	int arr[] = {1,2,3,4,5,6,7,8,9,10};
	int n = sizeof(arr) / sizeof(arr[0]);


	struct list *s1 = create_list(s1, n, arr);



	
	for (int i = 0; i < n; i++){
		printf("%d", arr[i]);
	}
	printf("\n");
	

	int the_size = s1->size;
	printf("size: %d\n", the_size);

	int new_arr[n];
	for (int j = 0; j < the_size; j++){
		new_arr[j] = s1.array[j];
	}
	for (int k = 0; k < the_size; k++){
		printf("new arr: %d\n", new_arr[k]);
	}



	return 0;
}