#ifndef GRA_GENERATOR_H
#define GRA_GENERATOR_H

#include "node.h"
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct node* generate_tree(size_t n, struct node** first);

#endif //GRA_GENERATOR_H
