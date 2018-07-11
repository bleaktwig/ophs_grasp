#include "hotelGrasp.h"

void tourGreedyRandomizedConstruction(
        unsigned int tripsSize, struct Trip *tour,
        unsigned int hotelsSize/*, unsigned int poisSize*/, struct Vertex *v,
        double **distancesMatrix,
        unsigned int RCLSize) {
    /*
     * places the starting and ending hotels in the first and last trips respectively
     * creates an unpicked hotels std::vector<struct Vertex>
     * for each trip given by tripsSize:
     *  * sorts the list by score divided by the distances
     *  * picks from this list in a greedy randomized fashion
     *  * sets this hotel as the end of the current trip and as the start of the next trip
     */
    tour[0].start = v[0];
    tour[tripsSize - 1].end = v[1];
    std::vector<struct Vertex> candidateHotels;
    candidateHotels.reserve(hotelsSize - 2);
    for (unsigned int i = 2; i < hotelsSize; ++i)
        candidateHotels.push_back(v[i]);
    for (unsigned int i = 0; i < tripsSize - 1; ++i) {
        // assigns score divided by distance to each hotel
        // TODO: this can be improved by instead using the distance from each
        //       poi to the line created between two hotels as the score for
        //       each. This also eliminates the necessity for the tempScore
        //       variable.

        // calculate temporary score
        for (unsigned int j = 0; j < candidateHotels.size(); ++j)
            candidateHotels[j].tempScore = candidateHotels[i].score /
                (d(v[0], v[j+2], distancesMatrix) +
                 d(v[j+2], v[1], distancesMatrix));
        if (RCLSize > candidateHotels.size())
            RCLSize = candidateHotels.size() - 1;
        // sorts hotels by this temporary score
        std::sort(candidateHotels.rbegin(), candidateHotels.rend());

        // pick one hotel from the RCL
        unsigned int choice;
        if (RCLSize > 0) choice = rand() % RCLSize;
        else             choice = 0;

        tour[i].end = candidateHotels[choice]; // TODO: reference instead of copy
        tour[i + 1].start = tour[i].end;

        // remove the chosen hotel from the RCL
        candidateHotels.erase(candidateHotels.begin() + choice);
    }
    // update the remainingLength from each trip
    for (unsigned int i = 0; i < tripsSize; ++i)
        tour[i].remainingLength = tour[i].totalLength -
            d(v[tour[i].start.index], v[tour[i].end.index], distancesMatrix);
    // TODO: check if one remainingLength is negative and repair or scrap the solution
    return;
}
// TODO: a function that checks if a tour is unfeasible and drops or repairs it
void tourLocalSearch(
        unsigned int tripsSize, struct Trip *tour,
        unsigned int hotelsSize/* unsigned int poisSize*/, struct Vertex *v,
        double **distancesMatrix) {
    return;
}
