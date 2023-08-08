#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "matrix.h"
using namespace std;

void readfile(RatingMatrix matrix){
std::ifstream myfile("u.data");
    string line;
    string row, col, strrating;
    while(getline(myfile, line)){
        
        stringstream ss(line);
        getline(ss,row,'\t');
        getline(ss,col,'\t');
        getline(ss,strrating,'\t');
        int user = stoi(row); // convert string to integer
        int item = stoi(col);
        int rating = (float) stoi(strrating);
        user--; // user numbers range from 1-943, while matrix indices range from 0-942. Subtract 1 from user to align with index
        item--; // same as user
        int matrixindex = matrix.get_index(user,item);
        matrix.data[matrixindex]= rating;
        //matrix[user*nitems+item] = rating;

    }
    myfile.close();
}