#include "./jacobi.h"


int main (int argc , char** argv){

    int n, nsteps;
    char* fname;
    double h;
     n      = (argc > 1) ? atoi(argv[1]) : 100;
    nsteps = (argc > 2) ? atoi(argv[2]) : 100;
    fname  = (argc > 3) ? argv[3] : NULL;

    Jacobi j (n);
    j.jacobi(nsteps,n);
    j.write_solution(n,fname);

    return 1;
}