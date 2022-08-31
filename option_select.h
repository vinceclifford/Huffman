
#ifndef GRA_OPTION_SELECT_H
#define GRA_OPTION_SELECT_H

#define VERSIONS 9
#define DEFAULT_VERSION 9

#define RADIX_SORT_BINARY radix_sort_binary
#define RADIX_SORT_DECIMAL radix_sort_decimal
#define SHELL_SORT shell_sort

#define BATCH_SIZE_SMALL 1
#define BATCH_SIZE_NORMAL 4096
#define BATCH_SIZE_LARGE 16384

#define PRESET {{RADIX_SORT_BINARY, BATCH_SIZE_SMALL}, {RADIX_SORT_DECIMAL, BATCH_SIZE_SMALL},  {SHELL_SORT, BATCH_SIZE_SMALL}, \
                {RADIX_SORT_BINARY, BATCH_SIZE_SMALL}, {RADIX_SORT_DECIMAL, BATCH_SIZE_NORMAL}, {SHELL_SORT, BATCH_SIZE_NORMAL}, \
                {RADIX_SORT_BINARY, BATCH_SIZE_SMALL}, {RADIX_SORT_DECIMAL, BATCH_SIZE_LARGE},  {SHELL_SORT, BATCH_SIZE_LARGE}}

#include <stdlib.h>
#include <stdio.h>
#include "sort.h"
#include "configuration.h"

void set_sorting(struct configuration* configuration, char* sorting);

void set_batch(struct configuration* configuration, char* batch);

void set_version(struct configuration* configuration, int version);

struct configuration* get_default();

#endif //GRA_OPTION_SELECT_H
