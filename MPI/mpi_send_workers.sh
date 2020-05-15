
#!/bin/bash

args=("$@")
file="${args[0]}"
echo mpicc -o $file $file -lm 
mpicc -o $file $file.c -lm 

scp $file wn1:HPC/MPI
scp $file wn2:HPC/MPI
scp $file wn3:HPC/MPI
mpirun -np 4 --host master,wn1,wn2,wn3 ./$file
