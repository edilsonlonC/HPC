#include <iostream>
#include <vector>
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

vector<vector<int>>  add (){
    int sum = 0;
    vector<vector<int>> result;
    result.resize(matrix1.size(),vector<int>(matrix1.size()));
    for(int i = 0 ; i < matrix2.size(); i++){
        for (int im1 = 0;im1 < matrix1.size();im1++){
            for(int pos = 0; pos < matrix1[im1].size();pos++){
                printf("%d %d \n", matrix1[im1][pos],matrix2[pos][i]);
                sum  = sum + matrix1[im1][pos] * matrix2[pos][i];
                
            }
            printf("esta es la suma %d \n" , sum);
            result[im1][i] = sum;
            sum=0;
            
        }
       
    }
    
    return  result;
}

void *test (){
    for (int i=0; i< matrix1.size() ; i++){
        for (int j = 0; j<matrix1[i].size();j++){
            cout << matrix1[j][i] << endl;
        }
    }
}

int main (){
   
    vector<vector<int>> result = add();
    matrixprint(result);
    return 1;
}

