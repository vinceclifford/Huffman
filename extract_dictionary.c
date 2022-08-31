
#include "extract_dictionary.h"

int _extract_dictionary(struct node* root, unsigned char** result, int depth, unsigned char current_path[MAX_NUMBER_OF_CHARS]) {
    // If the right pointer is NULL then we have found a leaf node (which is defined in the creation of the nodes
    // in the tree generation)
    if (root->left == NULL || root->right == NULL) {
        int index = root->character;

        // Allocate space for the encoding in .rodata
        result[index] = malloc(MAX_NUMBER_OF_CHARS);
        if (result[index] == NULL) {
            fprintf(stderr, "An error occurred while creating the dictionary. Could not allocate memory\n");
            return -1;
        }

        // Copy the currently traversed path into the allocated space in .rodata
        memcpy(result[index], current_path, MAX_NUMBER_OF_CHARS * sizeof(unsigned char));

        return 0;
    }
    // Traverse left subtree
    current_path[depth - 1] = '0';
    if (_extract_dictionary(root->left, result, depth + 1, current_path)) {
        return -1;
    }

    // Traverse right subtree
    current_path[depth - 1] = '1';
    if (_extract_dictionary(root->right, result, depth + 1, current_path)) {
        return -1;
    }

    //Reset changed data
    current_path[depth - 1] = 0;
    return 0;
}

void free_dictionary(unsigned char** dictionary) {
    for (int i = 0; i < MAX_NUMBER_OF_CHARS; i++) {
        if (dictionary[i] != NULL) {
            free(dictionary[i]);
        }
    }
    free(dictionary);
}

unsigned char** extract_dictionary(struct node* root) {
    // Allocate storage for all the pointers to the encodings as strings
    unsigned char** result = malloc(MAX_NUMBER_OF_CHARS * sizeof(unsigned char*));
    if (result == NULL) {
        fprintf(stderr, "An error occurred while creating the dictionary. Could not allocate memory\n");
        return NULL;
    }

    // Set all pointers in the list to NULL
    memset(result, 0, MAX_NUMBER_OF_CHARS * sizeof(unsigned char *));

    // Create array to store the current traversed path through the tree
    unsigned char currentPath[MAX_NUMBER_OF_CHARS] = {0};
    currentPath[0] = '0';

    // Extract all encodings and return the dictionary
    if (_extract_dictionary(root, result, 1, currentPath)) {
        free_dictionary(result);
        return NULL;
    }
    return result;
}
