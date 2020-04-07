#include <iostream>
#include "matrix.h"
using namespace std;


int main (int argc, char *argv[]){

    int n = 0;
    try{
        n = stoi(argv[1]);
    }catch(const exception e){
        cout<<"me dañe =("<<endl;
        return -1;
    }

    MatrixOperation matrix_operation(n);
    matrix_operation.add();
    
}

