#include <iostream>
#include <vector>
#include "../threads/matrix_generator.h"
#include "csv_generator.h"
#include <chrono>
#include <unistd.h>
#include <omp.h>


using namespace std;

class MatrixOperation{
    private: 
        vector<vector<int>> m1;
        vector<vector<int>> m2;
        vector<vector<int>> r;

    public:
        MatrixOperation(int n){
        this->m1.resize(n,vector<int>(n));
        this->m2.resize(n,vector<int>(n));
        this->r.resize(n,vector<int>(n));
        this->m1=matrix_generator(n);
        this->m2=matrix_generator(n);
        }
        ~MatrixOperation(){
              this->m1.clear();
        this->m2.clear();
        this->r.clear();
       // cout << "destructor success";
        }
        
        
        void add_elemets(vector<vector<int>> & m1 ,vector<vector<int>> & m2,vector<vector<int>> &r, long i){
            long mi = long(i);
            long pos = 0;
            long im1 = 0;
            //cout<<endl<<"thread number "<< mi <<endl;

            #pragma omp parallel private(im1, pos)


            for (im1 = 0;im1 < m1.size();im1++){
                int sum = 0;
            
            #pragma omp parallel for

                for(pos = 0; pos < m1[im1].size();pos++)
                    sum  = sum + m1[im1][pos] * m2[pos][mi];
                r[im1][mi] = sum;
          }
        
        }
      void matrixprint (vector<vector<int>>  &v){
        for(int i = 0; i < v.size();i++){
            for (int j = 0; j < v.size(); j++){
            cout<<"\t" << v[i][j] << "\t" ;
         }
            cout<<endl;
    }
      }

    double add (){

        
        
        // cpu time
        std::chrono::time_point<std::chrono::system_clock> start, end;
        start = std::chrono::system_clock::now();
    
        for(long i = 0 ; i < this->m2.size(); i++) this->add_elemets(this->m1,this->m2,this->r,i);
       
    
        end = std::chrono::system_clock::now();
        double time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
        cout <<endl<<"time here : " <<time<<endl;
        csv_generator(this->r);
        csv_time(time,this->m2.size());
        this->matrixprint(this->m1);
        this->matrixprint(this->m2);
        this->matrixprint(this->r);

        return time;
    

}

    
};