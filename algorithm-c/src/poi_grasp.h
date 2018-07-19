#ifndef GRASP_POI_H
#define GRASP_POI_H

// #include <algorithm>
// #include <stdlib.h>
// #include <stdio.h>

#include "vertex.h"
#include "trip.h"

void trip_grc(uint trips_n, uint hotels_n, uint pois_n, uint rcl,
              vertex *v, double **d_matrix, trip *tour);
void trip_ls(uint trips_n, uint hotels_n, uint pois_n, uint iter_n,
             vertex *v, double **d_matrix, trip *tour);

#endif
