#ifndef ERROR_IO_H
#define ERROR_IO_H

#include <stdio.h>
#include <stdlib.h>

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"

void usage();
void error_handler(int error_id, const char *info);

#endif
