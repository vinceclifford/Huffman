
#ifndef GRA_DECODE_H
#define GRA_DECODE_H

#include <stdlib.h>
#include "batch_io.h"
#include "configuration.h"
#include "node.h"
#include "write_information.h"

int huffman_decode(FILE* input, FILE* output, long int length, struct node* root, struct configuration* configuration);

#endif //GRA_DECODE_H
