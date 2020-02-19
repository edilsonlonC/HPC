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

int csv_time(double time , int threads){

    try{
    string headers = "threads,time";
    string cell;
    string line;
    std::fstream openfile("time.csv");
    if (openfile.is_open()){
        while(getline(openfile,line)){
            if (line != headers)
            {
            
            cell.append(line);
            cell.append("\n");
            }
        }
        openfile.close();
    }else {
        cout << "time csv doesn't exist"<<endl;
    }
    std::ofstream  file;
    file.open("time.csv");
    file << "threads,time\n";
    
    
    cell.append(to_string(threads));
    cell.append(",");
    cell.append(to_string (time));
    cell.append("\n");
    file << cell;
    file.close();
 
    
    }catch(const  exception e){
        cout<<"erro al generar el csv";
        return -1;
    }

    return 1;

}