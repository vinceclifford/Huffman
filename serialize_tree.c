
#include "serialize_tree.h"

int _insert_into_buffer(FILE* output, struct write_information* byte, struct configuration* configuration) {
    // Insert into the buffer
    byte->write_buffer[byte->write_counter++] = byte->current_byte;
    if (byte->write_counter == configuration->batch) {
        // If the buffer is full, we reset the counter and write the buffer into the file
        if (write_to_file(output, configuration->batch, byte->write_buffer)) {
            return -1;
        }
        byte->write_counter = 0;
        byte->total_size += configuration->batch * 8;
    }
    return 0;
}

int _insert_into_byte(FILE* output, struct write_information* byte, short value, struct configuration* configuration) {
    // Set the specified index of the byte to the specified value
    byte->current_byte |= value << (7 - byte->byte_pos);
    if (++byte->byte_pos == 8) {
        // If the byte is full, we reset the  counter and write the byte into the buffer
        if (_insert_into_buffer(output, byte, configuration)) {
            return -1;
        }
        byte->byte_pos = 0;
        byte->current_byte = 0;
    }
    return 0;
}

int _serialize_tree(FILE* output, struct node* tree, struct write_information* byte, struct configuration* configuration) {
    if (tree->left == NULL || tree->right == NULL) {
        // If we reach a leaf node, we mark it as a 1
        if (_insert_into_byte(output, byte, 1, configuration)) {  // (Store byte in buffer, or write back if necessary)
            return -1;
        }
        // Loop through the bits of the character and append each one to the current byte
        for (int i = 7; i >= 0; i--) {
            // Write the bit into the byte
            if (_insert_into_byte(output, byte, (tree->character >> i) & 1, configuration)) {
                return -1;
            }
        }
        return 0;
    }
    // Post order traversal
    if (_serialize_tree(output, tree->left, byte, configuration) || _serialize_tree(output, tree->right, byte, configuration)) {
        return -1;
    }
    // We are not at a leaf node, so we mark it as 0
    return _insert_into_byte(output, byte, 0, configuration);
}

int serialize_tree(FILE* output, struct node* heap, struct configuration* configuration) {
    struct write_information information = {.current_byte = 0, .byte_pos = 0, .write_counter = 0, .total_size = 0};
    information.write_buffer = malloc(configuration->batch);
    if (information.write_buffer == NULL) {
        fprintf(stderr, "An error occurred while serializing the tree. Could not allocate memory\n");
        return -1;
    }
    if (_serialize_tree(output, heap, &information, configuration)) {
        free(information.write_buffer);
        return -1;
    }
    // Write a 0 at the end as the termination symbol for the deserialization
    if (_insert_into_byte(output, &information, 0, configuration)) {
        free(information.write_buffer);
        return -1;
    }
    // If there is some leftover in the current byte, we write it into the buffer
    if (information.byte_pos != 0) {
        information.total_size += information.byte_pos;
        while (information.byte_pos != 0) {
            if (_insert_into_byte(output, &information, 0, configuration)) {
                free(information.write_buffer);
                return -1;
            }
        }
    }
    // If there is some leftover in the buffer, we write it into the file
    int status = 0;
    if (information.write_counter != 0) {
        information.total_size += (information.write_counter - 1) * 8;
        status = write_to_file(output, information.write_counter, information.write_buffer);
    }
    free(information.write_buffer);
    return status;
}