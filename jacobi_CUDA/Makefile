all:	cfd

cfd:	kernel.o main.o
	nvcc kernel.o main.o -o cfd

main.o:	main.cu
	nvcc -c main.cu -o main.o

kernel.o: kernel.cu
	nvcc -c kernel.cu -o kernel.o

clean:
	rm -f *.o cfd	
