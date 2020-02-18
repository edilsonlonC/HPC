#include <iostream>
#include <vector>
#include "../threads/matrix_generator.h"
#include "chrono"
#include "csv_generator.h"
using namespace std;




vector<vector<int>> matrix1 = {
    {2,0,1,3},
    {3,0,0,4},
    {5,1,1,5},
    {6,4,3,6}
} ;

vector<vector<int>> matrix2 = {
    {1,0,1,1},
    {1,2,1,2},
    {1,1,0,3},
    {2,3,4,4}
};

vector<vector<int>> result;


int multiplier(int a , int b){
   
 return a * b;
}

void matrixprint (vector<vector<int>>  &v){
    for(int i = 0; i < v.size();i++){
        for (int j = 0; j < v.size(); j++){
           cout<<"\t" << v[i][j] << "\t" ;
        }
        cout<<endl;

    }
}

int addElemets(int i){
    
}

void add (){
    int sum = 0;
      // cpu time
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    result.resize(matrix1.size(),vector<int>(matrix1.size()));
    for(int i = 0 ; i < matrix2.size(); i++){
        for (int im1 = 0;im1 < matrix1.size();im1++){
            for(int pos = 0; pos < matrix1[im1].size();pos++){
                sum  = sum + matrix1[im1][pos] * matrix2[pos][i];
                
            }
            result[im1][i] = sum;
            sum=0;
            
        }
       
    }
    end = std::chrono::system_clock::now();
    double time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    cout <<endl<<"time here : " <<time<<endl;
    csv_generator(result);
    
    
}

void *test (){
    for (int i=0; i< matrix1.size() ; i++){
        for (int j = 0; j<matrix1[i].size();j++){
            cout << matrix1[j][i] << endl;
        }
    }
}

int main (int argc, char *argv[]){

    int n = 0;
    try{
        n = stoi(argv[1]);
    }catch(const exception e){
        cout<<"me dañe =("<<endl;
        return -1;
    }
    matrix1 = matrix_generator(n);
    matrix2 = matrix_generator(n);
    result.resize(n,vector<int>(n));
    add();
 
   
    
    return 1;
}

