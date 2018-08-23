#include "error_io.h"

void usage() {
    // prints the usage of the program.
    fprintf(stderr, "\n");
    fprintf(stderr, "usage: ophs_grasp infile outfile iter_n h_rcl p_rcl ");
    fprintf(stderr, "ls_iter_n random tune\n");
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
    fprintf(stderr, "  - unsigned int tune:     ");
    fprintf(stderr, "    an integer telling the program to print parameter ");
    fprintf(stderr, "tuning data\n");
    fprintf(stderr, "\n");
    exit(1);
    return;
}
void error_handler(int error_id, const char *info) {
    // prints the error information related to error_id.
    fprintf(stderr, "%s", KRED);
    // not enough memory [00]
    if      (error_id == 0)
        fprintf(stderr, "Not enough memory allocated during %s.", info);
    // file io [01 - 09]
    else if (error_id == 1)
        fprintf(stderr, "input file name \"%s\" is invalid.", info);
    else if (error_id == 2) {
        fprintf(stderr, "The given total tour length doesn't correlate with ");
        fprintf(stderr, "the length of each individual trip. The instance ");
        fprintf(stderr, "given is invalid.");
    }
    else if (error_id == 6)
        fprintf(stderr, "Output file \"%s\" is invalid.", info);
    // trip handling [30 - 49]
    else if (error_id == 30)
        fprintf(stderr, "Tried to add a poi via endadd_v().");
    else if (error_id == 31)
        fprintf(stderr, "Tried to add to an invalid position via poiadd_v().");
    else if (error_id == 32)
        fprintf(stderr, "Tried to add a hotel via add_v().");
    else if (error_id == 33)
        fprintf(stderr, "Tried to add a vertex that doesn't exist via add_v().");
    else if (error_id == 34)
        fprintf(stderr, "Tried to add to an invalid position via add_v().");
    else if (error_id == 35)
        fprintf(stderr, "Tried to add a poi that was already visited via add_v().");
    else if (error_id == 36)
        fprintf(stderr, "Tried to remove an hotel.");
    else if (error_id == 37)
        fprintf(stderr, "Tried to remove a vertex that doesn't exist.");
    else if (error_id == 38)
        fprintf(stderr, "Tried to remove a poi from an invalid position.");
    else if (error_id == 39)
        fprintf(stderr, "Tried to remove an unvisited poi from a trip.");
    else if (error_id == 40)
        fprintf(stderr, "Tried to exchange a poi from an invalid position.");
    else if (error_id == 41)
        fprintf(stderr, "Tried to exchange an hotel.");
    else if (error_id == 42)
        fprintf(stderr, "Tried to exchange an inexistent poi.");
    else if (error_id == 43)
        fprintf(stderr, "Tried to exchange an unvisited poi.");
    // invalid error code
    else
        fprintf(stderr, "Invalid error code given to error_handler().");
    fprintf(stderr, " Exiting...\n");
    fprintf(stderr, "%s", KNRM);
    exit(1);
    return;
}
