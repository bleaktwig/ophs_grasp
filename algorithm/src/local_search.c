#include "local_search.h"

int cndt_poi_cmp(const void *a, const void *b) {
    // compares two candidate pois by their b_score attribute.
    const cndt_poi *aa = (const cndt_poi *) a;
    const cndt_poi *bb = (const cndt_poi *) b;

    if (isinf(aa->b_score) || isnan(aa->b_score)) {
        if (isinf(bb->b_score) || isnan(bb->b_score))
            return 0;
        return 1;
    }
    if (isinf(bb->b_score) || isnan(bb->b_score))
        return -1;

    if (aa->b_score < bb->b_score) return -1;
    if (aa->b_score > bb->b_score) return 1;
    return 0;
}
void local_search(uint trips_n, uint hotels_n, uint pois_n, uint iter_n,
                  vertex *v, double **d_matrix, trip *tour, uint iter) {
    // performs the local search phase of the grasp algorithm.
    cpoivec cndt_p;
    cpoivec_init(&cndt_p, 1);
    for (uint i = hotels_n; i < hotels_n + pois_n; ++i) {
        if (v[i].vis == false) {
            cndt_poi tmp_poi;
            tmp_poi.v = v[i];
            cpoivec_endadd(&cndt_p, tmp_poi);
        }
    }
    for (uint iter = 0; iter < iter_n; ++iter) {
// === INSERT ==================================================================
// tries to insert one poi into each trip as long as the maximum length of the
//      trip allows it.
// =============================================================================
        if (cndt_p.len == 0) break;
        for (uint t = 0; t < trips_n; ++t) {
            if (cndt_p.len == 0) break;
            for (uint c = 0; c < cndt_p.len; ++c) {
                cndt_p.items[c].b_score = -1.0;
                cndt_p.items[c].b_dis = -1.0;
                cndt_p.items[c].b_trip = -1;
                cndt_p.items[c].b_pos = -1;
            }
            for (uint c = 0; c < cndt_p.len; ++c) {
                for (uint p = 1; p < tour[t].route.len-1; ++p) {
                    double new_len =
                        d_add(tour[t].route.items[p], tour[t].route.items[p],
                              cndt_p.items[c].v.idx, d_matrix);
                    cndt_p.items[c].v.tmp_score = cndt_p.items[c].v.score / new_len;
                    if (cndt_p.items[c].v.tmp_score >= cndt_p.items[c].b_score) {
                        // BEGIN TRANSACTION
                        cndt_p.items[c].b_score = cndt_p.items[c].v.tmp_score;
                        cndt_p.items[c].b_dis = new_len;
                        cndt_p.items[c].b_trip = t;
                        cndt_p.items[c].b_pos = p;
                        // END TRANSACTION
                    }
                }
            }
            qsort(cndt_p.items, cndt_p.len, sizeof(cndt_poi), cndt_poi_cmp);

            if (cndt_p.items[cndt_p.len-1].b_trip  == -1   ||
                cndt_p.items[cndt_p.len-1].b_pos   == -1   ||
                cndt_p.items[cndt_p.len-1].b_score == -1.0 ||
                cndt_p.items[cndt_p.len-1].b_dis   == -1.0
            ) break;
            if (!add_v(&tour[t], cndt_p.items[cndt_p.len-1].b_pos, v,
                                 cndt_p.items[cndt_p.len-1].v.idx,
                                 hotels_n, pois_n, d_matrix)) {
                cpoivec_endpop(&cndt_p);
            }
        }
// === IN-TRIP SWAP ============================================================
// tries to exchange two pois from the same trip as long as this change reduces
//      or maintains the total length of the trip.
// =============================================================================
        for (uint t = 0; t < trips_n; ++t) {
            for (uint p1 = 1; p1 < tour[t].route.len-1; ++p1) {
                for (uint p2 = 1; p2 < tour[t].route.len-1; ++p2) {
                    if (p1 < p2) {
                        double old_len;
                        double new_len;
                        if (p2 - p1 == 1) {
                            old_len =
                                d_matrix[tour[t].route.items[p1-1]][tour[t].route.items[p1]] +
                                d_matrix[tour[t].route.items[p1]][tour[t].route.items[p1+1]] +
                                d_matrix[tour[t].route.items[p2-1]][tour[t].route.items[p2]] +
                                d_matrix[tour[t].route.items[p2]][tour[t].route.items[p2+1]];
                            new_len =
                                d_matrix[tour[t].route.items[p1-1]][tour[t].route.items[p2]] +
                                d_matrix[tour[t].route.items[p2]][tour[t].route.items[p1]] +
                                d_matrix[tour[t].route.items[p2]][tour[t].route.items[p1]] +
                                d_matrix[tour[t].route.items[p1]][tour[t].route.items[p2+1]];
                        }
                        else {
                            old_len =
                                d_matrix[tour[t].route.items[p1-1]][tour[t].route.items[p1]] +
                                d_matrix[tour[t].route.items[p1]][tour[t].route.items[p1+1]] +
                                d_matrix[tour[t].route.items[p2-1]][tour[t].route.items[p2]] +
                                d_matrix[tour[t].route.items[p2]][tour[t].route.items[p2+1]];
                            new_len =
                                d_matrix[tour[t].route.items[p1-1]][tour[t].route.items[p2]] +
                                d_matrix[tour[t].route.items[p2]][tour[t].route.items[p1+1]] +
                                d_matrix[tour[t].route.items[p2-1]][tour[t].route.items[p1]] +
                                d_matrix[tour[t].route.items[p1]][tour[t].route.items[p2+1]];
                        }
                        if (new_len - old_len < 0.0) {
                            trip_exchange_v(&tour[t], p1, p2, v, hotels_n, pois_n, d_matrix);
                        }
                    }
                }
            }
        }
    }
    cpoivec_free(&cndt_p);
    return;
}
