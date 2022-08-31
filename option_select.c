
#include "option_select.h"

// Set the used sorting algorithm if it is valid
void set_sorting(struct configuration* configuration, char* sorting) {
    if (strcmp(sorting, "radix_binary") == 0) {
        configuration->sorting = RADIX_SORT_BINARY;
    } else if (strcmp(sorting, "radix_decimal") == 0) {
        configuration->sorting = RADIX_SORT_DECIMAL;
    } else if (strcmp(sorting, "shell") == 0) {
        configuration->sorting = SHELL_SORT;
    } else {
        printf("WARNING: Specified sorting does not exist! Falling back to default\n");
    }
}

// Set the used batch size if it is valid
void set_batch(struct configuration* configuration, char* batch) {
    int size = strtol(batch, NULL, 10);
    if (size > 0) {
        configuration->batch = size;
    } else {
        printf("WARNING: Specified batch size is invalid! Falling back to default (%lu)\n", configuration->batch);
    }
}

// Set the used version if it is valid
void set_version(struct configuration* configuration, int version) {
    if (version > VERSIONS || version < 1) {
        printf("WARNING: Specified version does not exist! Falling back to version 1\n");
        return;
    }

    struct configuration versions[VERSIONS] = PRESET;
    if (versions[version - 1].sorting != NULL) {
        configuration->sorting = versions[version - 1].sorting;
    }
    configuration->batch = versions[version - 1].batch;
}

// Get the default version configuration
struct configuration* get_default() {
    struct configuration versions[VERSIONS] = PRESET;
    struct configuration* configuration = malloc(sizeof(struct configuration));
    if (configuration == NULL) {
        fprintf( stderr, "An error occurred while configuring the used settings. Could not allocate memory\n");
        return NULL;
    }
    configuration->sorting = versions[DEFAULT_VERSION - 1].sorting;
    configuration->batch = versions[DEFAULT_VERSION - 1].batch;

    return configuration;
}