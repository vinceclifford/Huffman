
#include "batch_io.h"

// Write a specified number of characters to the specified file
int write_to_file(FILE* output, size_t length, unsigned char string[length]) {
    if (fwrite(string, sizeof(unsigned char), length, output) != length) {
        fprintf(stderr, "An error occurred while writing to the output\n");
        return -1;
    }
    return 0;
}

// Read a specified number of characters from the specified file
unsigned char* read_from_file(FILE* file, size_t length) {
    unsigned char* string = malloc(length * sizeof(unsigned char));
    if (string == NULL) {
        fprintf(stderr, "An error occurred while reading from the file. Could not allocate memory\n");
        return NULL;
    }
    if (fread(string, sizeof(unsigned char), length, file) != length && ferror(file)) {
        fprintf(stderr, "An error occurred while reading from the file\n");
        free(string);
        return NULL;
    }
    return string;
}
