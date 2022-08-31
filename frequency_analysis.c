
#include "frequency_analysis.h"

int _count_characters(FILE* input, struct node** entire_range, long int file_size, struct configuration* configuration) {
    while (1) {
        unsigned char* handling = read_from_file(input, configuration->batch);
        if (handling == NULL) {
            return -1;
        }
        for (unsigned long i = 0; i < configuration->batch; i++) {
            if (!file_size--) {
                free(handling);
                return 0;
            }
            (entire_range[*(handling + i)])->weight++;
        }
        free(handling);
    }
}

void free_range(struct node** range, int max) {
    for (int i = 0; i < max; i++) {
        if (range[i] != NULL) {
            free(range[i]);
        }
    }
    free(range);
}

struct tuple_array_size* frequencyAnalysis(FILE* input, long int file_size, struct configuration* configuration) {
    struct node** entire_range = malloc(MAX_NUMBER_OF_CHARS * sizeof(struct node *));

    if (entire_range == NULL) {
        fprintf(stderr, "An error occurred during frequency analysis. Could not allocate memory\n");
        return NULL;
    }

    // setup the array that counts the frequency of every character
    unsigned char counter = 0;
    for (int i = 0; i < MAX_NUMBER_OF_CHARS; i++, counter++) {
        entire_range[i] = malloc(sizeof(struct node));

        if (entire_range[i] == NULL) {
            fprintf(stderr, "An error occurred during frequency analysis. Could not allocate memory\n");
            free_range(entire_range, i);
            return NULL;
        }
        entire_range[i]->weight = 0;
        entire_range[i]->character = counter;
        entire_range[i]->left = NULL;
        entire_range[i]->right = NULL;
    }

    // read in the characters from file in batches
    if (_count_characters(input, entire_range, file_size, configuration)) {
        free_range(entire_range, MAX_NUMBER_OF_CHARS);
        return NULL;
    }

    //count amount of characters that are actually represented in the file
    int amount_entries_not_zero = 0;
    for (int i = 0; i < MAX_NUMBER_OF_CHARS; i++) {
        if (entire_range[i]->weight != 0) {
            amount_entries_not_zero++;
        }
    }

    struct node** result_array = malloc(amount_entries_not_zero * sizeof(struct node*));

    if (result_array == NULL) {
        fprintf(stderr, "An error occurred during frequency analysis. Could not allocate memory\n");
        free_range(entire_range, MAX_NUMBER_OF_CHARS);
        return NULL;
    }

    size_t next_free = 0;

    // copy the elements that are not zero
    for (int i = 0; i < MAX_NUMBER_OF_CHARS; i++) {
        if ((entire_range[i])->weight != 0) {
            result_array[next_free++] = entire_range[i];
        } else {
            free(entire_range[i]);
        }
    }

    struct tuple_array_size* result = malloc(sizeof(struct tuple_array_size));
    if (result == NULL) {
        free(entire_range);
        free_range(result_array, amount_entries_not_zero);
        return NULL;
    }
    free(entire_range);

    result->size = amount_entries_not_zero;
    result->array = result_array;
    return result;
}