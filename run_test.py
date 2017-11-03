#!/usr/bin/env python3
import fileinput
import os
import subprocess
from time import gmtime, strftime

num_min_q = 1
num_max_q = 5000
incr_q = 100
numP_q = 2000

num_min_m = 1
num_max_m = 5000
incr_m = 100
numP_m = 2000

if not os.path.exists('datasets'):
    os.makedirs('datasets')


current_time = strftime("%Y-%m-%d_%H:%M:%S", gmtime())
QUICKSORT = '    ret = genera_tiempos_ordenacion(QuickSort, nombre,num_min, num_max,incr, n_perms);\n'
MERGESORT = '    ret = genera_tiempos_ordenacion(MergeSort, nombre,num_min, num_max,incr, n_perms);\n'

file = open('ejercicio5.c', 'r+')
data = file.readlines()
print("\033[31;1mQUICKSORT\n\n")
file.seek(0, 0)
data[67] = QUICKSORT
file.writelines(data)
file.flush()

os.system("make")
print("\n\n")

os.system('./ejercicio5 -num_min %d -num_max %d -incr %d -numP %d -fichSalida %s'%(num_min_q, num_max_q, incr_q, numP_q, '%s%s_QuickSort.txt'%('datasets/', current_time) ))

print("\033[0m")
print("\033[32;1mMERGESORT\n\n")
data[67] = MERGESORT
file.seek(0, 0)
file.writelines(data)
file.flush()

os.system("make")

print("\n\n")

os.system('./ejercicio5 -num_min %d -num_max %d -incr %d -numP %d -fichSalida %s'%(num_min_m, num_max_m, incr_m, numP_m, '%s%s_MergeSort.txt'%('datasets/', current_time) ))

print("\033[0m")
file.close()