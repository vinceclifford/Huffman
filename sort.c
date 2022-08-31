
#include "sort.h"

size_t get_highest_weight(int size, struct node** array){
    size_t highestWeight = array[0]->weight;
    for (int i = 1; i < size; i++) {
        size_t lookingAt = array[i]->weight;
        if (lookingAt > highestWeight) {
            highestWeight = lookingAt;
        }
    }
    return highestWeight;
}

void count_sort_binary(int size, struct node** array, int place) {
    struct node* temp[size];
    int count[2] = {0};

    for (int i = 0; i < size; i++) {
        count[(array[i]->weight >> place) & 1]++;
    }

    count[1] += count[0];

    for (int i = size - 1; i >= 0; i--) {
        size_t index = (array[i]->weight >> place) & 1;
        temp[count[index] - 1] = array[i];
        count[index]--;
    }

    memcpy(array, temp, size * sizeof(struct node *));
}

void radix_sort_binary(struct tuple_array_size *tuple) {
    int size = tuple->size;
    struct node** array = tuple->array;

    size_t highestWeight = get_highest_weight(size, array);
    int place = 0;

    while (highestWeight > 0) {
        count_sort_binary(size, array, place);
        place++;
        highestWeight = highestWeight >> 1;
    }
}

void count_sort_decimal(int size, struct node** array, int place) {
    struct node* temp[size];
    int count[10] = {0};

    for (int i = 0; i < size; i++) {
        count[(array[i]->weight / place) % 10]++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (int i = size - 1; i >= 0; i--) {
        size_t index = (array[i]->weight / place) % 10;
        temp[count[index] - 1] = array[i];
        count[index]--;
    }

    memcpy(array, temp, size * sizeof(struct node *));
}

void radix_sort_decimal(struct tuple_array_size* tuple) {
    int size = tuple->size;
    struct node** array = tuple->array;

    size_t highestWeight = get_highest_weight(size, array);
    int place = 1;

    while (highestWeight > 0) {
        count_sort_decimal(size, array, place);
        place = place * 10;
        highestWeight /= 10;
    }
}

void shell_sort(struct tuple_array_size* tuple){
    int size = tuple->size;
    struct node** array = tuple->array;

    for (int gap = size / 2; gap > 0; gap /= 2) {

        for (int i = gap; i < size; i++) {
            struct node* temp = *(array + i);

            int j;
            for (j = i; j >= gap && (*(array + j - gap))->weight > temp->weight; j -= gap) {
                *(array + j) = *(array + j - gap);
            }
            *(array + j) = temp;
        }
    }
}