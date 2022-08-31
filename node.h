
#ifndef GRA_NODE_H
#define GRA_NODE_H

#include <stddef.h>

struct node {
    unsigned char character;
    size_t weight;
    struct node* left;
    struct node* right;
};

#endif //GRA_NODE_H
