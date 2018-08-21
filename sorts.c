#include <Python.h>



int array_size; /* Keep track of the size of the array */ 




/* Test functions */
static char helloworld_docs[] = "helloworld( ): Any message you want to put here!!\n";

static PyObject* helloworld(PyObject* self) {
   return Py_BuildValue("s", "Hello, Python extensions!!");
}

/* Print a single integer */ 
static PyObject *test_func(PyObject *self, PyObject *args) {
	int result;

	if(!PyArg_ParseTuple(args, "i", &result)){
		return NULL;
	}
	printf("single integer: %d\n",result );
	Py_RETURN_NONE;
}





/**********************************************************************/
/**************************** Helper Functions ************************/
/**********************************************************************/

/* function to swap two pointers */ 
void swap(int *xp, int *yp){
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

/* generate a list of int from a PyObject */ 
int * list_gen(PyObject * args){
	PyObject * list_obj; /* the list of strings */
	int num_items;       /* how many lines we passed for parsing */
	PyObject * int_obj;  /* one string in the list */

	/* Parse PyObject as list_obj "O!" */
	if (! PyArg_ParseTuple( args, "O!", &PyList_Type, &list_obj)){
	 	return NULL;
	}

	num_items = PyList_Size(list_obj);
	array_size = num_items;
	if (num_items < 0){
		return NULL; /* Not a list */
	}   
	int *my_list = malloc (sizeof (int) * num_items);
	int i; 
	for (i=0; i<num_items; i++){
		int_obj = PyList_GetItem(list_obj, i);
		/* check all items are int */
		if(!PyInt_Check(int_obj)){
			return NULL;
		}
		my_list[i] = PyFloat_AsDouble(int_obj);
	}
	return my_list;
}


/* Create a PyList object to be returned to python */ 
PyObject * create_pylist(int arr[], int num_items){
	PyObject* python_val = PyList_New(num_items);
    for (int j = 0; j < num_items; ++j)
    {
        PyObject* python_int = Py_BuildValue("i", arr[j]);
        PyList_SetItem(python_val, j, python_int);
    }
    return python_val;

}






/**********************************************************************/
/**************************** Bubble sort *****************************/
/**********************************************************************/

static char bubblesort_docs[] = "Bubble sort implementation in C";


// A function to implement bubble sort
void alg_bubblesort(int arr[], int n){
   int i, j;
   for (i = 0; i < n-1; i++)      
 
       // Last i elements are already in place   
       for (j = 0; j < n-i-1; j++) 
           if (arr[j] > arr[j+1])
              swap(&arr[j], &arr[j+1]);
}

static PyObject *bubble_sort(PyObject *self, PyObject *args) {
	PyObject * list_obj; /* the list of strings */
	int num_items;       /* how many lines we passed for parsing */
	PyObject * int_obj;  /* one string in the list */

	/* Parse PyObject as list_obj "O!" */
	if (! PyArg_ParseTuple( args, "O!", &PyList_Type, &list_obj)){
	 	return NULL;
	}

	num_items = PyList_Size(list_obj);
	if (num_items < 0){
		return NULL; /* Not a list */
	}   

	int my_list[num_items];
	int i; 
	for (i=0; i<num_items; i++){
		int_obj = PyList_GetItem(list_obj, i);
		/* check all items are int */
		if(!PyInt_Check(int_obj)){
			Py_RETURN_NONE;
		}
		my_list[i] = PyFloat_AsDouble(int_obj);
	}

	alg_bubblesort(my_list, num_items);

	PyObject* python_val = PyList_New(num_items);
    for (int j = 0; j < num_items; ++j)
    {
        PyObject* python_int = Py_BuildValue("i", my_list[j]);
        PyList_SetItem(python_val, j, python_int);
    }
    return python_val;
}

/*********************************************************************/
/**************************** Quick sort *****************************/
/*********************************************************************/

static char quicksort_docs[] = "Quick sort implementation in C";

// Function to run quicksort on an array of integers
// l is the leftmost starting index, which begins at 0
// r is the rightmost starting index, which begins at array length - 1
void alg_quicksort(int arr[], int l, int r)
{
    // Base case: No need to sort arrays of length <= 1
    if (l >= r)
    {
        return;
    }
    
    // Choose pivot to be the last element in the subarray
    int pivot = arr[r];

    // Index indicating the "split" between elements smaller than pivot and 
    // elements greater than pivot
    int cnt = l;

    // Traverse through array from l to r
    for (int i = l; i <= r; i++)
    {
        // If an element less than or equal to the pivot is found...
        if (arr[i] <= pivot)
        {
            // Then swap arr[cnt] and arr[i] so that the smaller element arr[i] 
            // is to the left of all elements greater than pivot
            swap(&arr[cnt], &arr[i]);

            // Make sure to increment cnt so we can keep track of what to swap
            // arr[i] with
            cnt++;
        }
    }
    
    // NOTE: cnt is currently at one plus the pivot's index 
    // (Hence, the cnt-2 when recursively sorting the left side of pivot)
    alg_quicksort(arr, l, cnt-2); // Recursively sort the left side of pivot
    alg_quicksort(arr, cnt, r);   // Recursively sort the right side of pivot
}



static PyObject *quick_sort(PyObject *self, PyObject *args){
	int *p; /* pointer to an int, will be an array */
	PyObject *list;
	p = list_gen(args);
	alg_quicksort(p, 0, array_size);
	list = create_pylist(p, array_size);
	return list;
}



static PyObject *list_generator(PyObject *self, PyObject *args){
	int *p; /* pointer to an int, will be an array */
	PyObject *list;
	p = list_gen(args);
	list = create_pylist(p, array_size);
	return list;
}





/* Python method declarations*/
static PyMethodDef helloworld_funcs[] = {
   {"helloworld", (PyCFunction)helloworld, METH_NOARGS, helloworld_docs},
   {"read_num", (PyCFunction) test_func, METH_VARARGS, NULL},
   {"bubble_sort", (PyCFunction) bubble_sort, METH_VARARGS, bubblesort_docs},
   {"quick_sort", (PyCFunction) quick_sort, METH_VARARGS,quicksort_docs},
   {"list_gen", (PyCFunction) list_generator, METH_VARARGS, NULL},
   { NULL, NULL, 0, NULL }
};

void inithelloworld(void) {
   Py_InitModule3("helloworld", helloworld_funcs,
                  "Extension module example!");
}