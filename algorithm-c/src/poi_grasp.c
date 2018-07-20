#include "poi_grasp.h"

void trip_grc(uint trips_n, uint hotels_n, uint pois_n, uint rcl,
              vertex *v, double **d_matrix, trip *tour) {
    vervec cndt_p;
    vervec_init(&cndt_p, pois_n);
    for (uint i = hotels_n; i < hotels_n + pois_n; ++i) vervec_endadd(&cndt_p, v[i]);
    for (uint i = 0; i < trips_n; ++i) {
        while (tour[i].rem_len >= 0.0) {
            for (uint j = 0; j < cndt_p.len; ++j) {
                int len = tour[i].list.len;
                cndt_p.items[j].tmp_score = cndt_p.items[j].score /
                    d_add(tour[i].list.items[len-2], tour[i].list.items[len-1],
                          cndt_p.items[j].idx, d_matrix);
            }
            qsort(cndt_p.items, cndt_p.len, sizeof(vertex), vertex_cmp_asc);

            uint choice = (rcl > 0) ? rand()%rcl : 0;
            uint pos = cndt_p.len - 1 - choice;

            int len = tour[i].list.len;
            double new_rem_len = tour[i].rem_len - d_add(tour[i].list.items[len-2],
                tour[i].list.items[len-1], cndt_p.items[cndt_p.len-1-choice].idx, d_matrix);

            while (new_rem_len < 0.0 && choice != 0) {
                choice -= 1;
                new_rem_len = tour[i].rem_len
                    - d_add(tour[i].list.items[len-2], tour[i].list.items[len-1],
                            cndt_p.items[cndt_p.len-1-choice].idx, d_matrix);
            }
            if (new_rem_len < 0.0) break;

            uint aux_vert = uintvec_endpop(&tour[i].list);
            v[cndt_p.items[pos].idx].vis = true;
            uintvec_endadd(&tour[i].list, vervec_pop(&cndt_p, cndt_p.len-1-choice).idx);
            uintvec_endadd(&tour[i].list, aux_vert);
            tour[i].rem_len = new_rem_len;
        }
    }
    vervec_free(&cndt_p);
    return;
}
