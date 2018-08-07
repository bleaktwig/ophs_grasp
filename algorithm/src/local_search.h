#ifndef LOCAL_SEARCH_H
#define LOCAL_SEARCH_H

#include <stdio.h> // DEBUG
#include "user_io.h" // DEBUG

#include "vertex.h"
#include "trip.h"

typedef struct {
    vertex v;
    double b_score;
    double b_dis;
    int b_trip;
    int b_pos;
} cndt_poi;

CADTS_VECTOR(cpoivec,cndt_poi);

int cndt_poi_cmp(const void *a, const void *b);
void local_search(uint trips_n, uint hotels_n, uint pois_n, uint iter_n,
                  vertex *v, double **d_matrix, trip *tour, uint iter);

#endif
