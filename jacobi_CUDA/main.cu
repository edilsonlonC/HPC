#include <iostream>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "definitions.cuh"
#include <time.h>

//Number of elements on which to perform CFD
unsigned int Ni = 512; // Y elements
unsigned int Nj = 512; // X elements
unsigned int nIterations = 10000; // No Of Iterations
unsigned int kernelVersion =1; // Decides which GPU kernel version to call (Set it to 1 or 2)

int main(int argc, char** argv)
{

	//Variables for Timing
	float cpuTime, gpuTime;

	// CPU and GPU Pointers ( d_XX : refers to pointer pointing to GPU memory. This is just a convention)
	float *t = NULL, *t_prev = NULL;
	float *d_t = NULL,*d_t_prev= NULL;

	parseCommandLineArguments(argc, (char **)argv);
	printf("\n Ni= %d, Nj=%d nIteration=%d",Ni,Nj,nIterations);

	unsigned int size = Ni * Nj * sizeof(float);

	if(!initializeCPU(&t, &t_prev) )
	{
		printf("\n Error in allocating memory on CPU!!!");
		unInitializeCPU(&t, &t_prev);
		getchar();
		return 0;
	}

	if (!initializeGPU(&d_t, &d_t_prev)) 
	{
		printf("\n Error in allocating memory on GPU!!!");
		unInitializeCPU(&t, &t_prev);
		unInitializeGPU(&d_t, &d_t_prev);
		return 0;
	}
   
	//Perform CFD on CPU
	performCPUCFD(t,t_prev, &cpuTime);

	// To temporarily store CPU data. This is just for comparing with GPU output
	float *tempBuffer = (float*) calloc(Ni*Nj, sizeof(float));
	memcpy(tempBuffer, t_prev, size);

	//Perform CFD on GPU
	if(!performGPUCFD(d_t,d_t_prev, t, t_prev, &gpuTime))
	{
		printf("\n GPU Kernel failed !!!");
		unInitializeCPU(&t, &t_prev);
		unInitializeGPU(&d_t, &d_t_prev);
		if(tempBuffer !=NULL)
			free(tempBuffer);
		return 0;
	}
	
	printf("\n Is host equal to device = %d", checkHostEqualsDevice(tempBuffer,t));
	printf("\n Speedup = %fx", (float)(cpuTime/gpuTime));

	unInitializeCPU(&t, &t_prev);
	unInitializeGPU(&d_t, &d_t_prev);

	if(tempBuffer !=NULL)
		free(tempBuffer);
	
	printf("\n Finished Processing!!!");
	getchar();

}



int initializeCPU(float **t, float **t_prev)
{
	*t = (float*) calloc(Ni*Nj, sizeof(float));
	*t_prev = (float*) calloc(Ni*Nj, sizeof(float));

	if((*t)==NULL || (*t_prev) == NULL)
		return 0;
	else
		return 1;
}

void unInitializeCPU(float **t, float **t_prev)
{
	if((*t) !=NULL)
		free(*t);
	if((*t_prev) != NULL)
		free(*t_prev);
}

int initializeGPU(float **d_t, float **d_t_prev)
{

	unsigned int size = Ni * Nj * sizeof(float);

	

	// Choose which GPU to run on, change this on a multi-GPU system.
    cudaError_t cudaStatus = cudaSetDevice(0);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
		getchar();
        return 0;
    }
	 // Allocate GPU buffers.
    cudaStatus = cudaMalloc((void**)&(*d_t), size);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!");
		getchar();
        return 0;
    }

	 // Allocate GPU buffers   .
    cudaStatus = cudaMalloc((void**)&(*d_t_prev), size);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMalloc failed!");
		getchar();
        return 0;
    }

	 // Memset GPU buffers
    cudaStatus = cudaMemset((*d_t),0, size);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemset failed!");
		getchar();
        return 0;
    }

	// Memset GPU buffers
    cudaStatus = cudaMemset((*d_t_prev),0, size);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaMemset failed!");
		getchar();
        return 0;
    }

	return 1;
}


