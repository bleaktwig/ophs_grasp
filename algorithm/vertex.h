#ifndef GRASP_VERTEX_H
#define GRASP_VERTEX_H

#include <cmath>

struct Vertex {
    int index;
    double x;
    double y;
    double score;
    double tempScore; // used for computing each trip
    bool operator < (const Vertex& ver) const {
        return (tempScore < ver.tempScore);
    }
    bool operator > (const Vertex& ver) const {
        return (tempScore > ver.tempScore);
    }
};
double d(struct Vertex a, struct Vertex b, double **distancesMatrix);
void fillMatrix(unsigned int hotelsSize, unsigned int poisSize,
                double **distancesMatrix);
void calculateHotelScore(unsigned int hotelsSize, unsigned int poisSize,
                         struct Vertex *v, double **distancesMatrix);


#endif
