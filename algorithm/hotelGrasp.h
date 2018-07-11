#ifndef GRASP_HOTEL_H
#define GRASP_HOTEL_H


#include <vector>
#include <algorithm>
#include <stdlib.h>

#include "vertex.h"
#include "trip.h"

void tourGreedyRandomizedConstruction(
        unsigned int tripsSize, struct Trip *tour,
        unsigned int hotelsSize/*, unsigned int poisSize*/, struct Vertex *v,
        double **distancesMatrix,
        unsigned int RCLSize);
void tourLocalSearch(
        unsigned int tripsSize, struct Trip *tour,
        unsigned int hotelsSize/* unsigned int poisSize*/, struct Vertex *v,
        double **distancesMatrix);


#endif
