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
            // printf("%u ", v[i].idx);
            cndt_poi tmp_poi;
            tmp_poi.v = v[i];
            // tmp_poi.b_score = -1.0;
            // tmp_poi.b_dis = -1;
            // tmp_poi.b_trip = -1;
            // tmp_poi.b_pos = -1;
            cpoivec_endadd(&cndt_p, tmp_poi);
        }
    }
    // print_tour(trips_n, tour, v);
    // printf("\n");
    // for (uint i = 0; i < cndt_p.len; ++i) {
    //     printf("%u - vis:%u\n", cndt_p.items[i].v.idx, cndt_p.items[i].v.vis);
    // }
    // printf("\n");

    /*
     *  TODO: A better insertion algorithm would work like this:
     *          - for each trip
     *          - for each candidate poi
     *          - for each position in trip
     *          - add every candidate poi that can be added to the current trip in
     *              an order that maximizes the tmp_score variable.
     *  When I get the time I should try this algorithm, but it might over-optimize.
     */
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
                // DEBUG: WHY LEN-2 BEFORE?
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
            // printf("in trip %u with remaining lenght %.2f:\n", t, tour[t].rem_len);
            // for (uint i = cndt_p.len-1; i > cndt_p.len-6; --i) {
            //     printf("  - poi%u can be added in %u. score: %.2f, distance: %.2f\n",
            //            cndt_p.items[i].v.idx, cndt_p.items[i].b_pos,
            //            cndt_p.items[i].b_score, cndt_p.items[i].b_dis);
            // }
            // printf("added: %d\n", !add_v(&tour[t], cndt_p.items[cndt_p.len-1].b_pos, v,
            //                      cndt_p.items[cndt_p.len-1].v.idx,
            //                      hotels_n, pois_n, d_matrix));

            // printf("poi%u:\n  score: %.2f\n  dist:  %.2f\n  trip:  %u\n  pos:   %u\n",
            //     cndt_p.items[cndt_p.len-1].v.idx,
            //     cndt_p.items[cndt_p.len-1].b_score,
            //     cndt_p.items[cndt_p.len-1].b_dis,
            //     cndt_p.items[cndt_p.len-1].b_trip,
            //     cndt_p.items[cndt_p.len-1].b_pos
            // );
            if (cndt_p.items[cndt_p.len-1].b_trip  == -1   ||
                cndt_p.items[cndt_p.len-1].b_pos   == -1   ||
                cndt_p.items[cndt_p.len-1].b_score == -1.0 ||
                cndt_p.items[cndt_p.len-1].b_dis   == -1.0
            ) break;
            if (!add_v(&tour[t], cndt_p.items[cndt_p.len-1].b_pos, v,
                                 cndt_p.items[cndt_p.len-1].v.idx,
                                 hotels_n, pois_n, d_matrix)) {
                // printf("poi %u added to trip %u in position %u\n",
                //         cndt_p.items[cndt_p.len-1].v.idx, t,
                //         cndt_p.items[cndt_p.len-1].b_pos);
                        // print visibility to assert
                // printf("  poi's visibility is: %u\n",
                //         v[cndt_p.items[cndt_p.len-1].v.idx].vis);
                // print validity of trip to assert
                // printf("  trip's validity is: %d\n",
                //         !trip_vfy(tour[t], v, d_matrix, hotels_n));
                // remove the poi from the candidate pois list
                cpoivec_endpop(&cndt_p);
            }
            // else {
            //     printf("poi %u was not added to trip %u\n",
            //             cndt_p.items[cndt_p.len-1].v.idx, t);
            // }
            //     bool add_v(trip *t, uint tp, vertex *v, uint vp, uint hn, uint pn, double **dm) {
            // add the poi (add_v function asserts that it can be added), set v.vis
            //      to zero and remove from cndt_p.
            // DEBUG: remember to assert that cndt_p.len != 0 every once in a while
            //          and to check it's size constantly.
            // printf("valid: %d\n", !trip_vfy(tour[t], v, d_matrix, hotels_n));
        }
        // printf("----------------------------------------\n");
        // print_tour(trips_n, tour, v);
        // DEBUG: SOMETHING SEEMS TO BE WRONG WITH THE REMAINING DISTANCE
    }
    cpoivec_free(&cndt_p);
    return;
}
// // === INSERT ==================================================================
//         for (uint p = 0; p < cndt_p.len; ++p) {
//             for (uint i = 0; i < trips_n; ++i) {
//                 for (uint j = 0; j < tour[i].route.len-2; ++j) {
//                     cndt_p.items[p].v.tmp_score = cndt_p.items[p].v.score /
//                         d_add(tour[i].route.items[j], tour[i].route.items[j+1],
//                               cndt_p.items[p].v.idx, d_matrix);
//                     if (cndt_p.items[p].b_score <= cndt_p.items[p].v.tmp_score) {
//                         cndt_p.items[p].b_score = cndt_p.items[p].v.tmp_score;
//                         cndt_p.items[p].b_dis =
//                             d_add(tour[i].route.items[j], tour[i].route.items[j+1],
//                                   cndt_p.items[p].v.idx, d_matrix);
//                         cndt_p.items[p].b_trip = i;
//                         cndt_p.items[p].b_pos = j;
//                     }
//                 }
//             }
//         }
//         // for (uint i = 0; i < cndt_p.len; ++i)
//         //     printf("%u ", cndt_p.items[i].v.idx);
//         // printf("\n");
//         qsort(cndt_p.items, cndt_p.len, sizeof(cndt_poi), cndt_poi_cmp);
//         // for (uint i = 0; i < cndt_p.len; ++i)
//         //     printf("%u ", cndt_p.items[i].v.idx);
//         // printf("\n\n");
//
//         // print_tour(trips_n, tour, v);
//         // for (uint p = 0; p < cndt_p.len; ++p) {
//         //     printf("poi %u (%.2f,%.2f):\n - score: %.2f\n - distance: %.2f\n - position: %u, %u\n",
//         //            cndt_p.items[p].v.idx, cndt_p.items[p].v.x, cndt_p.items[p].v.y,
//         //            cndt_p.items[p].b_score, cndt_p.items[p].b_dis,
//         //            cndt_p.items[p].b_trip, cndt_p.items[p].b_pos);
//         // }
//         // print_tour(trips_n, tour, v);
//         while (true) {
//             uint top = cndt_p.len-1;
//             if (cndt_p.len == 0) break;
//             double new_rem_len = tour[cndt_p.items[top].b_trip].rem_len - cndt_p.items[top].b_dis;
//             if (new_rem_len <= 0.0) break;
//             tour[cndt_p.items[top].b_trip].rem_len = new_rem_len;
//             v[cndt_p.items[top].v.idx].vis = true;
//             // cndt_poi tmp = cpoivec_endpop(&cndt_p);
//             uintvec_add(&tour[cndt_p.items[top].b_trip].route, cndt_p.items[top].b_pos,
//                         cpoivec_endpop(&cndt_p).v.idx); // DEBUG!!
//             break;
//         }
//         // print_tour(trips_n, tour, v);
//         // for (uint i = 0; i < cndt_p.len; ++i)
//         //     printf("%u ", cndt_p.items[i].v.idx);
//         // printf("\n\n");
//
//         // print_tour(trips_n, tour, v);
//         // for (uint p = 0; p < cndt_p.len; ++p) {
//         //     printf("poi %u (%.2f,%.2f):\n - score: %.2f\n - distance: %.2f\n - position: %u, %u\n",
//         //            cndt_p.items[p].v.idx, cndt_p.items[p].v.x, cndt_p.items[p].v.y,
//         //            cndt_p.items[p].b_score, cndt_p.items[p].b_dis,
//         //            cndt_p.items[p].b_trip, cndt_p.items[p].b_pos);
//         // }
//     }
// // TODO: MOVE-BEST =============================================================
// // TODO: TWO-OPT ===============================================================
// // TODO: SWAP-TRIPS ============================================================
// // TODO: EXTRACT-INSERT ========================================================
// // TODO: EXTRACT2-INSERT =======================================================
// // TODO: EXTRACT5-INSERT =======================================================
// // TODO: EXTRACT-MOVE-INSERT ===================================================
// // TODO: REPLACEMENT ===========================================================
//     cpoivec_free(&cndt_p);
//     return;
// }
