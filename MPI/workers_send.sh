
#!/bin/bash

args=("$@")
file="${args[0]}"
echo mpicc $file.c -o $file 
mpicc $file.c -o $file

scp $file wn1:HPC/MPI
scp $file wn2:HPC/MPI
scp $file wn3:HPC/MPI
mpirun -np 4 --host master,wn1,wn2,wn3 ./$file
