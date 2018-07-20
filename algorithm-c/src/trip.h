#ifndef GRASP_TRIP_H
#define GRASP_TRIP_H

#include "vertex.h"

typedef struct {
    uintvec list;
    double tot_len;
    double rem_len;
} trip;
double trip_score(trip t, vertex *v);
double tour_score(uint trips_n, trip *t, vertex *v);
// bool trip_vfy(trip t, vertex *v, double **dm, uint hotels_n);

#endif
