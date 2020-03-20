#include "./jacobi.h"
#include "./csv_generator.h"
#include <chrono>

int main (int argc , char** argv){

    int n, nsteps;
    char* fname;
    double h;
     n      = (argc > 1) ? atoi(argv[1]) : 100;
    nsteps = (argc > 2) ? atoi(argv[2]) : 100;
    fname  = (argc > 3) ? argv[3] : NULL;

    Jacobi j (n);
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    j.jacobi(nsteps,n);
    end = std::chrono::system_clock::now();
    double time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    j.write_solution(n,fname);
    csv_time(time,nsteps/2);
    return 1;
}