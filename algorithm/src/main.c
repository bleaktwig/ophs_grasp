#include <stdio.h>  // printf and fprintf
#include <stdlib.h> // srand and rand
#include <time.h>   // time()

#include "vertex.h"
#include "trip.h"
#include "hotel_grasp.h"
#include "poi_grasp.h"
#include "local_search.h"
#include "file_io.h"
#include "user_io.h"

void usage() {
    fprintf(stderr, "\n");
    fprintf(stderr, "usage: ophs_grasp infile outfile iter_n h_rcl p_rcl ");
    fprintf(stderr, "ls_iter_n random debug\n");
    fprintf(stderr, "  - const char*  infile:    ");
    fprintf(stderr, "    the input file\n");
    fprintf(stderr, "  - const char*  outfile:   ");
    fprintf(stderr, "    the output file\n");
    fprintf(stderr, "  - unsigned int iter_n:    ");
    fprintf(stderr, "    number of iterations the program should run\n");
    fprintf(stderr, "  - unsigned int h_rcl:     ");
    fprintf(stderr, "    rcl size for the hotel construction algorithm\n");
    fprintf(stderr, "  - unsigned int p_rcl:     ");
    fprintf(stderr, "    rcl size for the poi construction algorithm\n");
    fprintf(stderr, "  - unsigned int ls_iter_n: ");
    fprintf(stderr, "    number of iterations for the local search ");
    fprintf(stderr, "algorithm\n");
    fprintf(stderr, "  - unsigned int random:    ");
    fprintf(stderr, "    a flag telling the program to use a random ");
    fprintf(stderr, "seed\n");
    fprintf(stderr, "  - unsigned int debug:     ");
    fprintf(stderr, "    an integer defining how much output the program ");
    fprintf(stderr, "should give\n");
    fprintf(stderr, "\n");
    return;
}
int main(int argc, char* argv[]) {
    const char *infile;
    const char *outfile;
    uint iters_n;
    uint h_rcl;
    uint p_rcl;
    uint ls_iter_n;
    uint random;
    uint debug;

    if (argc == 9) {
        // TODO: datatype checking
        infile  = argv[1];
        outfile = argv[2];
        iters_n = atoi(argv[3]);
        h_rcl = atoi(argv[4]);
        p_rcl = atoi(argv[5]);
        ls_iter_n = atoi(argv[6]);
        random = atoi(argv[7]);
        debug = atoi(argv[8]);
    }
    else {
        usage();
        return 1;
    }
    if (random) {
        uint seed = time(NULL);
        srand(seed);
        if (debug) printf("Using the random seed %d\n", seed);
    }

    if (!debug) printf("Running on \"%s\" with %u iterations...\n", infile, iters_n);
// === FILE READING ============================================================
    if (debug) printf("=== READING FILE =================================\n");
    uint trips_n, hotels_n, pois_n;
    double *trips_len;
    vertex *v;
    read_input(infile, &trips_n, &hotels_n, &pois_n, &trips_len, &v);

    if (debug == 2) print_in_vars(trips_n, trips_len, hotels_n, pois_n, v);
// === DISTANCES MATRIX CREATION ===============================================
    if (debug) printf("=== CREATING DISTANCES MATRIX ====================\n");
    double **d_matrix = (double**) malloc(sizeof(double*) * (hotels_n + pois_n));
    for (uint i = 0; i < hotels_n + pois_n; ++i)
        d_matrix[i] = (double*) malloc(sizeof(double) * (hotels_n + pois_n));
    create_d_matrix(d_matrix, hotels_n + pois_n, v);
    if (debug == 3) print_matrix(hotels_n + pois_n, d_matrix);
// === MAIN LOOP ===============================================================
    if (debug) printf("=== CREATING BEST TOUR AND STARTING LOOP =========\n");
    // create best_tour
    trip *best_tour = (trip*) malloc(sizeof(trip) * (trips_n));
    if (best_tour == NULL) {
        fprintf(stderr, "Not enough memory allocated for the best tour. Exiting...\n");
        exit(1);
    }
    for (uint i = 0; i < trips_n; ++i) {
        uintvec_init(&best_tour[i].route, 2);
        best_tour[i].tot_len = trips_len[i];
        best_tour[i].rem_len = trips_len[i];
    }
    double best_tour_score = -1.0;

    uint tour_grc_wack_sols = 0;
    for (uint iter = 0; iter < iters_n; ++iter) {
        bool scrap = false;
// === TOUR CREATION ===========================================================
        trip *tour = (trip*) malloc(sizeof(trip) * (trips_n));
        if (tour == NULL) {
            fprintf(stderr, "Not enough memory allocated for a tour in iter");
            fprintf(stderr, "%d. Exiting...\n", iter);
            exit(1);
        }
        for (uint i = 0; i < trips_n; ++i) {
            uintvec_init(&tour[i].route, 2);
            tour[i].tot_len = trips_len[i];
            tour[i].rem_len = trips_len[i];
        }
        for (uint i = 0; i < hotels_n + pois_n; ++i) v[i].vis = false;
// === TOUR HOTEL SELECTION ====================================================
        if (tour_grc(trips_n, hotels_n, pois_n, h_rcl, v, d_matrix, tour)) {
            tour_grc_wack_sols += 1;
            scrap = true;
        }
// === TOUR POIS SELECTION =====================================================
        if (!scrap) trip_grc(trips_n, hotels_n, pois_n, p_rcl, v, d_matrix, tour);
// === LOCAL SEARCH ============================================================
        // TODO: this is where we are now
        // if (!scrap) local_search(trips_n, hotels_n, pois_n, ls_iter_n, v, d_matrix, tour);
        // print_tour(trips_n, tour, v);
        // for (uint i = 0; i < trips_n; ++i)
            // printf("%u: %d\n", i, trip_vfy(tour[i], v, d_matrix, hotels_n));
        // print_in_vars(trips_n, trips_len, hotels_n, pois_n, v);
// === BEST VS CURRENT TOUR COMPARISON =========================================
        double tour_score_precalc = tour_score(trips_n, tour, v);
        if (!scrap && best_tour_score < tour_score_precalc) {
            best_tour_score = tour_score_precalc;
            uintvec tmp_trip;
            uintvec_init(&tmp_trip, 2);
            for (uint i = 0; i < trips_n; ++i) {
                best_tour[i].rem_len = tour[i].rem_len;
                for (uint j = 0; best_tour[i].route.len != 0; ++j)
                    uintvec_endpop(&best_tour[i].route);
                for (uint j = 0; tour[i].route.len != 0; ++j)
                    uintvec_endadd(&tmp_trip, uintvec_endpop(&tour[i].route));
                for (uint j = 0; tmp_trip.len != 0; ++j)
                    uintvec_endadd(&best_tour[i].route, uintvec_endpop(&tmp_trip));
            }
            uintvec_free(&tmp_trip);
            if (debug) printf("new best tour score: %.2f\n", best_tour_score);
        }
        for (uint i = 0; i < trips_n; ++i) uintvec_free(&tour[i].route);
        free(tour);
    }

    if (tour_grc_wack_sols > 0)
        printf("    %u/%u solutions were scrapped by the tour grc.\n",
                tour_grc_wack_sols, iters_n);
    printf("    The best solution found has a score of: %.2f\n",
            tour_score(trips_n, best_tour, v));
// === OUTPUT FILE WRITING =====================================================
    write_output(trips_n, best_tour, v, outfile);
// === MEMORY RELEASING ========================================================
    if (debug) printf("=== RELEASING MEMORY =============================\n");
    free(trips_len);
    free(v);
    for (uint i = 0; i < hotels_n + pois_n; ++i) free(d_matrix[i]);
    free(d_matrix);
    for (uint i = 0; i < trips_n; ++i) uintvec_free(&best_tour[i].route);
    free(best_tour);
    return 0;
}
