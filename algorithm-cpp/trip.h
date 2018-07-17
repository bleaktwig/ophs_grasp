#ifndef GRASP_TRIP_H
#define GRASP_TRIP_H

#include <vector>
#include "vertex.h"

struct Trip {
    struct Vertex start;
    struct Vertex end;
    std::vector<struct Vertex> poiList;
    // std::vector<unsigned int> poiList; // TODO: implement
    double totalLength;
    double remainingLength;
    double score;
};

/* double score(struct Trip *t)
 *  TODO: calculate score based on each vertex in poiList instead of manually
 *          updating it.
 */



#endif
