
#include "huffman_decode.h"

int huffman_decode(FILE* input, FILE* output, long int length, struct node* root, struct configuration* configuration) {
    struct write_information information = {.current_byte = 0, .byte_pos = 0, .write_counter = 0, .total_size = 0};
    information.write_buffer = malloc(configuration->batch);
    if (information.write_buffer == NULL) {
        fprintf(stderr, "An error occurred while decoding the file. Could not allocate memory\n");
        return -1;
    }
    struct node* iterator = root;
    while (length) {

        // Read a defined number of characters, which allows to reduce the number of memory accesses
        unsigned char* current = read_from_file(input, configuration->batch);
        if (current == NULL) {
            free(information.write_buffer);
            return -1;
        }

        // Loop through the read characters and work on each one individually
        for (unsigned long i = 0; i < configuration->batch; i++) {
            char current_char = *(current + i);

            // Loop through all the bits in the byte and traverse the tree
            for (int j = 7; j >= 0; j--) {

                // If we have reached a leaf node
                if (iterator->left == NULL || iterator->right == NULL) {

                    // Then we insert the character into the write buffer
                    information.write_buffer[information.write_counter++] = iterator->character;

                    // If the write buffer is full, then we write the buffer into the file and clear the buffer
                    if (information.write_counter == configuration->batch) {
                        if (write_to_file(output, configuration->batch, information.write_buffer)) {
                            free(current);
                            free(information.write_buffer);
                            return -1;
                        }
                        information.write_counter = 0;
                    }

                    // If there are no more characters to read, then we check if the buffer still contains some
                    // leftovers. If it does, we write that buffer into the file
                    if (--length <= 0) {
                        int status = 0;
                        if (information.write_counter > 0) {
                            status = write_to_file(output, information.write_counter, information.write_buffer);
                        }
                        free(current);
                        free(information.write_buffer);
                        return status;
                    }
                    iterator = root;
                }

                // Extract the next bit of the stream and check which direction we have to go
                short bit = (current_char >> j) & 1;
                if (bit == 0) {
                    if (iterator->left != NULL) {
                        iterator = iterator->left;
                    }
                } else {
                    if (iterator->right != NULL) {
                        iterator = iterator->right;
                    }
                }
            }

        }

        free(current);
    }
    free(information.write_buffer);
    return 0;
}