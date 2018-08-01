#ifndef GRASP_TRIP_H
#define GRASP_TRIP_H

#include "error_io.h"
#include "vertex.h"

typedef struct {
    uintvec route;
    double tot_len;
    double rem_len;
} trip;
double trip_score(trip t, vertex *v);
double tour_score(uint trips_n, trip *t, vertex *v);
bool trip_vfy(trip t, vertex *v, double **dm, uint hotels_n);
// TODO: trip new_trip(double tot_len);
// TODO: trip del_trip(trip *t);
bool endadd_v(trip *t, vertex *v, uint vp, uint hn, double **dm, bool override);
bool poiadd_v(trip *t, vertex *v, uint vp, uint hn, uint pn, double **dm);
bool add_v(trip *t, uint tp, vertex *v, uint vp, uint hn, uint pn, double **dm);

#endif
