

#ifndef GRA_HUFFMAN_H
#define GRA_HUFFMAN_H

#include "huffman_decode.h"
#include "deserialize_tree.h"
#include "huffman_encode.h"
#include "extract_dictionary.h"
#include "frequency_analysis.h"
#include "generator.h"
#include "serialize_tree.h"
#include "option_select.h"
#include "configuration.h"

int encode(char* input_filename, char* output_filename, struct configuration* configuration);

int decode(char* input_filename, char* output_filename, struct configuration* configuration);

#endif //GRA_HUFFMAN_H
