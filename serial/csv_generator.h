#include <iostream>
#include <fstream>
#include <vector>
#include <string>


using namespace std;

int csv_generator(vector<vector<int>>  & matrix){

    std::ofstream file;
    file.open("result.csv");
    for (int i = 0 ; i < matrix.size(); i++ ){
       std::string cell("");
        for (int j = 0; j < matrix[i].size(); j++){
            cell.append(to_string(matrix[i][j]));
            cell.append(",");
        }
        cell.append("\n");
        file << cell;
    }
    file.close();
}