
#ifndef GRA_SERIALIZE_TREE_H
#define GRA_SERIALIZE_TREE_H

#include "node.h"
#include "batch_io.h"
#include "write_information.h"
#include "configuration.h"

int serialize_tree(FILE* output, struct node* heap, struct configuration* configuration);

#endif //GRA_SERIALIZE_TREE_H
