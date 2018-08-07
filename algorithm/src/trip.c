#include "trip.h"

double trip_score(trip t, vertex *v) {
    // calculate and return the score associated to a given trip.
    double score = 0.0;
    for (uint i = 0; i < t.route.len; ++i)
        score += v[t.route.items[i]].score;
    return score;
}
double tour_score(uint trips_n, trip *t, vertex *v) {
    // calculate and return the score associated to all the trips within a tour.
    double score = 0.0;
    for (uint i = 0; i < trips_n; ++i)
        score += trip_score(t[i], v);
    return score;
}
bool trip_vfy(trip t, vertex *v, double **dm, uint hotels_n) {
    // verify the validity of a given trip.
    if (t.route.items[0] >= hotels_n) return 1;
    if (t.route.items[t.route.len-1] >= hotels_n) return 1;
    double d_assert = 0.0;
    for (uint i = 1; i < t.route.len; ++i)
        d_assert += dm[t.route.items[i-1]][t.route.items[i]];
    return (d_assert > t.tot_len);
}
bool endadd_v(trip *t, vertex *v, uint vp, uint hn, double **dm, bool override) {
    // add a given hotel to the end of a given trip.
    if (vp >= hn) error_handler(30, "");
    if (v[vp].vis && !override) return 1;
    double new_rem_len = t->rem_len;
    if (t->route.len > 0) new_rem_len -= dm[t->route.items[t->route.len-1]][vp];
    if (new_rem_len <= 0.0) return 1;
    { // START TRANSACTION
        uintvec_endadd(&(t->route), vp);
        t->rem_len = new_rem_len;
        v[vp].vis = 1;
    } // END TRANSACTION
    return 0;
}
// TODO: the naming convention for these two next functions is non-explanatory
bool poiadd_v(trip *t, vertex *v, uint vp, uint hn, uint pn, double **dm) {
    // add a given poi to the second-to-last position of a given trip.
    if (vp < hn || vp >= hn + pn) error_handler(31, "");
    if (v[vp].vis) return 1;
    double new_rem_len = t->rem_len;
    new_rem_len -= d_add(t->route.items[t->route.len-2],
                         t->route.items[t->route.len-1],
                         vp, dm);
    if (new_rem_len <= 0.0) return 1;
    { // START TRANSACTION
        uintvec_add(&t->route, t->route.len-1, vp);
        t->rem_len = new_rem_len;
        v[vp].vis = 1;
    } // END TRANSACTION
    return 0;
}
bool add_v(trip *t, uint tp, vertex *v, uint vp, uint hn, uint pn, double **dm) {
    // add a given poi to a given position of a given trip.
    if (vp < hn || vp >= hn + pn) error_handler(32, "");
    if (tp <= 0 || tp >= t->route.len-1) error_handler(33, "");
    if (v[vp].vis) error_handler(34, "");
    double new_rem_len = t->rem_len;
    new_rem_len -= d_add(t->route.items[tp-1], t->route.items[tp], vp, dm);
    if (new_rem_len <= 0.0) return 1;
    { // START TRANSACTION
        uintvec_add(&t->route, tp, vp);
        t->rem_len = new_rem_len;
        v[vp].vis = 1;
    } // END TRANSACTION
    return 0;
}
