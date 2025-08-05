#pragma once
#include <vector>
#include "matrix.h"
class keyNeighbors{
    public:
        std::vector<int> rel_users;
        std::vector<int> rel_items;
        int user;
        int item;
        std::vector<int> get_related_users(int user, int item, RatingMatrix matrix, int nusers, int nitems, int* rel_users_arr);
        std::vector<int> get_related_items(int user, int item, RatingMatrix matrix, std::vector<int> rel_use, int nusers, int nitems, int* rel_items);
        void get_key_neighbors(int user, int item, RatingMatrix matrix, int size, int nusers, int nitems, int* rel_users_arr, int* rel_items_arr);
};