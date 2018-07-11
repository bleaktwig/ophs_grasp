#ifndef GRASP_FILEIO_H
#define GRASP_FILEIO_H

#include <stdio.h>

#include "vertex.h"
#include "trip.h"

void readInput(uint *poisSize, uint *hotelsSize, uint *tripsSize,
               double **tripsLength, struct Vertex **vertices,
               const char *file);
void writeTours(uint tripsSize, struct Trip *tour, const char *file);

#endif
