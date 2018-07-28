#include "hotel_grasp.h"

bool tour_grc(uint trips_n, uint hotels_n, uint pois_n, uint rcl,
              vertex *v, double **d_matrix, trip *tour) {
    if (endadd_v(&tour[0], v, 0, d_matrix, 0)) return 1;

    vervec cndt_h;
    vervec_init(&cndt_h, hotels_n - 2);
    for (uint i = 2; i < hotels_n; ++i) vervec_endadd(&cndt_h, v[i]);

    for (uint i = 0; i < trips_n - 1; ++i) {
        for (int j = 0; j < cndt_h.len; ++j) {
            cndt_h.items[j].tmp_score = d_add(tour[i].route.items[0], 1, cndt_h.items[j].idx, d_matrix);
        }
        // TODO: If I manage to use qsort with v[idx] then I can I can change
        //          cndt_h from type vervec to uintvec and save memory.
        qsort(cndt_h.items, cndt_h.len, sizeof(vertex), vertex_cmp_desc);

        if (rcl > cndt_h.len - 1) rcl = cndt_h.len - 1;
        uint choice = (rcl > 0) ? cndt_h.len-1 - (rand()%rcl) : 0;
        if (endadd_v(&tour[i], v, cndt_h.items[choice].idx, d_matrix, 0)) return 1;
        if (endadd_v(&tour[i+1], v, cndt_h.items[choice].idx, d_matrix, 1)) return 1;

        vervec_pop(&cndt_h, choice);
    }
    if (endadd_v(&tour[trips_n-1], v, 1, d_matrix, 0)) return 1;
    vervec_free(&cndt_h);

    return 0;
}
