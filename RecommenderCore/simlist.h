#pragma once
#include "matrix.h"

RatingMatrix create_simlist(int nusers, int nitems, RatingMatrix matrix);
float calc_row_mean(int nitems, int row, RatingMatrix matrix);
float sim(int nitems, int u, int v, RatingMatrix matrix);