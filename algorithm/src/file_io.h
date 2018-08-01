#ifndef GRASP_FILEIO_H
#define GRASP_FILEIO_H

#include "error_io.h"
#include "vertex.h"
#include "trip.h"

void read_input(const char *file, uint *trips_n, uint *hotels_n, uint *pois_n,
                double **trips_len, vertex **v);
void write_output(uint trips_n, trip *tour, vertex *v, const char *file);
#endif
