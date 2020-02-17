#include <iostream>
#include <vector>
#include <pthread.h>
#include <unistd.h>
#include "matrix_generator.h"
#include "csv_generator.h"
#include <chrono>
using namespace std;





vector<vector<int>> matrix1 = {
    {2,0,1,3},
    {3,0,0,4},
    {5,1,1,5},
    {6,4,3,6}
};

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

void *add_elemets(void *i){
    long mi = long(i);
    //cout<<endl<<"thread number "<< mi <<endl;
     for (long im1 = 0;im1 < matrix1.size();im1++){
         int sum = 0;
            for(long pos = 0; pos < matrix1[im1].size();pos++){
                sum  = sum + matrix1[im1][pos] * matrix2[pos][mi];
               
                
            }
            result[im1][mi] = sum;
          
           
            
            
        }
        
        pthread_exit(NULL);
        
}

void  add (){

    
    pthread_t threads[matrix2.size()];
    int rc;
      // cpu time
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    
    for(long i = 0 ; i < matrix2.size(); i++){
       rc = pthread_create(&threads[i],NULL,add_elemets, (void *)i );
       
       cout <<endl;
        if(rc){
            cout<<"error form thread_create";
            exit(-1);
        }
         
        
    }
    for (int i = 0 ; i < matrix2.size();i++){
        pthread_join(threads[i],NULL);
    }
    end = std::chrono::system_clock::now();
    double time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    cout <<endl<<"time here : " <<time<<endl;
    csv_generator(result);
    matrix1.clear();
    matrix2.clear();
    result.clear();
    //free(threads);
   // matrixprint(result);
    pthread_exit(NULL);
  
   
   
}

void *test (){
    while(1)
    {
    for (int i=0; i< matrix1.size() ; i++){
        for (int j = 0; j<matrix1[i].size();j++){
            cout << matrix1[j][i] << endl;
        }
    }
    }
}

int main (int argcv, char * argv[]){
    int n = 0;
    try{
        n = stoi(argv[1]);
    }catch(const exception e){
        cout<<"no sirvo =("<<endl;
        return -1;
    }


    cout << "matrix 1"<<endl;
    matrix1 = matrix_generator(n);
    matrix2 = matrix_generator(n);
    //matrixprint(matrix1);
    cout << "matrix 2"<<endl;
    //matrixprint(matrix2);
    
    
    result.resize(matrix1.size(),vector<int>(matrix1.size()));

  
    add();
    
    
   
        
    return 1;
}

