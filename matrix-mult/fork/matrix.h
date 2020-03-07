#include <iostream>
#include <vector>
#include "../threads/matrix_generator.h"
#include "csv_generator.h"
#include <chrono>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

vector<vector<int>> m1 = {
  {1,2},
  {1,2}
};
vector<vector<int>> m2 = {
  {1,2},
  {1,2}
}; ;
vector<vector<int>> r;

class MatrixOperation{
    private: 
        // vector<vector<int>> m1;
        // vector<vector<int>> m2;
        // vector<vector<int>> r;

    public:
         MatrixOperation(int n){
        // m1.resize(n,vector<int>(n));
        // m2.resize(n,vector<int>(n));
        // r.resize(n,vector<int>(n));
        // m1=matrix_generator(n);
        // m2=matrix_generator(n);
        }
        ~MatrixOperation(){
        m1.clear();
        m2.clear();
        r.clear();
       // cout << "destructor success";
        }
        
        
        void add_elemets(vector<vector<int>> & m1 ,vector<vector<int>> & m2,vector<vector<int>> &r, long i){
            long mi = long(i);
            //cout<<endl<<"thread number "<< mi <<endl;
            for (long im1 = 0;im1 < m1.size();im1++){
                int sum = 0;
                cout<<"sum is : " <<sum<<endl;
                for(long pos = 0; pos < m1[im1].size();pos++)
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

        
        // id and status 
        pid_t pid;
        int status;
        // cpu time
        std::chrono::time_point<std::chrono::system_clock> start, end;
        start = std::chrono::system_clock::now();
    
        for(long i = 0 ; i < m2.size(); i++) {
          pid = fork();
          if (pid == 0){
            cout << "process : "<<getpid()<<" padre : "<<getppid()<<endl;
            this->add_elemets(m1,m2,r,i);
            exit(1);
          } else if (pid > 0) continue;
          else return -1;
          
       }

       for (long i = 0; i < m2.size();i++) wait(&status);


        this->matrixprint(r);
        end = std::chrono::system_clock::now();
        double time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
        //cout <<endl<<"time here : " <<time<<endl;
        csv_generator(r);
        csv_time(time,m2.size());
        return time;
    

}

    
};