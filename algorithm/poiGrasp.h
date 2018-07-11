#ifndef GRASP_POI_H
#define GRASP_POI_H

#include <vector>
#include <algorithm>
#include <stdlib.h>

#include "vertex.h"
#include "trip.h"

void tripGreedyRandomizedConstruction(
        unsigned int tripsSize, struct Trip *tour,
        unsigned int hotelsSize, unsigned int poisSize, struct Vertex *v,
        double **distancesMatrix,
        unsigned int RCLSize);
void tripLocalSearch(unsigned int tripsSize, struct Trip *tour,
        unsigned int hotelsSize, unsigned int poisSize, struct Vertex *v,
        double **distancesMatrix, unsigned int maxIter);



#endif
