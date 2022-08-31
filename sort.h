
#ifndef GRA_SORT_H
#define GRA_SORT_H

#include <stddef.h>
#include "frequency_analysis.h"
#include "node.h"

void radix_sort_binary(struct tuple_array_size* tuple);

void radix_sort_decimal(struct tuple_array_size* tuple);

void shell_sort(struct tuple_array_size* tuple);

#endif //GRA_SORT_H
