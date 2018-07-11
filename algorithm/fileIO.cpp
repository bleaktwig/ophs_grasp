#include "fileIO.h"

void readInput(uint *poisSize, uint *hotelsSize, uint *tripsSize,
               double **tripsLength, struct Vertex **v,
               const char *file) {
    FILE *in;
    in = fopen(file, "r");

    // parameters
    fscanf(in, "%d %d %d", poisSize, hotelsSize, tripsSize);

    *poisSize -= 2;
    *hotelsSize += 2;

    // tour length
    double totalTourLength;
    fscanf(in, "%lf", &totalTourLength);

    // trips length
    *tripsLength = (double *) malloc(sizeof(double) * (*tripsSize));
    // TODO: REMOVE (double *)
    if (*tripsLength == NULL) {
        fprintf(stderr, "Not enough memory allocated. Exiting...\n");
        exit(1);
    }

    double distanceCheck = 0.0;
    for (uint i = 0; i < *tripsSize; ++i) {
        fscanf(in, "%lf", &(*tripsLength)[i]);
        distanceCheck += (*tripsLength)[i];
    }
    if (distanceCheck >= (totalTourLength * 1.02) ||
        distanceCheck <= (totalTourLength * 0.98)) {
        fprintf(stderr, "The given total tour length doesn't correlate with ");
        fprintf(stderr, "the length of each individual trip. The instance ");
        fprintf(stderr, "given is wrong. Exiting...\n");
        exit(1);
    }

    *v = (struct Vertex *) malloc(sizeof(struct Vertex) * (*hotelsSize + *poisSize));
    // TODO: REMOVE (struct Vertex *)
    if (*v == NULL) {
        fprintf(stderr, "Not enough memory allocated. Exiting...\n");
        exit(1);
    }

    for (uint i = 0; i < *hotelsSize + *poisSize; ++i) {
        (*v)[i].index = i;
        fscanf(in, "%lf %lf %lf", &(*v)[i].x, &(*v)[i].y, &(*v)[i].score);
    }

    fclose(in);
    return;
}
void writeTours(uint tripsSize, struct Trip *tour, const char *file) {
    FILE *out;
    out = fopen(file, "w");

    for (uint i = 0; i < tripsSize; ++i) {
        fprintf(out, "%u ", tour[i].start.index);
        for (uint j = 0; j < tour[i].poiList.size(); ++j)
            fprintf(out, "%u ", tour[i].poiList[j].index);
        fprintf(out, "%u\n", tour[i].end.index);
    }

    fclose(out);
    return;
}
