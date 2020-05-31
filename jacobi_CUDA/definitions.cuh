
//Number of Threads per bolock
#define THREADS_PER_BLOCK_X 16
#define THREADS_PER_BLOCK_Y 16
#define RADIUS 1
#define HALO 1

#ifndef STRNCASECMP
#ifdef _WIN32
#define STRNCASECMP _strnicmp
#else
#define STRNCASECMP strncasecmp
#endif
#endif

int initializeCPU(float **t, float **t_prev);
int initializeGPU(float **d_t, float **d_t_prev);

void unInitializeCPU(float **t, float **t_prev);
void unInitializeGPU(float **d_t, float **d_t_prev);

void performCPUCFD(float *t, float *t_prev, float  *cpuTime);
int performGPUCFD(float *d_t, float *d_t_prev, float *t, float *t_prev, float *gpuTime);

//Utility functions
int checkHostEqualsDevice(float* o_host, float* o_device);
void parseCommandLineArguments(int argc,char*argv[]);

//Kernel Declaration
 __global__ void calculateCFD_V1( float* input,  float* output, unsigned int Ni, unsigned int Nj, float h);
 __global__ void calculateCFD_V2( float* input,  float* output, unsigned int Ni, unsigned int Nj, float h);


