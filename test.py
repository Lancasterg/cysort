import cysort as c
import time
import timeit
import random


# Create values to sort
values = []
for x in range(1000):
	values.append(random.randint(0, 100000)) 


def pysort_test(vals):
	p_sorted = vals.sort()


def cysort_bubblesort(vals):
	c_sorted = c.bubble_sort(values)

def cysort_quicksort(vals):
	c_sorted = c.quick_sort(values)


print(timeit.timeit('pysort_test(values)', setup="from __main__ import pysort_test, values", number=10000))
print(timeit.timeit('cysort_bubblesort(values)', setup="from __main__ import cysort_bubblesort, values", number=10000))
print(timeit.timeit('cysort_quicksort(values)', setup="from __main__ import cysort_quicksort, values", number=10000))