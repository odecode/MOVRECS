#include <iostream>
#include <chrono>
#include "matrix.h"
#include "simlist.h"
#include "engine.h"
#include "input.h"

const int nrows = 943;
const int ncols = 1682;

using namespace std::chrono;

int main(int argc, const char* argv[]){
    int which_user = 10;
    if(std::string(argv[0])=="usernum"){
        which_user = atoi(argv[1]);
    }
    auto start = high_resolution_clock::now();
    RatingMatrix datamatrix = RatingMatrix(nrows, ncols);
    readfile(datamatrix);
    RatingMatrix simlist = create_simlist(nrows,ncols,datamatrix);
    RatingCalculator engine = RatingCalculator(datamatrix,simlist,which_user,500);    
    auto stop = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(stop-start);
    std::cout << "Datastructures setup in " << time_span.count() << " seconds"<< std::endl;
    
    float MAE = 0.0f;
    duration<double> total_time = duration_cast<duration<double>>(stop-stop);
    int preds = 0;
    for(int i = 0; i < ncols; i++){
        start = high_resolution_clock::now();
        float rating = engine.predict_rating(i);
        stop = high_resolution_clock::now();
        time_span = duration_cast<duration<double>>(stop-start);
        total_time += time_span;
        std::cout << "predicted in " << time_span.count() << " seconds"<< " value "<< rating << std::endl;
        if(rating >= 0) preds++;
    }
    std::cout << "Total time " << total_time.count() << " " << preds << " predictions" <<std::endl;
}