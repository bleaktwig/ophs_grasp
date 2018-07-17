#include "trip.h"

double trip_score(trip t, vertex *v) {
    // O(vec_size)
    double score = 0.0;
    for (uint i = 0; i < t.list.len; ++i)
        score += v[t.list.items[i]].score;
    return score;
}
bool trip_vfy(trip t, vertex *v, double **dm, uint hotels_n) {
    if (t.list.items[0] >= hotels_n) return true;
    if (t.list.items[t.list.len-1] >= hotels_n) return true;
    double d_assert = 0.0;
    for (uint i = 1; i < t.list.len; ++i)
        d_assert += dm[t.list.items[i-1]][t.list.items[i]];

    return (d_assert > t.tot_len);
}
