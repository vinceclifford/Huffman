
#include "huffman_encode.h"

int huffman_encode(FILE* input, FILE* output, unsigned char** dictionary, long int file_size, struct configuration* configuration) {
    struct write_information information = {.current_byte = 0, .byte_pos = 0, .write_counter = 0, .total_size = 0};
    information.write_buffer = malloc(configuration->batch);
    if (information.write_buffer == NULL) {
        fprintf(stderr, "An error occurred while encoding the file. Could not allocate memory\n");
        return -1;
    }
    unsigned char* string;

    // As long as there are characters to encode we continue to evaluate the loop
    while (1) {

        // Read a batch of characters from the input file
        string = read_from_file(input, configuration->batch);
        if (string == NULL) {
            free(information.write_buffer);
            return -1;
        }

        // Loop through all read characters and evaluate each byte individually
        for (unsigned long i = 0; i < configuration->batch; i++) {

            // If we reached the end or found
            if (!file_size--) {
                // If the last byte was not filled completely, do that here
                if (information.byte_pos != 0) {
                    information.current_byte <<= 7 - information.byte_pos;
                    information.write_buffer[information.write_counter++] = information.current_byte;
                }
                // If there is something in the buffer, we write it back normally,
                int status = 0;
                if (information.write_counter != 0) {
                    status = write_to_file(output, information.write_counter, information.write_buffer);
                }
                free(string);
                free(information.write_buffer);
                return status;
            }
            // Gather the encoding of the current character and loop through the current encoding of
            // the character and append it to the current string
            unsigned char* sequence = dictionary[(int) *(string + i)];
            if (sequence == NULL) {
                fprintf(stderr, "An error occurred while encoding the file. One of the characters was not mapped\n");
                free(information.write_buffer);
                free(string);
                return -1;
            }
            for (int j = 0; *(sequence + j); j++) {
                information.current_byte |= (*(sequence + j) - 48);

                if (++information.byte_pos == 8) {
                    // If the string is full we insert the byte into the byte buffer.
                    information.write_buffer[information.write_counter++] = information.current_byte;

                    // If the buffer is full, we write the buffer into the file
                    if (information.write_counter == configuration->batch) {
                        if (write_to_file(output, configuration->batch, information.write_buffer)) {
                            free(string);
                            free(information.write_buffer);
                            return -1;
                        }
                        information.write_counter = 0;
                    }

                    information.current_byte = 0;
                    information.byte_pos = 0;
                } else {
                    // If the byte is not full yet, we shift the byte to the left to make space for the next entry
                    information.current_byte <<= 1;
                }
            }
        }
        free(string);
    }
}