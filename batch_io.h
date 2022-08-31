
#ifndef GRA_BATCH_IO_H
#define GRA_BATCH_IO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int write_to_file(FILE* output, size_t length, unsigned char string[length]);

unsigned char* read_from_file(FILE* file, size_t length);

#endif //GRA_BATCH_IO_H
