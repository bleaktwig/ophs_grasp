#include "poiGrasp.h"

void tripGreedyRandomizedConstruction(
        unsigned int tripsSize, struct Trip *tour,
        unsigned int hotelsSize, unsigned int poisSize,
        struct Vertex *v, std::vector<struct Vertex> &candidatePois,
        double **distancesMatrix,
        unsigned int RCLSize) {
    //std::vector<struct Vertex> candidatePois;

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
        unsigned int hotelsSize, unsigned int poisSize,
        struct Vertex *v, std::vector<struct Vertex> &candidatePois,
        double **dm /*distancesMatrix*/, unsigned int maxIter) {
    // TODO: see about going through N iterations without changes instead of
    //          using maxIter.
    for (unsigned int iter = 0; iter < maxIter; ++iter) {
        {
            /* TODO: insert: go through all the pois and see which one can be
             *               added with the most added score divided by distance.
             */
            unsigned int bestPoiIndex;
            double bestPoiScore = 0.0;
            unsigned int btop; // bestTourPosition
            int btrp; // bestTripPosition
            for (unsigned int p = 0; p < candidatePois.size(); ++p) {
                unsigned int tourPosition;
                int tripPosition;
                for (unsigned int t = 0; t < tripsSize; ++t) {
                    // first
                    double calcAux = 0.0;
                    double increase;
                    double newLength;
                    if (tour[t].poiList.size() > 0) {
                        increase =
                            d(tour[t].start, candidatePois[p], dm) +
                            d(candidatePois[p], tour[t].poiList[0], dm) -
                            d(tour[t].start, tour[t].poiList[0], dm);
                        newLength = tour[t].remainingLength + increase;
                        calcAux = candidatePois[p].score / increase;
                        if (newLength > 0) {
                            candidatePois[p].tempScore = calcAux;
                            tourPosition = t;
                            tripPosition = -1;
                        }
                    }
                    // in-between
                    for (unsigned int i = 0; i < tour[t].poiList.size(); ++i) {
                        increase =
                            d(tour[t].poiList[i], candidatePois[p], dm) +
                            d(candidatePois[p], tour[t].poiList[i+1], dm) -
                            d(tour[t].poiList[i], tour[t].poiList[i+1], dm);
                        newLength = tour[t].remainingLength + increase;
                        calcAux = candidatePois[p].score / increase;
                        if (calcAux > candidatePois[p].tempScore && newLength > 0) {
                            candidatePois[p].tempScore = calcAux;
                            tourPosition = t;
                            tripPosition = i;
                        }
                    }
                    // last
                    if (tour[t].poiList.size() > 0) {
                        unsigned int size = tour[t].poiList.size();
                        increase =
                            d(tour[t].poiList[size - 1], candidatePois[p], dm) +
                            d(candidatePois[p], tour[t].end, dm) -
                            d(tour[t].poiList[size - 1], tour[t].end, dm);
                        newLength = tour[t].remainingLength + increase;
                        calcAux = candidatePois[p].score / increase;
                        if (calcAux > candidatePois[p].tempScore && newLength > 0) {
                            candidatePois[p].tempScore = calcAux;
                            tourPosition = t;
                            tripPosition = size;
                        }
                    }
                    else {
                        increase =
                            d(tour[t].start, candidatePois[p], dm) +
                            d(candidatePois[p], tour[t].end, dm) -
                            d(tour[t].start, tour[t].end, dm);
                        newLength = tour[t].remainingLength + increase;
                        calcAux = candidatePois[p].score / increase;
                        if (calcAux > candidatePois[p].tempScore && newLength > 0) {
                            candidatePois[p].tempScore = calcAux;
                            tourPosition = t;
                            tripPosition = -1;
                        }
                    }
                }
                // currently I have the best position in which I could add this poi.
                if (candidatePois[p].tempScore > bestPoiScore) {
                    // this poi is better than the currently best poi.
                    bestPoiIndex = p;
                    bestPoiScore = candidatePois[p].tempScore;
                    btop = tourPosition;
                    btrp = tripPosition;
                }
            }
            // check that adding this poi doesn't make the remainingLength negative
            double newLength;
            unsigned int size = tour[btop].poiList.size();
            if (btrp == -1 && tour[btop].poiList.size() == 0)
                newLength = tour[btop].remainingLength
                    - d(tour[btop].start, candidatePois[bestPoiIndex], dm)
                    - d(candidatePois[bestPoiIndex], tour[btop].end, dm)
                    + d(tour[btop].start, tour[btop].end, dm);
            else if (btrp == -1)
                newLength = tour[btop].remainingLength
                    - d(tour[btop].start, candidatePois[bestPoiIndex], dm)
                    - d(candidatePois[bestPoiIndex], tour[btop].poiList[0], dm)
                    + d(tour[btop].start, tour[btop].poiList[0], dm);
            else if (btrp == (int)size)
                newLength = tour[btop].remainingLength
                    - d(tour[btop].poiList[size - 1], candidatePois[bestPoiIndex], dm)
                    - d(candidatePois[bestPoiIndex], tour[btop].end, dm)
                    + d(tour[btop].poiList[size - 1], tour[btop].end, dm);
            else
                newLength = tour[btop].remainingLength
                    - d(tour[btop].poiList[btrp], candidatePois[bestPoiIndex], dm)
                    - d(candidatePois[bestPoiIndex], tour[btop].poiList[btrp + 1], dm)
                    + d(tour[btop].poiList[btrp], tour[btop].poiList[btrp + 1], dm);

            /*
            printf("Best poi found:\n");
            printf(" - index:     %u\n", bestPoiIndex);
            printf(" - tempScore: %.2f\n", bestPoiScore);
            printf(" - on tour:   %u\n", btop);
            printf(" - in trip:   %d\n\n", btrp);
            printf("old length: %.2f\n", tour[btop].remainingLength);
            printf("new length: %.2f\n", newLength);
            printf("%u - %d\n", size, btrp);
            */

            if (newLength > 0) {
                if ((int)size == btrp)
                    tour[btop].poiList.push_back(candidatePois[bestPoiIndex]);
                else
                    tour[btop].poiList.insert(
                        tour[btop].poiList.begin() + btrp + 1,
                        candidatePois[bestPoiIndex]);
                candidatePois.erase(candidatePois.begin() + bestPoiIndex);
                tour[btop].remainingLength = newLength;
                tour[btop].score += tour[btop].poiList.back().score;
                printf("%u > Inserted poi!\n", iter);
            }
            else
                printf("%u > Inserting poi would fuck up trip!\n", iter);
        }

        // TODO: move-best
        // TODO: two-opt
        // TODO: swap-trips
        // TODO: extract-insert
        // TODO: extract2-insert
        // TODO: extract5-insert
        // TODO: extract-move-insert
        // TODO: replacement
    }
    return;
}
