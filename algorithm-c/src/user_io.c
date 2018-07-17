#include "user_io.h"

void print_in_vars(uint trips_n, double *trips_len,
                   uint hotels_n, uint pois_n, vertex *v) {
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
    for (uint i = 0; i < size; ++i) {
        for (uint j = 0; j < size; ++j) {
            if (d_matrix[i][j] < 10.0) printf(" %.0f ", d_matrix[i][j]);
            else                       printf("%.0f ",  d_matrix[i][j]);
        }
        printf("\n");
    }
    return;
}

// void printMatrix(unsigned int hotelsSize, unsigned int poisSize, double **distancesMatrix) {
//     /*
//      * prints all the values in the distances matrix for debugging purposes.
//      */
//     for (unsigned int i = 0; i < hotelsSize + poisSize; ++i) {
//         for (unsigned int j = 0; j < hotelsSize + poisSize; ++j) {
//             if (distancesMatrix[i][j] < 10.0)
//                 printf(" %.2f ", distancesMatrix[i][j]);
//             else
//                 printf("%.2f ", distancesMatrix[i][j]);
//         }
//         printf("\n");
//     }
//     return;
// }
// void printHotelScores(unsigned int hotelsSize, struct Vertex *vertices) {
//     for (unsigned int i = 0; i < hotelsSize; ++i)
//         printf("%d: (%.2f,%.2f) %.2f\n",
//                i, vertices[i].x, vertices[i].y, vertices[i].score);
//     return;
// }
// void printTourHotels(unsigned int tripsSize, struct Trip *tour,
//                      double **distancesMatrix) {
//     /*
//      * TODO: this is the variable we are optimizing in the construction of each
//      *       tour. When analyzing each solution this is what we need to compare
//      *       between solutions, and when tuning the RCLSize parameter this is
//      *       one of the best comparing factors before actually building each
//      *       trip.
//      */
//     double usableDistance = 0;
//     for (unsigned int i = 0; i < tripsSize; ++i) {
//         printf("%d(%.2f,%.2f) - %d(%.2f,%.2f), %.2f - %.2f = %.2f\n",
//             tour[i].start.index, tour[i].start.x, tour[i].start.y,
//             tour[i].end.index, tour[i].end.x, tour[i].end.y,
//             tour[i].totalLength,
//             distancesMatrix[tour[i].start.index][tour[i].end.index],
//             tour[i].remainingLength);
//         usableDistance += tour[i].remainingLength;
//     }
//     printf("usable distance: %.2f\n", usableDistance);
//     return;
// }
// void printTours(unsigned int tripsSize, struct Trip *tour) {
//     double totalScore = 0.0;
//     for (unsigned int i = 0; i < tripsSize; ++i) {
//         totalScore += tour[i].score;
//         printf("-------------------------------------------\n");
//         printf("Trip %u\nscore: %.2f\nremLength: %.2f\n",
//                i, tour[i].score, tour[i].remainingLength);
//         printf("- hotel%d: (%.2f, %.2f)\n",
//                tour[i].start.index, tour[i].start.x, tour[i].start.y);
//         for (unsigned int j = 0; j < tour[i].poiList.size(); ++j)
//             printf("  - poi%d: (%.2f, %.2f) - %.2f\n",
//                    tour[i].poiList[j].index,
//                    tour[i].poiList[j].x,
//                    tour[i].poiList[j].y,
//                    tour[i].poiList[j].score);
//         printf("- hotel%d: (%.2f, %.2f)\n",
//                tour[i].end.index, tour[i].end.x, tour[i].end.y);
//     }
//     printf("total score: %.2f\n", totalScore);
//     return;
// }
