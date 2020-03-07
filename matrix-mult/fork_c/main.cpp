#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <time.h>


void solve_matrix  (int ** m1 , int ** m2 ,int **r, int number,long i){
    
    for (long j = 0; j < number; j ++){
        int sum = 0;
        for (long x = 0; x < number; x ++ )
            sum = sum + m1[j][x] * m2[x][i];
        r[j][i] = sum;
    }
}

void solve (int ** m1 , int ** m2 , int  ** r, int number){
    
    for (long i = 0; i<number; i++) solve_matrix(m1,m2,r,number,i);
}

void create(int **m1 , int number)
{
    for (int i = 0;i<number;i++){
        for (int j = 0 ; j<number;j++){
             m1[i][j] = rand() & 9;
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



int main (){


    int number = 3;
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
    solve(m1,m2,r,number);
    print_matrix(m1,number);
    print_matrix(m2,number);
    print_matrix(r,number);

    
    return 1;
}