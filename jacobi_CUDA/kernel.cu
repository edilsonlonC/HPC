#include "definitions.cuh"

//Performs CFD calculation on global memory. This code does not use any advance optimization technique on GPU
// But still acheives many fold performance gain
__global__ void calculateCFD_V1( float* input,  float* output, unsigned int Ni, unsigned int Nj, 
								   float h)
{
	unsigned int i = threadIdx.x + blockIdx.x * blockDim.x; // Y - ID
	unsigned int j = threadIdx.y + blockIdx.y * blockDim.y; // X - ID

	unsigned int iPrev = i-1; // Previous Y element
	unsigned int iNext = i+1; // Next Y element

	unsigned int jPrev = j-1; //Previous X element
	unsigned int jNext = j+1; // Next X element


	unsigned int index = i * Nj + j;

	if( i > 0 && j > 0 && i < (Ni-1) && j <(Nj-1))
		output[index] = 0.25f * (input[iPrev] + input[iNext] + input[jPrev] + input[jNext] - 4*h*h);
}
/*
//This version of Kernel uses optimization by copying the data into shared memory and hence results in better performance
__global__ void calculateCFD_V2( float* input,  float* output, unsigned int Ni, unsigned int Nj, 
								   float h)


	//Current Global ID
	int i = ; // Y - ID
	int j = ; // X - ID
	
	// Fill the size of shared memory
	__shared__ float sData [][];
	
	unsigned int index = (i)* Nj + (j) ;

	// copy data to shared memory
	sData[][] = input[]; 

	//Add synchronization. Guess Why?

	if( i > 0 && j > 0 && i < (Ni-1) && j <(Nj-1))
		output[index] = 0.25f * (sData[][] + sData[][] + sData[][] 
			+ sData[][] - 4*h*h);

}*/