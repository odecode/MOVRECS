#include "matrix.h"
#include "input.h"
#include "simlist.h"
#include <iostream>
#include <fstream>

const int nrows = 943;
const int ncols = 1682;

int main() {
    RatingMatrix datamatrix(nrows, ncols);
    readfile(datamatrix);
    RatingMatrix simlist = create_simlist(nrows, ncols, datamatrix);
    std::ofstream outfile("simlist.txt");
    if (!outfile.is_open()) {
        std::cerr << "Could not open simlist.txt for writing" << std::endl;
        return 1;
    }
    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols; ++j) {
            outfile << simlist.data[simlist.get_index(i, j)];
            if (j < ncols - 1) outfile << " ";
        }
        outfile << "\n";
    }
    outfile.close();
    std::cout << "simlist.txt written successfully." << std::endl;
    return 0;
}
