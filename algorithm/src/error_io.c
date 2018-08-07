#include "error_io.h"

void usage() {
    fprintf(stderr, "\n");
    fprintf(stderr, "usage: ophs_grasp infile outfile iter_n h_rcl p_rcl ");
    fprintf(stderr, "ls_iter_n random debug\n");
    fprintf(stderr, "  - const char*  infile:    ");
    fprintf(stderr, "    the input file\n");
    fprintf(stderr, "  - const char*  outfile:   ");
    fprintf(stderr, "    the output file\n");
    fprintf(stderr, "  - unsigned int iter_n:    ");
    fprintf(stderr, "    number of iterations the program should run\n");
    fprintf(stderr, "  - unsigned int h_rcl:     ");
    fprintf(stderr, "    rcl size for the hotel construction algorithm\n");
    fprintf(stderr, "  - unsigned int p_rcl:     ");
    fprintf(stderr, "    rcl size for the poi construction algorithm\n");
    fprintf(stderr, "  - unsigned int ls_iter_n: ");
    fprintf(stderr, "    number of iterations for the local search ");
    fprintf(stderr, "algorithm\n");
    fprintf(stderr, "  - unsigned int random:    ");
    fprintf(stderr, "    a flag telling the program to use a random ");
    fprintf(stderr, "seed\n");
    fprintf(stderr, "  - unsigned int debug:     ");
    fprintf(stderr, "    an integer defining how much output the program ");
    fprintf(stderr, "should give\n");
    fprintf(stderr, "\n");
    exit(1);
    return;
}
void error_handler(int error_id, const char *info) {
    // not enough memory [00]
    if      (error_id == 0)
        fprintf(stderr, "Not enough memory allocated during %s. Exiting...\n", info);
    // file io [01 - 09]
    else if (error_id == 1)
        fprintf(stderr, "input file name \"%s\" is invalid. Exiting...\n", info);
    else if (error_id == 2) {
        fprintf(stderr, "The given total tour length doesn't correlate with ");
        fprintf(stderr, "the length of each individual trip. The instance ");
        fprintf(stderr, "given is invalid. Exiting...\n");
    }
    else if (error_id == 6)
        fprintf(stderr, "Output file \"%s\" is invalid. Exiting...\n", info);
    // trip handling [30 - 39]
    else if (error_id == 30)
        fprintf(stderr, "Tried to add a poi via endadd_v(). Exiting...\n");
    else if (error_id == 31)
        fprintf(stderr, "Tried to add to an invalid position via poiadd_v(). Exiting...\n");
    else if (error_id == 32)
        fprintf(stderr, "Tried to add a hotel via add_v(). Exiting...\n");
    else if (error_id == 33)
        fprintf(stderr, "Tried to add to an invalid position via add_v(). Exiting...\n");
    else if (error_id == 34)
        fprintf(stderr, "Tried to add a poi that was already visited. Exiting...\n");
    // invalid error code
    else
        fprintf(stderr, "Invalid error code given to error_handler(). Exiting...\n");
    // exit(1);
    return;
}
