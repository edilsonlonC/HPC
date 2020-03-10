#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <time.h>
#include <sys/wait.h>
#include <chrono>
#include "./csv_generator.h"


void solve_matrix  (int ** m1 , int ** m2 ,int **r, int number,long i){
    
    for (long j = 0; j < number; j ++){
        int sum = 0;
        for (long x = 0; x < number; x ++ )
            sum = sum + m1[j][x] * m2[x][i];
        r[j][i] = sum;
    }
}

void solve (int ** m1 , int ** m2 , int  ** r, int number){
    int status;

  
    pid_t p_id;

    for (long i = 0; i<number; i++) {

        p_id = fork();
        if (p_id == 0){
            solve_matrix(m1,m2,r,number,i);
            //printf("the child %d and father %d \n \n",getpid(),getppid());

            exit(1);
        }else continue;
        }
    for (long i = 0; i < number;i++) wait(&status);

       

}

void create(int **m1 , int number)
{
    for (int i = 0;i<number;i++){
        for (int j = 0 ; j<number;j++){
             //srand(time(0));
             m1[i][j] = rand() % 9;
        }
       
    }
}

void print_matrix(int ** m, int number){

    for (int i = 0;i<number;i++){
        for (int j = 0 ; j<number;j++){
            printf(" %d ", m[i][j] );
        }
        printf("\n");
    }
    printf("\n");
}



int main (int argc, char *argv[]){


    int number = (int)atoi(argv[1]);


    int  ** m1;
    int  ** m2; 
    int   **r;

    m1 = (int **) mmap(NULL,sizeof(int *)*number,PROT_READ | PROT_WRITE,MAP_SHARED | MAP_ANONYMOUS,1,0);
    m2 = (int **) mmap(NULL,sizeof(int *)*number,PROT_READ | PROT_WRITE,MAP_SHARED | MAP_ANONYMOUS,1,0);
    r = (int **) mmap(NULL,sizeof(int *)*number,PROT_READ | PROT_WRITE,MAP_SHARED | MAP_ANONYMOUS,1,0);

    for (int i = 0; i< number;i++){
        m1[i] = (int*)mmap(NULL,sizeof(int *)*number,PROT_READ | PROT_WRITE,MAP_SHARED | MAP_ANONYMOUS,1,0);
        m2[i] = (int*)mmap(NULL,sizeof(int *)*number,PROT_READ | PROT_WRITE,MAP_SHARED | MAP_ANONYMOUS,1,0);
        r[i] = (int*)mmap(NULL,sizeof(int *)*number,PROT_READ | PROT_WRITE,MAP_SHARED | MAP_ANONYMOUS,1,0);


    }
    create(m1,number);
    create(m2,number);
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    solve(m1,m2,r,number);
     end = std::chrono::system_clock::now();
    double time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    //printf("\n time here %lf \n",time);
    csv_time(time,number);
    //print_matrix(m1,number);
    //print_matrix(m2,number);
    //print_matrix(r,number);

    
    return 1;
}