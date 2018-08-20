#include <Python.h>

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

/* Bubble sort */
static char bubblesort_docs[] = "Bubble sort implementation in C";

/* swap function for bubble sort */ 
void swap(int *xp, int *yp){
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// A function to implement bubble sort
void bubbleSort(int arr[], int n){
   int i, j;
   for (i = 0; i < n-1; i++)      
 
       // Last i elements are already in place   
       for (j = 0; j < n-i-1; j++) 
           if (arr[j] > arr[j+1])
              swap(&arr[j], &arr[j+1]);
}

static PyObject *read_list(PyObject *self, PyObject *args) {
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
			//Py_RETURN_NONE;
		}
		my_list[i] = PyFloat_AsDouble(int_obj);
	}

	bubbleSort(my_list, num_items);

	PyObject* python_val = PyList_New(num_items);
    for (int j = 0; j < num_items; ++j)
    {
        PyObject* python_int = Py_BuildValue("i", my_list[j]);
        PyList_SetItem(python_val, j, python_int);
    }
    return python_val;
}



/* Python method declarations*/
static PyMethodDef helloworld_funcs[] = {
   {"helloworld", (PyCFunction)helloworld, METH_NOARGS, helloworld_docs},
   {"read_num", (PyCFunction) test_func, METH_VARARGS, NULL},
   {"read_list", (PyCFunction) read_list, METH_VARARGS, bubblesort_docs},
   { NULL, NULL, 0, NULL }
};

void inithelloworld(void) {
   Py_InitModule3("helloworld", helloworld_funcs,
                  "Extension module example!");
}