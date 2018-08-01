#include "file_io.h"

void read_input(const char *file, uint *trips_n, uint *hotels_n, uint *pois_n,
                double **trips_len, vertex **v) {

    FILE *in;
    in = fopen(file, "r");

    if (in == NULL) error_handler(1, file);

// === GENERAL PARAMETERS ======================================================
    fscanf(in, "%d %d %d", pois_n, hotels_n, trips_n);
    *pois_n -= 2;
    *hotels_n += 2;

// === TOTAL TOUR AND TRIPS LENGTH =============================================
    double total_tour_len;
    fscanf(in, "%lf", &total_tour_len);

    *trips_len = (double *) malloc(sizeof(double) * (*trips_n));
    if (*trips_len == NULL) error_handler(0, "file_io");

    double d_check = 0.0;
    for (uint i = 0; i < *trips_n; ++i) {
        fscanf(in, "%lf", &(*trips_len)[i]);
        d_check += (*trips_len)[i];
    }
    if (d_check >= (total_tour_len * 1.02) || d_check <= (total_tour_len * 0.98))
        error_handler(2, "");
// === VERTICES ================================================================
    *v = (vertex *) malloc(sizeof(vertex) * (*hotels_n + *pois_n));
    if (*v == NULL) error_handler(0, "file_io");

    for (uint i = 0; i < *hotels_n + *pois_n; ++i) {
        fscanf(in, "%lf %lf %lf", &(*v)[i].x, &(*v)[i].y, &(*v)[i].score);
        (*v)[i].idx = i;
        (*v)[i].vis = false;
    }

// === DONE ====================================================================
    fclose(in);
    return;
}
void write_output(uint trips_n, trip *tour, vertex *v, const char *file) {

    FILE *out;
    out = fopen(file, "w");

    if (out == NULL) error_handler(6, file);
    for (uint i = 0; i < trips_n; ++i) {
        for (uint j = 0; j < tour[i].route.len; ++j)
            fprintf(out, "%u ", v[tour[i].route.items[j]].idx);
        fprintf(out, "\n");
    }
    fclose(out);
    return;
}
