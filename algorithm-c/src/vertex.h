#ifndef GRASP_VERTEX_H
#define GRASP_VERTEX_H

#include <stdbool.h>
#include <math.h>
// #include <stdio.h>

#include "cadts_vector.h"

typedef unsigned int uint;

typedef struct {
    uint idx;
    double x;
    double y;
    double score;
    double tmp_score;
    bool vis;
} vertex;

CADTS_VECTOR(uintvec,uint);
CADTS_VECTOR(vervec,vertex);

int vertex_cmp_desc(const void *a, const void *b);
int vertex_cmp_asc(const void *a, const void *b);
double d(vertex v1, vertex v2);
double d_add(uint v1, uint v2, uint add_v, double **d_matrix);
void create_d_matrix(double **d_matrix, uint size, vertex *v);
double calc_h_score(uint index, uint hotels_n, uint pois_n, double importance,
                    vertex *v, double **d_matrix);

#endif
