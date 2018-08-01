#include "poi_grasp.h"

void trip_grc(uint trips_n, uint hotels_n, uint pois_n, uint rcl,
              vertex *v, double **d_matrix, trip *tour) {
    vervec cndt_p;
    vervec_init(&cndt_p, pois_n);
    for (uint i = hotels_n; i < hotels_n + pois_n; ++i) vervec_endadd(&cndt_p, v[i]);
    for (uint i = 0; i < trips_n; ++i) {
        while (tour[i].rem_len >= 0.0) {
            for (uint j = 0; j < cndt_p.len; ++j) {
                cndt_p.items[j].tmp_score = cndt_p.items[j].score /
                    d_add(tour[i].route.items[tour[i].route.len-2],
                          tour[i].route.items[tour[i].route.len-1],
                          cndt_p.items[j].idx, d_matrix);
            }
            // TODO: If I manage to use qsort with v[idx] then I can change
            //          cndt_h from type vervec to uintvec and save memory.
            qsort(cndt_p.items, cndt_p.len, sizeof(vertex), vertex_cmp_asc);

            if (rcl > cndt_p.len) rcl = cndt_p.len;
            if (cndt_p.len == 0) break;

            uint choice = (rcl > 0) ? cndt_p.len-1 - (rand()%rcl) : 0;
            if (poiadd_v(&tour[i], v, cndt_p.items[choice].idx, hotels_n, pois_n, d_matrix)) break;
            vervec_pop(&cndt_p, choice);
        }
        if (cndt_p.len == 0) break;
    }
    vervec_free(&cndt_p);
    return;
}
