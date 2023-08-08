#include "matrix.h"
#include "related.h"
#include "simlist.h"
class RatingCalculator{
    public:
        RatingMatrix datamatrix;
        RatingMatrix imputated_matrix;
        RatingMatrix simlist;
        keyNeighbors key_neighbors;
        keyNeighbors key_neigh_knn;
        keyNeighbors P;
        int* rel_users_arr;
        int* rel_items;
        int user;
        int item;
        int neighborhood_size;
        RatingCalculator() = default;
        RatingCalculator(RatingMatrix data, RatingMatrix simlist, int user, int size);
        void imputate_matrix();
        void clear_imputated_matrix();
        float predict_rating(int item);
};

//int user, int item, int** matrix, float** simlist, int* rel_users_arr, int* rel_items
