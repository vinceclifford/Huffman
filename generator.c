#include "generator.h"

// creates new node with new weight from passed child nodes
struct node* new_node(struct node* left, struct node* right) {
    struct node* newNode = (struct node *) malloc(sizeof(struct node));
    // print error message if malloc went wrong
    if (newNode == NULL) {
        fprintf(stderr, "An error occurred while creating the tree. Could not allocate memory\n");
        return NULL;
    }
    // set new node's data
    size_t rightWeight = right != NULL ? right->weight : 0;
    size_t leftWeight = left != NULL ? left->weight : 0;
    newNode->weight = rightWeight + leftWeight;
    newNode->left = left;
    newNode->right = right;
    return newNode;
}

// checks if first node's weight is less than second node's weight
bool lt(struct node* first, struct node* second) {
    if (first == NULL && second != NULL) {
        return false;
    } else if (first != NULL && second == NULL) {
        return true;
    } else if (first != NULL) {
        return first->weight < second->weight;
    }
    return false;
}

// main function to generate huffman tree
struct node* generate_tree(size_t n, struct node** first) {
    if (n == 1) {
        return *first;
    }
    // initialize second array with NULL
    struct node* second[n];
    memset(second, 0, n * sizeof(struct node *));
    // initialize pointers for second array
    int secondBackPointer = 0;
    int secondFrontPointer = 0;
    struct node* current = *first;
    for (size_t i = 1; i < n; i++) {
        // if the element in first is smaller than current or the element in second, then the element in first
        // is one of the components that are used for the merge
        if (lt(*(first + i), current) || lt(*(first + i), second[secondFrontPointer])) {
            // now we need to select the second component of the merge operation.
            // if there exists a further element in first, we check if that one is smaller than current and
            // the element on the stack. if that is the case, it is the second merge component
            if (i + 1 != n && lt(*(first + i + 1), current) && lt(*(first + i + 1), second[secondFrontPointer])) {
                second[secondBackPointer++] = current;
                current = new_node(*(first + i), *(first + i + 1));
                // we increment i because we used an additional element from first that now has to be skipped
                i++;
            } else if (lt(current, second[secondFrontPointer])) {
                // either there was no further element in first, or either the element in second or current
                // was smaller than that additional element. if that was the case, we check which of the remaining
                // options is smaller.
                current = new_node(*(first + i), current);
            } else {
                // the element in second was smaller than current (and the possibly existing additional element in first)
                second[secondBackPointer++] = current;
                current = new_node(*(first + i), second[secondFrontPointer++]);
            }
        } else {
            // if the element in first is larger than both current and the element in second, then those two
            // are the smallest and need to be merged
            current = new_node(second[secondFrontPointer++], current);
            // we decrement i, because no element of first was used, thus we cannot skip the current element
            i--;
        }
        if (current == NULL) {
            return NULL;
        }
    }
    second[secondBackPointer++] = current;
    // if there is only one element in second array return it -> Huffman tree is complete
    if (secondBackPointer - secondFrontPointer == 1) {
        return second[secondFrontPointer];
    }
    // else copy the array back into first and pass it tail recursively to this function
    memcpy(first, (second + secondFrontPointer), (secondBackPointer - secondFrontPointer) * sizeof(struct node *));
    return generate_tree(secondBackPointer - secondFrontPointer, first);
}
