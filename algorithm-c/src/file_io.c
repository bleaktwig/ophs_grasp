#include "file_io.h"

void read_input(const char *file, uint *trips_n, uint *hotels_n, uint *pois_n,
                double **trips_len, vertex **v) {

    FILE *in;
    in = fopen(file, "r");

    if (in == NULL) {
        fprintf(stderr, "input file name \"%s\" is invalid. Exiting...\n", file);
        exit(1);
    }

// === GENERAL PARAMETERS ======================================================
    fscanf(in, "%d %d %d", pois_n, hotels_n, trips_n);
    *pois_n -= 2;
    *hotels_n += 2;

// === TOTAL TOUR AND TRIPS LENGTH =============================================
    double total_tour_len;
    fscanf(in, "%lf", &total_tour_len);

    *trips_len = /*(double *) */malloc(sizeof(double) * (*trips_n));
    if (*trips_len == NULL) {
        fprintf(stderr, "Not enough memory allocated for trips. Exiting...\n");
        exit(1);
    }

    double d_check = 0.0;
    for (uint i = 0; i < *trips_n; ++i) {
        fscanf(in, "%lf", &(*trips_len)[i]);
        d_check += (*trips_len)[i];
    }
    if (d_check >= (total_tour_len * 1.02) || d_check <= (total_tour_len * 0.98)) {
        fprintf(stderr, "The given total tour length doesn't correlate with ");
        fprintf(stderr, "the length of each individual trip. The instance ");
        fprintf(stderr, "given is invalid. Exiting...\n");
        exit(1);
    }
// === VERTICES ================================================================
    *v = /*(vertex *) */malloc(sizeof(vertex) * (*hotels_n + *pois_n));
    if (*v == NULL) {
        fprintf(stderr, "Not enough memory allocated for vertices. Exiting...\n");
        exit(1);
    }


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

    if (out == NULL) {
        fprintf(stderr, "Output file \"%s\" is invalid. Exiting...\n", file);
        exit(1);
    }
    for (uint i = 0; i < trips_n; ++i) {
        for (uint j = 0; j < tour[i].list.len; ++j) {
            fprintf(out, "%u ", v[tour[i].list.items[j]].idx);
        }
        fprintf(out, "\n");
    }
    return;
}
