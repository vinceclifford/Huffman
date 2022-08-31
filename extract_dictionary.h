
#ifndef GRA_EXTRACT_DICTIONARY_H
#define GRA_EXTRACT_DICTIONARY_H
#define MAX_NUMBER_OF_CHARS 256

#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "node.h"

void free_dictionary(unsigned char** dictionary);

unsigned char** extract_dictionary(struct node* root);

#endif //GRA_EXTRACT_DICTIONARY_H
