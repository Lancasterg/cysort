import cysort as c
import time
import timeit
import random


# Create values to sort
values = []
for x in range(1000):
	values.append(random.randint(0, 100000)) 


def pysort_test(vals):
	""" 
	Sort implemented in pure python as the benchmark test. 
	Args:
		vals (list): A list of random numbers
	Returns:
		vals (list): A sorted list of numbers

	"""
	length = len(vals)
	for i in range(len(vals)):
		for j in range(i,length):
			if vals[i]>vals[j]:
				tmp=vals[i]
				vals[i]=vals[j]
				vals[j]=tmp
	return vals


def cysort_bubblesort(vals):
	""" 
	Cysort bubblesort
	Args:
		vals (list): A list of random numbers
	Returns:
		vals (list): A sorted list of numbers

	"""
	c_sorted = c.bubble_sort(vals)
	return c_sorted

def cysort_quicksort(vals):
	""" 
	Cysort quicksort test
	Args:
		vals (list): A list of random numbers
	Returns:
		vals (list): A sorted list of numbers

	"""
	c_sorted = c.quick_sort(vals)
	return c_sorted

def cysort_insertionsort(vals):
	""" 
	Cysort insertionsort test
	Args:
		vals (list): A list of random numbers
	Returns:
		vals (list): A sorted list of numbers

	"""
	c_sorted = c.insertion_sort(vals)
	return c_sorted


def cysort_selectionsort(vals):
	""" 
	Cysort selectionsort test
	Args:
		vals (list): A list of random numbers
	Returns:
		vals (list): A sorted list of numbers

	"""
	c_sorted = c.selection_sort(vals)
	return c_sorted

def cysort_parquicksort(vals):
	c_sorted = c.par_quick_sort(vals)
	return c_sorted


print("Python sort time:\t\t" +  str(timeit.timeit('pysort_test(values)',\
						 setup="from __main__ import pysort_test, values", number=100)))
print("Cysort insertionsort time: \t" + str(timeit.timeit('cysort_insertionsort(values)', \
						 setup="from __main__ import cysort_insertionsort, values", number=100)))
print("Cysort bubblesort time:\t\t" + str(timeit.timeit('cysort_bubblesort(values)',\
						 setup="from __main__ import cysort_bubblesort, values", number=100)))
print("Cysort quicksort time: \t\t" + str(timeit.timeit('cysort_quicksort(values)', \
						 setup="from __main__ import cysort_quicksort, values", number=100)))
print("Cysort selectionsort time: \t" + str(timeit.timeit('cysort_selectionsort(values)', \
						 setup="from __main__ import cysort_selectionsort, values", number=100)))
print("Cysort par_quicksort time: \t" + str(timeit.timeit('cysort_parquicksort(values)', \
						 setup="from __main__ import cysort_parquicksort, values", number=100)))

