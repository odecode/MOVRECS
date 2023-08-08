#include "engine.h"

RatingCalculator::RatingCalculator(RatingMatrix data, RatingMatrix simlist, int user, int size){
    this->datamatrix = data;
    this->simlist = simlist;
    this->imputated_matrix = data.copy();
    this->user = user;
    this->neighborhood_size = size;
    this->rel_users_arr = new int[this->datamatrix.nrows];
    this->rel_items = new int[this->datamatrix.ncols*this->datamatrix.nrows];
}

void RatingCalculator::clear_imputated_matrix(){
    for(int i = 0; i < this->datamatrix.nrows*this->datamatrix.ncols; i++){
        this->imputated_matrix.data[i] = this->datamatrix.data[i];
    }
}

void RatingCalculator::imputate_matrix(){
    this->key_neighbors.get_key_neighbors(this->user, this->item,this->datamatrix,this->neighborhood_size,this->datamatrix.nrows,this->datamatrix.ncols,this->rel_users_arr,this->rel_items);
    int rel_use_size = this->key_neighbors.rel_users.size();
    int rel_it_size = this->key_neighbors.rel_items.size();
    int current_user = -1;
    int current_item = -1;
    int curuserindex = 0;
    int curitemindex = 0;
    while(curuserindex < rel_use_size && current_user < this->datamatrix.nrows && current_user >= 0){
            
            while(curitemindex < rel_it_size && current_item < this->datamatrix.ncols && current_item >= 0){
                int matrixrating = datamatrix.get_index(current_user,current_item);
                int rating = datamatrix.data[matrixrating];
                if(rating == 0){
                    float mean_cur_key_neigh = calc_row_mean(this->datamatrix.ncols,current_user,datamatrix);
                    float sum_above = 0.0f;
                    float sum_below = 0.0f;
                    key_neigh_knn.get_key_neighbors(current_user,current_item,datamatrix,this->neighborhood_size,this->datamatrix.nrows,this->datamatrix.ncols,rel_users_arr,rel_items);
                    std::vector<int> key_neighbors_neighbors = key_neigh_knn.rel_users;
                    int key_neigh_neigh = key_neighbors_neighbors[0];
                    for(int x = 0; x < key_neighbors_neighbors.size(); x++){
                        if(key_neigh_neigh != current_user){
                            int simlistindex = simlist.get_index(current_user,key_neigh_neigh);
                            float sim = simlist.data[simlistindex];
                            float mean_key_neigh_neigh = calc_row_mean(this->datamatrix.ncols,key_neigh_neigh,datamatrix);
                            int matrixindex = datamatrix.get_index(key_neigh_neigh,current_item);
                            sum_above += sim*((datamatrix.data[matrixindex]-mean_key_neigh_neigh));
                            sum_below += sim;
                            
                            key_neigh_neigh = key_neighbors_neighbors[x];
                        }
                    }
                if(sum_below == 0.0f){sum_below = 0.001f;}
                float imp_rating = mean_cur_key_neigh+(sum_above/sum_below);
                int impmatindex = imputated_matrix.get_index(current_user,current_item);
                this->imputated_matrix.data[impmatindex] = abs(imp_rating);
                
                }
                curitemindex++;
            }
            curuserindex++;
        }
}

float RatingCalculator::predict_rating(int item){
    this->item = item;
    float rating = this->datamatrix.data[this->datamatrix.get_index(this->user,this->item)];

    if(rating != 0.0f){
        std::cout << "Rating already observed\n";
        return -1.0f;
    }
    else{
        for(int i = 0; i < this->datamatrix.nrows; i++){
            this->rel_users_arr[i] = -1;
        }
        for(int i = 0; i < this->datamatrix.ncols; i++){
            this->rel_items[i] = -1;
        }
        imputate_matrix();
        P.get_key_neighbors(this->user, this->item,this->datamatrix,this->neighborhood_size,this->datamatrix.nrows,this->datamatrix.ncols,this->rel_users_arr,this->rel_items);
        std::vector<int> neighbors = P.rel_users;
        const int pneighsize = P.rel_users.size();
        int neighbordata = -1;
        if(pneighsize > 0) neighbordata = neighbors[0];

        float sum_above = 0.0f;
        float sum_below = 0.0f;
        float mean_user = calc_row_mean(this->datamatrix.ncols,user,datamatrix);
        for(int i = 0; i < pneighsize; i++){
            int simlistindex = this->simlist.get_index(user,neighbordata);
            float sim = simlist.data[simlistindex];
            float mean_neighbor = calc_row_mean(this->datamatrix.ncols,neighbordata,datamatrix);
            float impdata = imputated_matrix.data[imputated_matrix.get_index(neighbordata,item)];
            sum_above += sim*(impdata-mean_neighbor);
            sum_below += sim;
            neighbordata = neighbors[i];
        }
        sum_below = sum_below == 0.0f ? 0.00001f : sum_below;
        float predicted_rating = mean_user+(sum_above/sum_below);
        
        // if(predicted_rating > 5.0){predicted_rating = 5.0;}
        // else if(predicted_rating < 0.0){predicted_rating = 0.0;}
        predicted_rating = predicted_rating > 5.0f ? 5.0f : predicted_rating;
        predicted_rating = predicted_rating < 0.0f ? 0.0f : predicted_rating;
        this->clear_imputated_matrix();
        return predicted_rating;
    }

}

