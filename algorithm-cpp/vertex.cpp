#include "vertex.h"

double d(struct Vertex a, struct Vertex b, double **distancesMatrix) {
    if (distancesMatrix[a.index][b.index] == -1.0)
        distancesMatrix[a.index][b.index] =
            sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
    return distancesMatrix[a.index][b.index];
}
void fillMatrix(unsigned int hotelsSize, unsigned int poisSize,
                double **distancesMatrix) {
    /*
     * fills the distance matrix with -1.0.
     */
    for (unsigned int i = 0; i < hotelsSize + poisSize; ++i) {
        for (unsigned int j = 0; j < hotelsSize + poisSize; ++j) {
            if (i == j) distancesMatrix[i][j] = 0.0;
            else distancesMatrix[i][j] = -1.0;
        }
    }
    return;
}
void calculateHotelScore(unsigned int hotelsSize, unsigned int poisSize,
                         struct Vertex *v, double **distancesMatrix) {
    /*
     * assigns a score to each hotel based on the scores of the pois around it
     * divided by the distance to each, updating the vertices array. This
     * assignation is static, meaning that it's done only once in the
     * algorithm's execution.
     * TODO: The ratio of importance for a vertex's score vs distance to it
     *          should be handled by a parameter.
     * TODO: Implement the distance of each poi to the trip line instead of the
     *          distance straight to the hotel.
     */
    for (unsigned int i = 2; i < hotelsSize; ++i) { // go through hotels (0 and 1 are required)
        for (unsigned int j = hotelsSize; j < hotelsSize + poisSize; ++j) { // go through pois
            if (d(v[i], v[j], distancesMatrix) <= 1.0)
                v[i].score += v[j].score;
            else
                v[i].score += v[j].score / d(v[i], v[j], distancesMatrix);
        }
    }
    return;
}
