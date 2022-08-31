
#include "huffman.h"

// Construct long int from an 8 byte binary number string
unsigned int _long_int_from_binary(const unsigned char* binary) {
    unsigned int num = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 7; j >= 0; j--) {
            num |= (*(binary + i) >> j) & 1;
            if (i != 7 || j != 0) {
                num <<= 1;
            }
        }
    }
    return num;
}

void _free_tree(struct node* root) {
    if (root == NULL) {
        return;
    }
    _free_tree(root->left);
    _free_tree(root->right);
    free(root);
}

// Close file pointer
int _terminate(FILE* input, FILE* output) {
    fclose(input);
    fclose(output);
    return -1;
}

int encode(char* input_filename, char* output_filename, struct configuration* configuration) {
    FILE* input = fopen(input_filename, "r");
    if (input == NULL) {
        printf("Error opening input file %s\n Terminating \n", input_filename);
        return -1;
    }
    FILE* output = fopen(output_filename, "w");
    if (output == NULL) {
        printf("Error opening output file %s\n Terminating \n", input_filename);
        fclose(input);
        return -1;
    }
    // Gather the length of the file
    fseek(input, 0, SEEK_END);
    long int file_size = ftell(input);
    if (file_size == 0) {
        printf("Warning: file is empty\n");
        return _terminate(input, output);
    }
    rewind(input);
    // Create the dictionary
    struct tuple_array_size* tuple_array = frequencyAnalysis(input, file_size, configuration);
    if (tuple_array == NULL) {
        return _terminate(input, output);
    }
    configuration->sorting(tuple_array);
    struct node* tree = generate_tree(tuple_array->size, tuple_array->array);
    if (tree == NULL) {
        free_range(tuple_array->array, tuple_array->size);
        free(tuple_array);
        return _terminate(input, output);
    }
    free(tuple_array->array);
    free(tuple_array);
    // Write the tree to the file
    if (serialize_tree(output, tree, configuration)) {
        _free_tree(tree);
        return _terminate(input, output);
    }
    // Write the filesize to the file
    unsigned char size[8];
    for (int i = 0; i < 8; i++) {
        size[i] = (file_size >> (7 - i) * 8);
    }
    if (write_to_file(output, 8, size)) {
        return _terminate(input, output);
    }
    unsigned char** dictionary = extract_dictionary(tree);
    _free_tree(tree);
    if (dictionary == NULL) {
        return _terminate(input, output);
    }
    // Encode the file
    rewind(input);
    if (huffman_encode(input, output, dictionary, file_size, configuration)) {
        free_dictionary(dictionary);
        return _terminate(input, output);
    }
    free_dictionary(dictionary);
    fclose(input);
    fclose(output);
    return 0;
}

int decode(char* input_filename, char* output_filename, struct configuration* configuration) {
    FILE* input = fopen(input_filename, "r");
    if (input == NULL) {
        printf("Error opening input file %s\n Terminating \n", input_filename);
        return -1;
    }
    FILE* output = fopen(output_filename, "w");
    if (output == NULL) {
        printf("Error opening output file %s\n Terminating \n", input_filename);
        fclose(input);
        return -1;
    }
    // Gather the file length
    fseek(input, 0, SEEK_END);
    long int file_size = ftell(input);
    if (file_size == 0) {
        printf("Warning: file is empty\n");
        return _terminate(input, output);
    }
    rewind(input);
    // Deserialize the tree
    struct node* tree = deserialize_tree(input);
    if (tree == NULL) {
        return _terminate(input, output);
    }
    unsigned char* string_size_s = read_from_file(input, 8);
    if (string_size_s == NULL) {
        _free_tree(tree);
        return _terminate(input, output);
    }
    // Gather the original file length
    long int string_size = _long_int_from_binary(string_size_s);
    free(string_size_s);
    // Encode the file
    if (huffman_decode(input, output, string_size, tree, configuration)) {
        _free_tree(tree);
        return _terminate(input, output);
    }
    _free_tree(tree);
    fclose(input);
    fclose(output);
    return 0;
}
