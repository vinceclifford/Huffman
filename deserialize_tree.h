

#ifndef GRA_DESERIALIZE_TREE_H
#define GRA_DESERIALIZE_TREE_H
#define MAX_STACK_SIZE 512

#include "node.h"
#include "batch_io.h"
#include "frequency_analysis.h"
#include <stdlib.h>
#include <stdio.h>

struct node* deserialize_tree(FILE* file);

#endif //GRA_DESERIALIZE_TREE_H
