#include "trip.h"

double trip_score(trip t, vertex *v) {
    // calculates and returns the score associated to a given trip.
    double score = 0.0;
    for (uint i = 0; i < t.route.len; ++i)
        score += v[t.route.items[i]].score;
    return score;
}
double tour_score(uint trips_n, trip *t, vertex *v) {
    // calculates and returns the score associated to all the trips within a tour.
    double score = 0.0;
    for (uint i = 0; i < trips_n; ++i)
        score += trip_score(t[i], v);
    return score;
}
double calc_dist(trip t, double **dm) {
    // calculates and returns the distance of a given trip.
    double distance = 0;
    for (uint i = 0; i < t.route.len-1; ++i) {
        distance += dm[t.route.items[i]][t.route.items[i+1]];
    }
    return distance;
}
bool trip_vfy(trip t, vertex *v, double **dm, uint hotels_n) {
    // verifies the validity of a given trip.
    if (t.route.items[0] >= hotels_n) return 1;
    if (t.route.items[t.route.len-1] >= hotels_n) return 1;
    double d_assert = 0.0;
    for (uint i = 1; i < t.route.len; ++i)
        d_assert += dm[t.route.items[i-1]][t.route.items[i]];
    return (d_assert > t.tot_len);
}
bool endadd_v(trip *t, vertex *v, uint vp, uint hn, double **dm, bool override) {
    // adds a given hotel to the end of a given trip.
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
    // adds a given poi to the second-to-last position of a given trip.
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
    // adds a given poi to a given position of a given trip.
    if (vp < hn) error_handler(32, "");
    if (vp >= hn + pn) error_handler(33, "");
    if (tp <= 0 || tp >= t->route.len) error_handler(34, "");
    if (v[vp].vis) error_handler(35, "");
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
uint rem_v(trip *t, uint tp, vertex *v, uint hn, uint pn, double **dm) {
    // removes a poi from a trip and returns its index
    if (tp <= 0 || tp >= t->route.len-1) error_handler(38, "");
    if (v[t->route.items[tp]].idx < hn) error_handler(36, "");
    if (v[t->route.items[tp]].idx > hn + pn) error_handler(37, "");
    if (!v[t->route.items[tp]].vis) error_handler(39, "");

    double new_rem_len = t->rem_len;
    new_rem_len += dm[v[t->route.items[tp-1]].idx][v[t->route.items[tp]].idx];
    new_rem_len += dm[v[t->route.items[tp]].idx][v[t->route.items[tp+1]].idx];
    new_rem_len -= dm[v[t->route.items[tp-1]].idx][v[t->route.items[tp+1]].idx];
    uint rem_poi;
    { // START TRANSACTION
        rem_poi = uintvec_pop(&t->route, tp);
        v[rem_poi].vis = 0;
        t->rem_len = new_rem_len;
    } // END TRANSACTION

    return rem_poi;
}
bool trip_exchange_v(trip *t, uint tp1, uint tp2, vertex *v, uint hn, uint pn, double **dm) {
    // exchanges two pois inside one trip.
    if (tp2 <= tp1) {
        uint auxtp = tp2;
        tp2 = tp1;
        tp1 = auxtp;
    }
    if (tp1 <= 0 || tp1 >= t->route.len) error_handler(40, "");
    if (tp2 <= 0 || tp2 >= t->route.len) error_handler(40, "");
    if (v[t->route.items[tp1]].idx < hn) error_handler(41, "");
    if (v[t->route.items[tp2]].idx < hn) error_handler(41, "");
    if (v[t->route.items[tp1]].idx > hn + pn) error_handler(42, "");
    if (v[t->route.items[tp2]].idx > hn + pn) error_handler(42, "");
    if (!v[t->route.items[tp1]].vis) error_handler(43, "");
    if (!v[t->route.items[tp2]].vis) error_handler(43, "");

    uint aux_v1, aux_v2;
    { // BEGIN TRANSACTION
        aux_v2 = rem_v(t, tp2, v, hn, pn, dm);
        aux_v1 = rem_v(t, tp1, v, hn, pn, dm);
        if (!add_v(t, tp1, v, aux_v2, hn, pn, dm)) {
            if (!add_v(t, tp2, v, aux_v1, hn, pn, dm)) {
                // pass
            }
            else {
                rem_v(t, tp1, v, hn, pn, dm);
                add_v(t, tp1, v, aux_v1, hn, pn, dm);
                add_v(t, tp2, v, aux_v2, hn, pn, dm);
                return 1;
            }
        }
        else {
            add_v(t, tp1, v, aux_v1, hn, pn, dm);
            add_v(t, tp2, v, aux_v2, hn, pn, dm);
            return 1;
        }
    } // END TRANSACTION
    return 0;
}
