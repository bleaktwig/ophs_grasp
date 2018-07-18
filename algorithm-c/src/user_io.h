#ifndef GRASP_USERIO_H
#define GRASP_USERIO_H

#include <stdio.h>

#include "vertex.h"
#include "trip.h"

void print_in_vars(uint trips_n, double *trips_len, uint hotels_n, uint pois_n, vertex *v);
void print_matrix(uint size, double **d_matrix);
void print_tour(uint trips_n, trip *tour, vertex *v);
// void printHotelScores(unsigned int hotelsSize, struct Vertex *vertices);
// void printTourHotels(unsigned int tripsSize, struct Trip *tour,
//                      double **distancesMatrix);
// void printTours(unsigned int tripsSize, struct Trip *tour);

#endif
