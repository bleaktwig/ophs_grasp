#ifndef GRASP_FILEIO_H
#define GRASP_FILEIO_H

#include <stdio.h> // fprintf(stderr, *)

#include "vertex.h"
// #include "trip.h"

void read_input(const char *file, uint *trips_n, uint *hotels_n, uint *pois_n,
                double **trips_len, vertex **v);
// void writeTours(uint tripsSize, struct Trip *tour, const char *file);

#endif
