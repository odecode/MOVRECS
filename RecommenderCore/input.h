#pragma once
#include "matrix.h"
#include <fstream>
#include <sstream>
#include <string>

// Reads u.data and fills the RatingMatrix
inline void readfile(RatingMatrix& mat) {
    std::ifstream infile("./u.data");
    if (!infile.is_open()) {
        std::cerr << "Could not open Docker/u.data" << std::endl;
        return;
    }
    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        int user, item, rating;
        long timestamp;
        if (!(iss >> user >> item >> rating >> timestamp)) continue;
        // u.data is 1-indexed, matrix is 0-indexed
        int row = user - 1;
        int col = item - 1;
        if (row >= 0 && row < mat.nrows && col >= 0 && col < mat.ncols)
            mat.data[mat.get_index(row, col)] = static_cast<float>(rating);
    }
    infile.close();
}
