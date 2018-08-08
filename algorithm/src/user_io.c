#include "user_io.h"

void print_in_vars(uint trips_n, double *trips_len,
                   uint hotels_n, uint pois_n, vertex *v) {
    // prints the variables given from the input file.
    printf("------- Trips length: ---------------------\n");
    for (uint i = 0; i < trips_n; ++i)
        printf("index%u: %.2f\n", i, trips_len[i]);
    printf("\n------- Hotels: ---------------------------\n");
    for (uint i = 0; i < hotels_n; ++i)
        printf("hotel%u: %.2f %.2f - %.2f, %d\n", i, v[i].x, v[i].y, v[i].score, v[i].vis);
    printf("\n------- POIs: -----------------------------\n");
    for (uint i = hotels_n; i < hotels_n + pois_n; ++i)
        printf("poi%u: %.2f %.2f - %.2f, %d\n", i, v[i].x, v[i].y, v[i].score, v[i].vis);
    return;
}
void print_matrix(uint size, double **d_matrix) {
    // prints each double in the distances matrix.
    /*
     * May whatever divinity you believe in have mercy on any terminal printing
     * this for a big enough matrix.
     */
    for (uint i = 0; i < size; ++i) {
        for (uint j = 0; j < size; ++j) {
            if (d_matrix[i][j] < 10.0) printf(" %.0f ", d_matrix[i][j]);
            else                       printf("%.0f ",  d_matrix[i][j]);
        }
        printf("\n");
    }
    return;
}
void print_tour(uint trips_n, trip *tour, vertex *v) {
    // prints a given tour in a human-readable format.
    for (uint i = 0; i < trips_n; ++i) {
        printf("-------------------------------------------\n");
        printf("Trip %u\n  score: %.2f\n  rem_len: %.2f/%.2f\nRoute:\n",
                i, trip_score(tour[i], v), tour[i].rem_len, tour[i].tot_len);
        for (uint j = 0; j < tour[i].route.len; ++j) {
            printf("  - %d: (%.2f, %.2f) - %.2f\n",
                    v[tour[i].route.items[j]].idx,
                    v[tour[i].route.items[j]].x,
                    v[tour[i].route.items[j]].y,
                    v[tour[i].route.items[j]].score);
        }
    }
    printf("-------------------------------------------\n");
    printf("Total score collected: %.2f\n", tour_score(trips_n, tour, v));
    return;
}
