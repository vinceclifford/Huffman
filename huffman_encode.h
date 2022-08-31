
#ifndef GRA_ENCODE_H
#define GRA_ENCODE_H

#include <stdlib.h>
#include "batch_io.h"
#include "write_information.h"
#include "configuration.h"

int huffman_encode(FILE* input, FILE* output, unsigned char** dictionary, long int file_size, struct configuration* configuration);

#endif //GRA_ENCODE_H