void unInitializeGPU(float **d_t, float **d_t_prev)
{
	cudaError_t cudaStatus;

	if((*d_t)!=NULL)
    cudaStatus = cudaFree((*d_t));
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaFree failed!");
        return;
    }

	if((*d_t_prev)!=NULL)
    cudaStatus = cudaFree((*d_t_prev));
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaFree failed!");
        return;
    }

#if 0
	cudaStatus = cudaDeviceReset();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaDeviceReset failed!");
		getchar();
        return;
    }
#endif
}

void performCPUCFD(float *t, float *t_prev, float *cpuTime)
{

	float h,x,y;

	h = 1.0f/(Ni-1);

	for(unsigned int i=0;i<Ni;i++)
	{
		x = i*h;
		t_prev[i*Nj+0] = x*x;
		t_prev[i*Nj+(Nj-1)] = x*x + 1.0f;
	}

	for(unsigned int j=0;j < Nj; j++)
	{
		y = j*h;
		t_prev[0*Nj+j] = y*y;
		t_prev[((Ni-1) * Nj) + j] = 1.0f + y*y;

	}

    float elapsedTimeInMs = 0.0f;

	clock_t start = clock();
	
	for(unsigned int k=0;k<nIterations;k++)
	{
		for(unsigned int j=1;j<(Nj-1);j++)
		{
			for(unsigned int i=1;i<(Ni-1);i++)
			{
				t[i*Nj+j] = 0.25f * (t_prev[(i-1)*Nj+j] + t_prev[(i+1)*Nj+j] + t_prev[i*Nj+(j-1)] + 
					t_prev[i*Nj+(j+1)] - 4*h*h);
			}
		}
		
		float* pingPong = t_prev;
        t_prev = t;
        t = pingPong;
	}

	clock_t end = clock();
	elapsedTimeInMs = (float)((end - start) * 1000 / CLOCKS_PER_SEC);

	printf("\n CPU Time:: %f ms", elapsedTimeInMs);
	*cpuTime = elapsedTimeInMs;
}

int performGPUCFD(float *d_t, float *d_t_prev, float *t, float *t_prev, float*gpuTime)
{

	float h,x,y;
	const char *str = (char*) malloc(1024); // To store error string
	
	//Decide how many blocks per thread and how many blocks per grid
	dim3 dimBlock(THREADS_PER_BLOCK_X,THREADS_PER_BLOCK_Y);
	dim3 dimGrid(Nj/dimBlock.x,Ni/dimBlock.y);
	
	h = 1.0f/(Ni-1);
	memset(t_prev, 0, sizeof(float) * Ni * Nj);
  
	for(unsigned int i=0;i<Ni;i++)
	{
		x = i*h;
		t_prev[i*Nj+0] = x*x;
		t_prev[i*Nj+(Nj-1)] = x*x + 1.0f;
	}

	for(unsigned int j=0;j < Nj; j++)
	{
		y = j*h;
		t_prev[0*Nj+j] = y*y;
		t_prev[((Ni-1) * Nj) + j] = 1.0f + y*y;

	}

	//Copy data to device
	cudaMemcpy(d_t_prev, t_prev, sizeof(float) * Ni * Nj , cudaMemcpyHostToDevice);

	//Insert event to calculate time
	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);


	//This calls Version 1 of kernel which uses Global memory
	if(kernelVersion ==1)
	{
		printf("\n Inside Kernel ::1\n");
		cudaEventRecord(start, 0);
		
		for(unsigned int k=0;k<nIterations;k++)
		{
			// Launch a kernel on the GPU with one thread for each element.
			calculateCFD_V1<<<dimGrid,dimBlock>>>(d_t_prev,d_t, Ni, Nj, h);
			
			float* pingPong = d_t_prev;
			d_t_prev = d_t;
			d_t = pingPong;
		}
		cudaEventRecord(stop, 0);
		cudaEventSynchronize(stop);
	}
	//This calls Version 2 of kernel which uses optimization by copying data to shared memory
	else if(kernelVersion ==2)
	{
		printf("\n Inside Kernel ::2\n");
		cudaEventRecord(start, 0);
	
		for(unsigned int k=0;k<nIterations;k++)
		{
			// Launch a kernel on the GPU with one thread for each element.
			calculateCFD_V2<<<dimGrid,dimBlock>>>(d_t_prev,d_t, Ni, Nj, h);
			
			float* pingPong = d_t_prev;
			d_t_prev = d_t;
			d_t = pingPong;
		}
	 	cudaEventRecord(stop, 0);
		cudaEventSynchronize(stop);

	}
	
	cudaError_t cudaStatus = cudaGetLastError();
	if (cudaStatus != cudaSuccess) {
		str = cudaGetErrorString(cudaStatus);
		fprintf(stderr, "CUDA Error!:: %s\n", str);
		getchar();
		return 0;
	}
	
	float elapsedTime;
	cudaEventElapsedTime(&elapsedTime, start, stop);
	printf("\n GPU Time:: %f ms", elapsedTime);

	*gpuTime = elapsedTime;

	cudaStatus = cudaMemcpy(t, d_t_prev, sizeof(float) * Ni * Nj , cudaMemcpyDeviceToHost);
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaMemcpy failed!");
		str = cudaGetErrorString(cudaStatus);
		fprintf(stderr, "CUDA Error!:: %s\n", str);
		getchar();
		return 0;
	}
	
	return 1;
}

