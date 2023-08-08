#pragma once
#include <iostream>
class RatingMatrix{
    public:
        float* data;
        int nrows;
        int ncols;
        
        int get_index (int x, int y) const {
            return x*ncols+y;
        }

        RatingMatrix copy(){
            RatingMatrix copy = RatingMatrix(this->nrows,this->ncols);
            for(int i = 0; i < nrows*ncols; i++){
                copy.data[i] = this->data[i];
            }
            return copy;
        }

        RatingMatrix() = default;

        RatingMatrix(int rows, int cols){
            this->nrows = rows;
            this->ncols = cols;
            this->data = new float[rows*cols];
            for(int i = 0; i < rows; i++){
                for(int j = 0; j < cols; j++){
                    int index = this->get_index(i,j);
                    // if(index > 1500000) {
                    //     std::cout << rows*cols << std::endl;
                    //     std::cout << index << std::endl;
                    // }
                    this->data[index] = 0.0f;
                }
            }
        }
};