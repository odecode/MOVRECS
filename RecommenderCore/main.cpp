#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <utility>
#include <fstream>
#include "matrix.h"
#include "simlist.h"
#include "engine.h"
#include "input.h"

const int nrows = 943;
const int ncols = 1682;

using namespace std::chrono;

// Helper to read simlist from file
void read_simlist(const std::string& filename, RatingMatrix& simlist) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Could not open " << filename << " for reading" << std::endl;
        return;
    }
    for (int i = 0; i < simlist.nrows; ++i) {
        for (int j = 0; j < simlist.ncols; ++j) {
            infile >> simlist.data[simlist.get_index(i, j)];
        }
    }
    infile.close();
}

int main(int argc, const char* argv[]){
    int which_user = 10;
    if(std::string(argv[0])=="usernum"){
        which_user = atoi(argv[1]);
    }
    std::vector<std::pair<int, float>> results;
    auto start = high_resolution_clock::now();
    RatingMatrix datamatrix = RatingMatrix(nrows, ncols);
    readfile(datamatrix);
    RatingMatrix simlist = RatingMatrix(nrows, ncols);
    read_simlist("simlist.txt", simlist);
    RatingCalculator engine = RatingCalculator(datamatrix,simlist,which_user,500);    
    auto stop = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(stop-start);
    // std::cout << "Datastructures setup in " << time_span.count() << " seconds"<< std::endl;
    
    float MAE = 0.0f;
    duration<double> total_time = duration_cast<duration<double>>(stop-stop);
    int preds = 0;
    for(int i = 0; i < ncols; i++){
        start = high_resolution_clock::now();
        float rating = engine.predict_rating(i);
        stop = high_resolution_clock::now();
        time_span = duration_cast<duration<double>>(stop-start);
        total_time += time_span;
        if(rating >= 0){
            preds++;
            results.push_back(std::make_pair(i, rating));
        }
    }
    // Sort results by rating descending
    std::sort(results.begin(), results.end(), [](const std::pair<int, float>& a, const std::pair<int, float>& b) {
        return a.second > b.second;
    });
    // Print top 5 items
    std::cout << "Top 5 recommended items for user " << which_user << ":\n";
    for(int k = 0; k < 5 && k < results.size(); ++k) {
        std::cout << "Item: " << results[k].first << ", Predicted rating: " << results[k].second << std::endl;
    }
    std::cout << "Total time " << total_time.count() << " " << preds << " predictions" <<std::endl;
}