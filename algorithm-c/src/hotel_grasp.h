#ifndef GRASP_HOTEL_H
#define GRASP_HOTEL_H

// #include <algorithm>
#include <float.h>
#include <stdlib.h>
#include <stdio.h> // DEBUG

#include "vertex.h"
#include "trip.h"

bool tour_grc(uint trips_n, uint hotels_n, uint pois_n, uint rcl,
              vertex *v, double **d_matrix, trip *tour);
void tour_ls(uint trips_n, uint hotels_n, uint pois_n, uint iter_n,
             vertex *v, double **d_matrix, trip *tour);

#endif
