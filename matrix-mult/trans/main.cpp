#include <iostream>
#include "matrix.h"
using namespace std;

int main (int argcv, char * argv[]){
    int n = 0;
    try{
        n = stoi(argv[1]);
    }catch(const exception e){
        cout<<"no sirvo =("<<endl;
        return -1;
    }

    MatrixOperation matrix_operation(n);
    matrix_operation.add();
    return 1;
}

