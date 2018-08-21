import helloworld as h
import time
import random


values = []

for x in range(100):
	values.append(random.randint(0, 100000)) 


values_2 = h.list_gen(values)
print(values_2)



start = time.time()
py_sorted = values.sort()
end = time.time()
py_sort_time = end - start
print("Python sort function: "+ str(end - start))

start = time.time()
c_sorted = h.bubble_sort(values)
end = time.time()
bubble_sort_time = end - start
print("C bubble_sort: "+ str(end - start))

start = time.time()
c_sorted = h.quick_sort(values)
end = time.time()
quick_sort_time = end - start

print("C quick_sort: "+ str(end - start))

print(c_sorted)

print(float(quick_sort_time))


if (quick_sort_time > bubble_sort_time):
	print(":(")
else:
	print(":)")
