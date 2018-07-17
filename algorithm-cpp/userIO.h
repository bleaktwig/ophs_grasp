#ifndef GRASP_USERIO_H
#define GRASP_USERIO_H

#include <stdio.h>
#include <vector>

#include "vertex.h"
#include "trip.h"

void printVariables(unsigned int tripsSize, double *tripsLength,
                    unsigned int hotelsSize, unsigned int poisSize, struct Vertex *vertices);
void printMatrix(unsigned int hotelsSize, unsigned int poisSize, double **distancesMatrix);
void printHotelScores(unsigned int hotelsSize, struct Vertex *vertices);
void printTourHotels(unsigned int tripsSize, struct Trip *tour,
                     double **distancesMatrix);
void printTours(unsigned int tripsSize, struct Trip *tour);

#endif
