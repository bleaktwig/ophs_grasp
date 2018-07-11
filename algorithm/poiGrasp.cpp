#include "poiGrasp.h"

void tripGreedyRandomizedConstruction(
        unsigned int tripsSize, struct Trip *tour,
        unsigned int hotelsSize, unsigned int poisSize, struct Vertex *v,
        double **distancesMatrix,
        unsigned int RCLSize) {
    std::vector<struct Vertex> candidatePois;

    candidatePois.reserve(poisSize);
    for (unsigned int i = 0; i < poisSize; ++i)
        candidatePois.push_back(v[hotelsSize + i]);
    for (unsigned int i = 0; i < tripsSize; ++i) {
        bool first = true;
        while(tour[i].remainingLength >= 0.0) {
            if (RCLSize > candidatePois.size())
                RCLSize = candidatePois.size() - 1;

            // update the candidate list scores
            for (unsigned int j = 0; j < candidatePois.size(); ++j) {
                if (first)
                    candidatePois[j].tempScore = candidatePois[j].score /
                    (d(tour[i].start, candidatePois[j], distancesMatrix) +
                     d(candidatePois[j], tour[i].end, distancesMatrix));
                else
                    candidatePois[j].tempScore = candidatePois[j].score /
                    (d(tour[i].poiList.back(), candidatePois[j], distancesMatrix) +
                    d(candidatePois[j], tour[i].end, distancesMatrix));
            }

            // sort pois by this temporary score
            std::sort(candidatePois.rbegin(), candidatePois.rend());

            // pick one poi from the RCL
            int choice;
            if (RCLSize > 0) choice = rand() % RCLSize;
            else             choice = 0;
            tour[i].poiList.push_back(candidatePois[choice]); // TODO: reference instead of copy
            if (first) {
                tour[i].remainingLength = tour[i].remainingLength
                    + d(tour[i].start, tour[i].end, distancesMatrix)
                    - d(tour[i].start, tour[i].poiList.back(), distancesMatrix)
                    - d(tour[i].poiList.back(), tour[i].end, distancesMatrix);
                tour[i].score = tour[i].poiList.back().score;
            }
            else {
                tour[i].remainingLength = tour[i].remainingLength
                    + d(tour[i].poiList.rbegin()[1], tour[i].end, distancesMatrix)
                    - d(tour[i].poiList.rbegin()[1], tour[i].poiList.back(), distancesMatrix)
                    - d(tour[i].poiList.back(), tour[i].end, distancesMatrix);
                tour[i].score += tour[i].poiList.back().score;
            }
            // remove the chosen poi from the RCL
            candidatePois.erase(candidatePois.begin() + choice);
            if (tour[i].remainingLength < 0.0) {
                if (first) {
                    candidatePois.push_back(tour[i].poiList.back());
                    tour[i].remainingLength -=
                        d(tour[i].poiList.back(), tour[i].end, distancesMatrix);
                    tour[i].remainingLength +=
                        d(tour[i].start, tour[i].poiList.back(), distancesMatrix);
                    tour[i].remainingLength +=
                        d(tour[i].poiList.back(), tour[i].end, distancesMatrix);
                    tour[i].score -= tour[i].poiList.back().score;
                    tour[i].poiList.pop_back();
                    break;
                }
                else {
                    // add the last POI added back to candidates and remove it from the trip
                    // it is worth noting that this is far from optimal, but it shouldn't
                    //     really bother much since there is a local search phase afterwards
                    candidatePois.push_back(tour[i].poiList.back());
                    tour[i].remainingLength -=
                        d(tour[i].poiList.rbegin()[1], tour[i].end, distancesMatrix);
                    tour[i].remainingLength +=
                        d(tour[i].poiList.rbegin()[1], tour[i].poiList.back(), distancesMatrix);
                    tour[i].remainingLength +=
                        d(tour[i].poiList.back(), tour[i].end, distancesMatrix);
                    tour[i].score -= tour[i].poiList.back().score;
                    tour[i].poiList.pop_back();
                    break;
                }
            }
            first = false;
        }
    }
    return;
}
void tripLocalSearch(unsigned int tripsSize, struct Trip *tour,
        unsigned int hotelsSize, unsigned int poisSize, struct Vertex *v,
        double **distancesMatrix, unsigned int maxIter) {
    // TODO: see about going through N iterations without changes instead of
    //          using maxIter.
    for (unsigned int iter = 0; iter < maxIter; ++iter) {
        /* TODO: insert: go through all the pois and see which one can be added
         *          with the most added score divided by distance.
         * TODO: I'm gonna need the candidateList for this, otherwise I'll need
         *          to go through each poi in the trip again lot of times, WHICH
         *          IS NOT THAT INNEFICIENT TBH.
         */

    }
    // TODO: move-best
    // TODO: two-opt
    // TODO: swap-trips
    // TODO: extract-insert
    // TODO: extract2-insert
    // TODO: extract5-insert
    // TODO: extract-move-insert
    // TODO: replacement
    return;
}