int checkHostEqualsDevice(float* o_host, float* o_device)
{
	int flag =1;

	float tolerance = 0.0001f;
	//Compare the results
	for(unsigned int j=0;j<Nj;j++)
	{
		for(unsigned int i=0;i<Ni;i++)
		{
			if( (o_host[i*Nj+j] - o_device[i*Nj+j]) >= tolerance ||  (o_host[i*Nj+j] - o_device[i*Nj+j]) <= -tolerance)
			{
				printf("\n D=[%f]!=H=[%f] since Diff  > tol %f for [%d][%d]",o_device[i*Nj+j],  o_host[i*Nj+j],tolerance, i, j);
				flag =0;
				getchar();
				return flag;
			}
		}
	}

	return flag;
}

void parseCommandLineArguments(int argc, char**argv)
{
    if (argc >= 1) 
	{
        for (int i=1; i < argc; i++) 
		{
			int bFirstArgIsParam = false;
			int string_start = 0;
			while (argv[i][string_start] == '-')
				string_start++;
			char *string_argv = &argv[i][string_start];

			if (!STRNCASECMP(string_argv, "Ni=", 3)) 
			{
                bFirstArgIsParam = true; 
				Ni = atoi(&string_argv[3]);
				continue;
			}
			if (!STRNCASECMP(string_argv, "Nj=", 3)) 
			{
                bFirstArgIsParam = true; 
				Nj = atoi(&string_argv[3]);
				continue;
			}
			if (!STRNCASECMP(string_argv, "iterations=", 11)) 
			{
                bFirstArgIsParam = true; 
				nIterations = atoi(&string_argv[11]);
				continue;
			}
			if (!STRNCASECMP(string_argv, "kernel=", 7)) 
			{
                bFirstArgIsParam = true; 
				kernelVersion = atoi(&string_argv[7]);
				continue;
			}

			if (!bFirstArgIsParam) 
			{
					printf("Invalid arguments\n");
					for (int n=0; n < argc; n++) 
					{
						printf("argv[%d] = %s\n", n, argv[n]);
					}
					printf("\n");
					exit(0);
			}
		}
	}

	if(( Ni % THREADS_PER_BLOCK_Y != 0)  || (Nj % THREADS_PER_BLOCK_X != 0))
	{
		fprintf(stderr, "Please specify Ni & Nj as multiple of 16 !!!!");
		getchar();
		exit(0);
	}
}

