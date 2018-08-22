#include <Python.h>

/*
 * Cysort module 
 * Author: 	George Lancaster
 * Email: 	gl162@brighton.ac.uk
 */

/* Keep track of the size of the array */
int array_size; 


/**********************************************************************/
/**************************** Helper Functions ************************/
/**********************************************************************/

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

/*
 * Function: list_gen
 * ---------------------
 * Generate a list of integers from a PyObject
 *
 * PyObject: Arguments parsed by Python
 *
 * Returns: List of integers
 *
 */
int * list_gen(PyObject * args) {
    PyObject * list_obj; /* the list of strings */
    int num_items;       /* how many lines we passed for parsing */
    PyObject * int_obj;  /* one string in the list */

    /* Parse PyObject as list_obj "O!" */
    if (! PyArg_ParseTuple( args, "O!", &PyList_Type, &list_obj)) {
        return NULL;
    }

    num_items = PyList_Size(list_obj);
    array_size = num_items;
    if (num_items < 0) {
        return NULL; /* Not a list */
    }
    int *my_list = malloc (sizeof (int) * num_items);
    int i;
    for (i=0; i<num_items; i++) {
        int_obj = PyList_GetItem(list_obj, i);
        /* check all items are int */
        if(!PyInt_Check(int_obj)) {
            return NULL;
        }
        my_list[i] = PyFloat_AsDouble(int_obj);
    }
    return my_list;
}


/*
 * Function: create_pylist
 * ----------------------------
 * Create a PyList object to be returned to python 
 *
 * arr: array of C integers
 * num_items: number of items in arr
 *
 * Returns: PyObject list
 */
PyObject * create_pylist(int arr[], int num_items) {
    PyObject* python_val = PyList_New(num_items);
    for (int j = 0; j < num_items; ++j)
    {
        PyObject* python_int = Py_BuildValue("i", arr[j]);
        PyList_SetItem(python_val, j, python_int);
    }
    return python_val;

}

/*
 * Function: list_generator
 * ---------------------------
 * Boilerplate Python function call
 *
 * *self: pointer to self
 * *args: pointer to args passed by Python 
 *
 */
static PyObject *list_generator(PyObject *self, PyObject *args) {
    int *p; /* pointer to an int, will be an array */
    PyObject *list;
    p = list_gen(args);
    list = create_pylist(p, array_size);

    return list;
}





/**********************************************************************/
/**************************** Bubble sort *****************************/
/**********************************************************************/

/* Bubblesort documentation */ 
static char bubblesort_docs[] = "Bubble sort implementation in C";


/*
 * Function: alg_bubblesort
 * -------------------------
 * Bubblesort implementation
 *
 * arr: unsorted array of integers
 * n: number of items in arr
 *
 */
void alg_bubblesort(int arr[], int n) {
    int i, j;
    for (i = 0; i < n-1; i++)

        // Last i elements are already in place
        for (j = 0; j < n-i-1; j++)
            if (arr[j] > arr[j+1])
                swap(&arr[j], &arr[j+1]);
}

/*
 * Function: bubble_sort
 * ----------------------------
 * Bubblesort function called by Python
 * 
 * *self: pointer to self
 * *args: pointer to args passed by Python 
 */
static PyObject *bubble_sort(PyObject *self, PyObject *args) {
	int *p; /* pointer to an int, will be an array */
    PyObject *list;
    p = list_gen(args);
    alg_bubblesort(p, array_size);

    list = create_pylist(p, array_size);
    return list;
}

/*********************************************************************/
/**************************** Quick sort *****************************/
/*********************************************************************/

/* quicksort documentation */ 
static char quicksort_docs[] = "Quick sort implementation in C";


/*
 * Function: alg_quicksort
 * -------------------------
 * Implementation of a quicksort algorithm 
 *
 * arr: array to be sorted
 * l: leftmost point
 * r: rightmost point
 *
 */
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


/*
 * Function: quick_sort
 * -----------------------
 * Quicksort function called by Python 
 *
 * *self: pointer to self
 * *args: pointer to args passed by Python 
 *
 */
static PyObject *quick_sort(PyObject *self, PyObject *args) {
    int *p; /* pointer to an int, will be an array */
    PyObject *list;
    p = list_gen(args);
    alg_quicksort(p, 0, array_size);
    list = create_pylist(p, array_size);
    return list;
}


/*********************************************************************/
/**************************** Insertion sort *************************/
/*********************************************************************/

static char insertionsort_docs[] = "Insertion sort implementation in C";

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
 * Function: insertion_sort
 * ---------------------------
 * Insertion sort function called by Python
 *
 * *self: pointer to self
 * *args: pointer to args passed by Python 
 *
 */
static PyObject *insertion_sort(PyObject *self, PyObject *args) {
	int *c_array; /* pointer to an int, will be an array */
	PyObject *list;
	c_array = list_gen(args);
	alg_insertionsort(c_array, array_size);
	list = create_pylist(c_array, array_size);
	return list;
}



/* Python method declarations*/
static PyMethodDef cysort_funcs[] = {
    {"bubble_sort", (PyCFunction) bubble_sort, METH_VARARGS, bubblesort_docs},
    {"quick_sort", (PyCFunction) quick_sort, METH_VARARGS,quicksort_docs},
    {"insertion_sort", (PyCFunction) insertion_sort, METH_VARARGS, insertionsort_docs},
    {"list_gen", (PyCFunction) list_generator, METH_VARARGS, NULL},
    { NULL, NULL, 0, NULL }
};

/*
 * Function: initcysort
 * ---------------------
 * Initalise the cysort module for Python
 */
void initcysort(void) {
    Py_InitModule3("cysort", cysort_funcs,
                   "Extension module example!");
}