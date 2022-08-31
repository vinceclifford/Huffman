
#include "deserialize_tree.h"

void _free_stack(struct node* stack[MAX_STACK_SIZE]) {
    for (int i = 0; i < MAX_STACK_SIZE; i++) {
        if (stack[i] != NULL) {
            free(stack[i]);
        }
    }
}

struct node* deserialize_tree(FILE* file){

    // Instead of receiving the amount of bits in the serialized tree as an argument, in our optimized version we stray
    // away from this idea. This result in even tighter compression. This is explained in greater detail in our paper.
    // Thus, we don't know how long our tree sequence is. However,the tree must be stored in following 512 Byte. The size
    // of the tree will never exceed this approximation.

    unsigned char* tree = read_from_file(file, MAX_STACK_SIZE);
    if (tree == NULL) {
        return NULL;
    }

    int top_of_stack = 0;
    struct node* stack[MAX_STACK_SIZE];
    int bit_at = 0;

    memset(stack, 0, MAX_STACK_SIZE * sizeof(unsigned char *));

    while (1) {

        // Check whether bit that we are looking at is a zero or a one. Because we can't directly access bits of a char*, some
        // bit shifting has to take place. If bit_at == 0, then we need to pop the upper two nodes off the stack. Then we will
        // create a new inner node. The uppermost node will be the right child of the inner node, the second to upper will be
        // the left child. We push the inner node onto the stack. If bit_at == 0, we create a new leaf node with the
        // character and push it onto the stack

        if ((((*(tree + (bit_at / 8))) >> (7 - (bit_at % 8))) & 1) == 1) {
            bit_at++;
            unsigned char character_of_node;

            // If the bit that we are handling is one byte aligned we can simply read the character of the inner node directly.
            // Otherwise, bit shifts have to be performed to extract the character of the node. The basic principle is the following: We
            // take the byte that we are looking at and shift it n-times to the left. n is calculated by the bit that we located at.
            // Afterwards, we take the ensuing byte and shift if m-times to the right. Again, m is dependent on bit_at. We add the two
            // numbers together. This will be the character of the node

            if (bit_at % 8 == 0) {
                character_of_node = *(tree + bit_at / 8);
            } else {
                character_of_node = *(tree + (bit_at / 8)) << (bit_at % 8);
                unsigned char character_ahead = *(tree + (bit_at / 8) + 1);
                unsigned char character_ahead_shifted = character_ahead >> (8 - (bit_at % 8));
                character_of_node += character_ahead_shifted;
            }
            struct node* to_insert = malloc(sizeof(struct node));

            if (to_insert == NULL) {
                fprintf(stderr, "An error occurred while deserializing the tree. Could not allocate memory\n");
                _free_stack(stack);
                free(tree);
                return NULL;
            }

            to_insert->character = character_of_node;
            to_insert->left = NULL;
            to_insert->right = NULL;
            stack[top_of_stack++] = to_insert;
            bit_at += 8;
        } else {

            // if we read a 0 bit, and we only have got one element on the stack we know that this is the root node.
            // pointer to file will be advanced to long int, node will be returned

            if (top_of_stack == 1) {
                int bytes_to_advance = (bit_at / 8) + 1;
                fseek(file, bytes_to_advance, SEEK_SET);
                free(tree);
                return stack[0];
            }
            struct node* right_child = stack[--top_of_stack];
            struct node* left_child = stack[--top_of_stack];
            struct node* to_insert = malloc(sizeof(struct node));

            if (to_insert == NULL) {
                fprintf(stderr, "An error occurred while deserializing the tree. Could not allocate memory\n");
                _free_stack(stack);
                free(tree);
                return NULL;
            }

            if (right_child == NULL || left_child == NULL) {
                fprintf(stderr, "An error occurred while deserializing the tree. Received corrupted tree\n");
                _free_stack(stack);
                free(to_insert);
                free(tree);
                return NULL;
            }

            to_insert->left = left_child;
            to_insert->right = right_child;
            stack[top_of_stack++] = to_insert;
            bit_at++;
        }
    }
}
