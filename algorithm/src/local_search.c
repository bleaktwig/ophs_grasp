#include "local_search.h"

int cndt_poi_cmp(const void *a, const void *b) {
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
    cpoivec cndt_p;
    cpoivec_init(&cndt_p, 1);
    for (uint i = hotels_n; i < hotels_n + pois_n; ++i) {
        if (v[i].vis == false) {
            cndt_poi tmp_poi;
            tmp_poi.v = v[i];
            // tmp_poi.b_score = -1.0;
            // tmp_poi.b_dis = -1;
            // tmp_poi.b_trip = -1;
            // tmp_poi.b_pos = -1;
            cpoivec_endadd(&cndt_p, tmp_poi);
        }
    }
    for (uint iter = 0; iter < iter_n; ++iter) {
// === INSERT ==================================================================
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
    // for each trip
        // for each poi in trip
            // check if swapping the poi to another position inside the trip can
            //      improve the rem_len of the entire trip
            // swap the first two pois found that improve the rem_len variable


    }
    cpoivec_free(&cndt_p);
    return;
}
