#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

vector<vector<int>> matrix_generator(int num){
    vector<vector<int>> matrix;
    matrix.resize(num,vector<int>(num));

    for (int i=0;i < matrix.size();i ++){
        for (int j=0; j< matrix[i].size();j++)
        matrix[i][j] = rand()%10 + 1;
    }

    return matrix;
}