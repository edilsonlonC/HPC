#include <vector>
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

vector<vector<vector<int>>> create_matrix(int num, vector<vector<int>>  & matrix1 , vector<vector<int>>  & matrix2 )
{
    matrix1.resize(num,vector<int>(num));
    matrix2.resize(num,vector<int>(num));
    for (int i = 0; i < num; i++){
        for (int j=0; j < num ; j++){
            matrix1[i][j] = 10;
            matrix2[i][j]  = 10;
        }

     
    }
       vector<vector<vector<int>>> result = {
            matrix1,
            matrix2
        };
        return result;

}

vector<vector<int>> matrix_create (int num){
    vector<vector<int>> matrix;
    matrix.resize(num,vector<int>(num,0));
    for (int i = 0 ;  i < num;i++ ){
        for (int j=0; j < num ; j++){
            matrix[i][j] = rand() % 10 +1 ;
        }
    }
    return matrix;
}