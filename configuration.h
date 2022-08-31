
#ifndef GRA_CONFIGURATION_H
#define GRA_CONFIGURATION_H

#include "tuple_array_size.h"

struct configuration {
    void (*sorting)(struct tuple_array_size*);
    unsigned long batch;
};

#endif //GRA_CONFIGURATION_H
