#include <stdio.h>  // printf and fprintf
#include <stdlib.h> // srand and rand
#include <time.h>   // time()

#include "vertex.h"
#include "trip.h"
#include "hotel_grasp.h"
#include "poi_grasp.h"
#include "file_io.h"
#include "user_io.h"

// TODO: Check that pois visibility is correctly set as true in poi_grasp.c. It
//       looks like there's something wrong there from the output images.

void usage() { // TODO
    fprintf(stderr, "Wrong usage.\nExiting...\n");

    return;
}
int main(int argc, char* argv[]) {
    /* TODO: argument handling
     *  const char* infile
     *      File containing the instance to be ran.
     *  const char* outfile
     *      File where the output will be written.
     *  uint iter_n
     *      Number of iterations of the GRASP algorithm.
     *  uint h_rcl
     *      Size of the RCL used for the hotel greedy randomized construction.
     *  uint p_rcl
     *      Size of the RCL used for the poi greedy randomized construction
     *  uint ls_iter_n
     *      Number of iterations for the poi local search phase.
     *  uint random
     *      unsigned integer defining if a random seed should be used or not.
     *  uint debug
     *      unsigned integer defining the debug output the program should give.
     *        - 0 is only basic output
     *        - 1 is phase correctness verification
     *        - 2 is verbose output
     *        - 3 is absurdly verbose output
     */
    const char *infile;
    const char *outfile;
    uint iters_n;
    uint h_rcl;
    uint p_rcl;
    // uint ls_iter_n;
    uint random;
    uint debug;

    if (argc == 8) {
        infile  = argv[1];
        outfile = argv[2];
        iters_n = atoi(argv[3]);
        h_rcl = atoi(argv[4]);
        p_rcl = atoi(argv[5]);
        random = atoi(argv[6]);
        debug = atoi(argv[7]);
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

    if (!debug) printf("Running on \"%s\"...\n", infile);
// === FILE READING ============================================================
    if (debug) printf("=== READING FILE =================================\n");
    uint trips_n, hotels_n, pois_n;
    double *trips_len;
    vertex *v;
    read_input(infile, &trips_n, &hotels_n, &pois_n, &trips_len, &v);

    if (debug == 2) print_in_vars(trips_n, trips_len, hotels_n, pois_n, v);

// === DISTANCES MATRIX CREATION ===============================================
    if (debug) printf("=== CREATING DISTANCES MATRIX ====================\n");
    double **d_matrix = /*(double**) */malloc(sizeof(double*) * (hotels_n + pois_n));
    for (uint i = 0; i < hotels_n + pois_n; ++i)
        d_matrix[i] = /*(double*) */malloc(sizeof(double) * (hotels_n + pois_n));
    create_d_matrix(d_matrix, hotels_n + pois_n, v);
    if (debug == 3) print_matrix(hotels_n + pois_n, d_matrix);
// === MAIN LOOP ===============================================================
    if (debug) printf("=== CREATING BEST TOUR AND STARTING LOOP =========\n");
    // create best_tour
    trip *best_tour = malloc(sizeof(trip) * (trips_n));
    if (best_tour == NULL) {
        fprintf(stderr, "Not enough memory allocated for the best tour. Exiting...\n");
        exit(1);
    }
    for (uint i = 0; i < trips_n; ++i) {
        uintvec_init(&best_tour[i].list, 2);
        best_tour[i].tot_len = trips_len[i];
        best_tour[i].rem_len = trips_len[i];
    }
    // double best_tour_score = 0.0;

    uint tour_grc_wack_sols = 0;
    for (uint iter = 0; iter < iters_n; ++iter) {
        bool scrap = false;
// === TOUR CREATION ===========================================================
        trip *tour = malloc(sizeof(trip) * (trips_n));
        if (tour == NULL) {
            fprintf(stderr, "Not enough memory allocated for a tour in iter");
            fprintf(stderr, "%d. Exiting...\n", iter);
            exit(1);
        }
        for (uint i = 0; i < trips_n; ++i) {
            uintvec_init(&tour[i].list, 2);
            tour[i].tot_len = trips_len[i];
            tour[i].rem_len = trips_len[i];
        }
        for (uint i = 0; i < hotels_n + pois_n; ++i) v[i].vis = false;
// === TOUR HOTEL SELECTION ====================================================
        if (debug) {
            if (iters_n == 1)
                printf("=== RUNNING TOUR GREEDY RANDOMIZED CONSTRUCTION ==\n");
            else if (iter%(iters_n-1) == 0 && iter != 0)
                printf("=== RUNNING TOUR GREEDY RANDOMIZED CONSTRUCTION ==\n");
        }
        // TODO: There might be something wrong with the last hotel added here.
        if (tour_grc(trips_n, hotels_n, pois_n, h_rcl, v, d_matrix, tour)) {
            tour_grc_wack_sols += 1;
            scrap = true;
        }
// === TOUR POIS SELECTION =====================================================
        if (debug) {
            if (iters_n == 1)
                printf("=== RUNNING TRIP GREEDY RANDOMIZED CONSTRUCTION ==\n");
            else if (iter%(iters_n-1) == 0 && iter != 0)
                printf("=== RUNNING TRIP GREEDY RANDOMIZED CONSTRUCTION ==\n");
        }
        if (!scrap) trip_grc(trips_n, hotels_n, pois_n, p_rcl, v, d_matrix, tour);

// === LOCAL SEARCH ============================================================

// === BEST VS CURRENT TOUR COMPARISON =========================================
        // print_tour(trips_n, tour, v);
        write_output(trips_n, tour, v, outfile);

        // TODO: remember that copying the trip with uintvec is not trivial.
        //       First, I need to copy the variables of the trip (tot_len and rem_len).
        //       then, for each trip, I need to pass each uint from the trips to a
        //       tmp_trip, and then do the same from this tmp_trip to best_trip.
        //       This is done to conserve order.
        for (uint i = 0; i < trips_n; ++i) uintvec_free(&tour[i].list);
        free(tour);
    }

    if (tour_grc_wack_sols > 0)
        printf("    %u/%u solutions were scrapped by the tour grc.\n",
                tour_grc_wack_sols, iters_n);
// === OUTPUT FILE WRITING =====================================================
    // if (!debug) printf("OK!\n");
    // if (!debug) printf("Writing to \"%s\"...    ", outfile);
    //
    // if (!debug) printf("OK!\n"); TODO: uncomment
// === MEMORY RELEASING ========================================================
    if (debug) printf("=== RELEASING MEMORY =============================\n");
    free(trips_len);
    free(v);
    for (uint i = 0; i < hotels_n + pois_n; ++i) free(d_matrix[i]);
    free(d_matrix);
    for (uint i = 0; i < trips_n; ++i) uintvec_free(&best_tour[i].list);
    free(best_tour);

    return 0;
}
