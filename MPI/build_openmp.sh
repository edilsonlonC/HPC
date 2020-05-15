#!/bin/bash

args=("$@")
file="${args[0]}"
echo gcc -fopenmp $file.c -o $file 
gcc -fopenmp $file.c -o $file

./$file 800 800 0.001 8