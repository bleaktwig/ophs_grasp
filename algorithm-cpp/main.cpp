#include <stdio.h>
#include <vector>
#include <time.h>
#include <string.h>

#include "vertex.h"
#include "trip.h"
#include "hotelGrasp.h"
#include "poiGrasp.h"
#include "fileIO.h"
#include "userIO.h"

/* TODO: write a description for each function in a standard C manner.
 * TODO: the tour construction algorithm has no encouragement to move around the
 *          solution space, causing many solutions to be curled up in a small
 *          area. Different construction algorithms could be proposed that favor
 *          exploration of the solution space.
 * TODO: tours should be a struct themselves, with a trips vector (or dynamic
 *          array) and a score.
 * TODO: trips should only contain a vertex's index, not the entire struct.
 * TODO: upgrade the file output so that it also shows the total score collected
 *          in each individual trip as well as for the whole tour.
 */

int main(int argc, char* argv[]) {
    /* TODO: argument handling
     *  inFile with a default file chosen if none is given
     *  number of iterations with a default given by average time per iteration
     *  a flag for choosing between a random seed or a given one
     *  amount of iterations to be run
     *  HotelRCLSize with a default of 3
     *  PoiRCLSize with a default of 3
     *  LocalSearchMaxIter with a default of 100
     *  Debug flag with a default of false, with 1 meaning normal and 2 meaning verbose
     */
    uint iterNumber = 1;
    uint HotelRCLSize = 3;
    uint PoiRCLSize = 3;
    uint LocalSearchMaxIter = 100;
    uint debug = 1;

    //srand(time(NULL)); // TODO: a flag should handle this

    const char *inFile;
    const char *outFile;
    if (argc == 3) {
        inFile  = argv[1];
        outFile = argv[2];
    }
    else {
        fprintf(stderr, "Usage:\nExiting...\n"); // TODO: Usage()
        return 1;
    }

    if (!debug) printf("Running on %s... ", inFile);

    // variables used
    uint tripsSize;
    uint hotelsSize;
    uint poisSize;
    double *tripsLength;
    struct Vertex *vertices;

// === FILE READING ============================================================
    readInput(&poisSize, &hotelsSize, &tripsSize,
              &tripsLength, &vertices,
              inFile);
    if (debug) printf("===========================================\n");
    if (debug) printf("FILE READING OK!\n");
    if (debug == 2) printVariables (tripsSize, tripsLength,
                                    hotelsSize, poisSize, vertices);
// === MATRIX FILLING ==========================================================
    double **distancesMatrix = (double**) malloc(sizeof(double*) * (hotelsSize + poisSize));
    for (uint i = 0; i < hotelsSize + poisSize; ++i)
        distancesMatrix[i] = (double*) malloc(sizeof(double) * (hotelsSize + poisSize));
    // TODO: remove (double **) and (double *)
    // TODO: move all memory allocation for the matrix to fillMatrix()
    // TODO: assert that no distanceMatrix pointer is pointing to NULL

    fillMatrix(hotelsSize, poisSize, distancesMatrix);
    if (debug) printf("===========================================\n");
    if (debug) printf("MATRIX FILLING OK!\n");
    if (debug == 3) printMatrix(hotelsSize, poisSize, distancesMatrix);

// === HOTEL SCORE CALCULATION =================================================
    // TODO: picking hotels based on trip score
    calculateHotelScore(hotelsSize, poisSize, vertices, distancesMatrix);
    if (debug) printf("===========================================\n");
    if (debug) printf("HOTEL SCORE CALCULATION OK!\n");
    if (debug == 2) printHotelScores(hotelsSize, vertices);

    // TODO: try - catch
    struct Trip *bestTour = new struct Trip [tripsSize];
    for (uint i = 0; i < tripsSize; ++i) bestTour[i].score = 0.0;
    double bestTourTotalScore = 0.0;

// === MAIN LOOP ===============================================================
    for (uint iter = 0; iter < iterNumber; ++iter) {
        // TODO: try - catch
        struct Trip *tour = new struct Trip [tripsSize];
        for (uint i = 0; i < tripsSize; ++i) {
            tour[i].totalLength = tripsLength[i];
            tour[i].remainingLength = tripsLength[i];
            tour[i].score = 0.0;
        }

// === TOUR HOTEL SELECTION ====================================================
        tourGreedyRandomizedConstruction(
            tripsSize, tour,
            hotelsSize, vertices,
            distancesMatrix,
            HotelRCLSize);
        if (debug == 2 && iter % 100 == 1) {
            printf("===========================================\n");
            printf("iter %d: TOUR HOTEL SELECTION OK!\n", iter);
            printTourHotels(tripsSize, tour, distancesMatrix);
        } // TODO: check that I didn't hurt anything by setting iter % 100 == 1
          //        instead of iter % 100 == 0.
        else if (debug && iter == iterNumber - 1) {
            printf("===========================================\n");
            printf("TOUR HOTEL SELECTION OK!\n");
        }

// === TOUR HOTELS LOCAL SEARCH ================================================
        tourLocalSearch(
            tripsSize, tour,
            hotelsSize, vertices,
            distancesMatrix); // TODO: implement
        // printTourHotels(tripsSize, tour);

// === TOUR POIS SELECTION =====================================================
        std::vector<struct Vertex> candidatePois; // DEBUG: SHIT
        tripGreedyRandomizedConstruction(
            tripsSize, tour,
            hotelsSize, poisSize,
            vertices, candidatePois,
            distancesMatrix,
            PoiRCLSize);

        // for (uint i = 0; i < candidatePois.size(); ++i) {
        //     printf("%d - (%.2f, %.2f) :: %.2f\n",
        //            i, candidatePois[i].x, candidatePois[i].y, candidatePois[i].score);
        // }

        if (debug == 2 && iter % 100 == 1) {
            printf("===========================================\n");
            printf("iter %d: TOUR POI SELECTION OK!\n", iter);
            printTours(tripsSize, bestTour);
        }
        else if (debug && iter == iterNumber - 1) {
            printf("===========================================\n");
            printf("TOUR POI SELECTION OK!\n");
        }

// === TOUR POIS LOCAL SEARCH ==================================================
        tripLocalSearch(
            tripsSize, tour,
            hotelsSize, poisSize, vertices, candidatePois,
            distancesMatrix, LocalSearchMaxIter); // TODO: implement
        if (debug == 2 && iter % 100 == 1) {
            printf("===========================================\n");
            printf("iter %d: TOUR POI LOCAL SEARCH OK!\n", iter);
            printTours(tripsSize, bestTour);
        }
        else if (debug && iter == iterNumber - 1) {
            printf("===========================================\n");
            printf("TOUR POI LOCAL SEARCH OK!\n");
        }

        // TODO: the tour could be improved by shaking the trips as described by
        //          Divsalar et. al.
// === BEST VS CURRENT TOUR COMPARISON =========================================
        double tourTotalScore = 0.0;
        for (uint i = 0; i < tripsSize; ++i)
            tourTotalScore += tour[i].score;
        if (debug == 2 && iter % 100 == 1) {
            printf("===========================================\n");
            printf("current tour score: %.2f\n", tourTotalScore);
            printf("best tour score:    %.2f\n", bestTourTotalScore);
        }
        if (tourTotalScore > bestTourTotalScore) {
            for (uint i = 0; i < tripsSize; ++i)
                bestTour[i] = tour[i]; // DEBUG
            bestTourTotalScore = tourTotalScore;
        }
        delete[] tour;
    }
    if (debug) {
        printf("===========================================\n");
        printf("best found tour in %u iterations:\n", iterNumber);
        printTours(tripsSize, bestTour);
    }
// === OUTPUT FILE WRITING =====================================================
    writeTours(tripsSize, bestTour, outFile);

    if (debug) printf("===========================================\n");
    if (debug) printf("OUTPUT FILE WRITING OK!\n");
// === MEMORY RELEASING ========================================================
    // TODO: move to it's own function maybe?

    free(tripsLength);
    free(vertices);
    for (uint i = 0; i < hotelsSize + poisSize; ++i) free(distancesMatrix[i]);
    free(distancesMatrix);
    delete[] bestTour;

    if (debug) printf("===========================================\n");
    if (debug) printf("MEMORY RELEASING OK!\n");
    if (debug) printf("===========================================\n");

    if (!debug) printf("OK!\n");

    return 0;
}

/*
procedure GRASP(max_iter, seed):
    Read_input(); [1]
    best_solution = null;
    for k = 0,..., max_iter do:
        solution = Greedy_randomized_construction(seed);
        if solution is not feasible then: [2]
            solution = Repair(solution); [3]
        end;
        solution = Local_search(solution);
        Update_solution(solution, best_solution);
    end;
    return(best_solution);
end GRASP;

procedure Greedy_randomized_construction(seed):
    solution = null;
    Initialize the set of candidate elements; [4]
    Evaluate the incremental cost of candidate elements; [5]
    while there exists at least one candidate element do:
        Build the restricted_candidate_list(RCL); [6]
        Select an element s from RCL at random;
        solution = solution + s;
        Update the set of candidate elements;
        Reevaluate the incremental costs;
    end;
    return solution;
end Greedy_randomized_construction;

procedure Local_search(solution): [7]
    while solution is not locally optimal do:
        find solution' in the neighborhood of solution with f(solution') < f(solution);
        solution = solution';
    end;
    return solution;
end Local_search;
*/
