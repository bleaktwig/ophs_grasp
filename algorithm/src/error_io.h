#ifndef ERROR_IO_H
#define ERROR_IO_H

#include <stdio.h>
#include <stdlib.h>

void usage();
void error_handler(int error_id, const char *info);

#endif
