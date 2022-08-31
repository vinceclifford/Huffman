
#ifndef GRA_FREQUENCY_ANALYSIS_H
#define GRA_FREQUENCY_ANALYSIS_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "extract_dictionary.h"
#include "node.h"
#include "batch_io.h"
#include "tuple_array_size.h"
#include "configuration.h"

void free_range(struct node** range, int max);

struct tuple_array_size* frequencyAnalysis(FILE* input, long int file_size, struct configuration* configuration);

#endif //GRA_FREQUENCY_ANALYSIS_H
