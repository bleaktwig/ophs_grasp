#include "trip.h"

double trip_score(trip t, vertex *v) {
    double score = 0.0;
    for (uint i = 0; i < t.route.len; ++i)
        score += v[t.route.items[i]].score;
    return score;
}
double tour_score(uint trips_n, trip *t, vertex *v) {
    double score = 0.0;
    for (uint i = 0; i < trips_n; ++i)
        score += trip_score(t[i], v);
    return score;
}
bool trip_vfy(trip t, vertex *v, double **dm, uint hotels_n) {
    if (t.route.items[0] >= hotels_n) return 1;
    if (t.route.items[t.route.len-1] >= hotels_n) return 1;
    double d_assert = 0.0;
    for (uint i = 1; i < t.route.len; ++i)
        d_assert += dm[t.route.items[i-1]][t.route.items[i]];

    return (d_assert > t.tot_len);
}
bool endadd_v(trip *t, vertex *v, uint vp, double **dm, bool override) {
    // TODO: assert that vp < hotels_n since this should only be used for hotels
    if (v[vp].vis && !override) return 1;
    double new_rem_len = t->rem_len;
    if (t->route.len > 0) {
        new_rem_len -= dm[t->route.items[t->route.len-1]][vp];
        if (new_rem_len <= 0.0) return 1;
    }
    uintvec_endadd(&(t->route), vp);
    t->rem_len = new_rem_len;
    v[vp].vis = 1;
    return 0;
}
bool poiadd_v(trip *t, vertex *v, uint vp, double **dm) {
    // TODO: assert that vp > hotels_n && vp < hotels_n + trips_n since this
    //          should only be used for pois and to avoid segfault
    if (v[vp].vis) return 1;
    double new_rem_len = t->rem_len;
    // calc new_rem_len
    new_rem_len -= d_add(t->route.items[t->route.len-2],
                         t->route.items[t->route.len-1],
                         vp, dm);
    // assert >=0.0
    if (new_rem_len <= 0.0) return 1;
    // add poi and update data
    uint aux_v = uintvec_endpop(&t->route);
    uintvec_endadd(&t->route, vp);
    uintvec_endadd(&t->route, aux_v);
    t->rem_len = new_rem_len;
    v[vp].vis = 1;
    return 0;
}

//bool add_v(trip t, uint p, vertex *v, double **dm);
