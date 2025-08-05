#include <vector>
#include <cmath>
#include <chrono>
#include <iostream>
#include "matrix.h"
using namespace std::chrono;
float calc_row_mean(int nitems, int row, RatingMatrix matrix){
    // calculate mean rating for a user
    // row represents user
    float mean = 0.0f;
    float index = 0.0f;
    for(int i = 0; i < nitems; i++){ 
        int increment1 = mean+1;
        int increment2 = index+1;
        int index_rowi = matrix.get_index(row,i);
        mean = matrix.data[index_rowi] != 0 ? increment1 : mean;
        index = matrix.data[index_rowi] != 0 ? increment2 : index;
    }
    mean /= index;
    return mean;
}

float sim(int nitems, int u, int v, RatingMatrix matrix){
    /*
        Calculate Pearson correlation coefficient between user u and user v
        BUG: Sometimes divides by zero. Circumvented by setting denominator to 0.001 if it is 0
    */
    
    std::vector<int> T;
    // find all co-rated items between u and v, store in vector T
    for(int i = 0; i < nitems; i++){
        int index_ui = matrix.get_index(u,i);
        int index_vi = matrix.get_index(v,i);
        if(matrix.data[index_ui] != 0 && matrix.data[index_vi] != 0){
            T.push_back(i);
        }
        // if(matrix[u*nitems+i] != 0 && matrix[v*nitems+i] != 0){
        //     T.push_back(i);
        // }
    }
    float mean_u = calc_row_mean(nitems,u,matrix);
    float mean_v = calc_row_mean(nitems,v,matrix);
    float sum_above = 0.0f; //numerator
    float sum_below = 0.0f;  //denominator
    //for every item in T, calculate (rating from u - mean_rating_u)*(rating from v - mean_rating v)
    for(int n = 0; n < T.size(); n++){
        int utn = matrix.get_index(u,T[n]);
        int vtn = matrix.get_index(v,T[n]);
        sum_above += ((matrix.data[utn] - mean_u)*(matrix.data[vtn]-mean_v));
        sum_below += sqrt((pow((matrix.data[utn] - mean_u),2))*(pow((matrix.data[vtn] - mean_v),2)));
        // sum_above += ((matrix[u*nitems+T[n]] -mean_u)*(matrix[v*nitems+T[n]]-mean_v));
        // sum_below += sqrt((pow((matrix[u*nitems+T[n]]- mean_u),2))*(pow((matrix[v*nitems+T[n]] - mean_v),2)));
    }
    //if(sum_below == 0.0){sum_below =0.001;}
    sum_below = sum_below == 0.0f ? 0.001f : sum_below;
    float sim = sum_above/sum_below;
    return sim;
}
RatingMatrix create_simlist(int nusers, int nitems, RatingMatrix matrix){
    int index = 0;
    
    auto start = high_resolution_clock::now();
    RatingMatrix simlist = RatingMatrix(nusers, nitems);
    auto stop = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(stop-start);
    // std::cout << "similarity datastructure allocated in " << time_span.count() << std::endl;

    for(int i = 0; i < nusers; i++){
        for(int j = 0; j < nusers; j++){
            int simlistindex = simlist.get_index(i,j);
            float simil = sim(nitems,i,j,matrix);
            simlist.data[simlistindex] = simil;
        }
    }
    return simlist;    
}

