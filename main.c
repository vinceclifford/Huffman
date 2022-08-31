#include "huffman.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#define DECODE 0
#define ENCODE 1

int main(int argc, char** argv) {
    int verbose = 0;
    int log_runtime = -1;
    char* input = NULL;
    int mode = ENCODE;
    char* output = NULL;
    int opt;

    struct option long_options[] = {
            {"help", no_argument, 0, 'h'},
            {"verbose", no_argument, 0, 'v'},
            {"batchsize", required_argument, 0, 'b'},
            {"sort", required_argument, 0, 's'},
            {0, 0, 0, 0}};
    struct configuration* configuration = get_default();
    if (configuration == NULL) {
        return EXIT_FAILURE;
    }
    // Option select
    while ((opt = getopt_long(argc, argv, "V::B::do:hvb:s:", long_options, 0)) != -1) {
        switch (opt) {
            case 0:
                break;
            case 'V':
                if (optarg != NULL) {
                    set_version(configuration, strtol(optarg, NULL, 10));
                }
                break;
            case 'B':
                if (optarg != NULL) {
                    log_runtime = strtol(optarg, NULL, 10);
                    if (log_runtime <= 0) {
                        log_runtime = 1;
                        printf("WARNING: Specified sample size is invalid. Falling back to default (1)\n");
                    }
                }
                break;
            case 'd':
                mode = DECODE;
                break;
            case 'o':
                output = optarg;
                break;
            case 'v':
                verbose = 1;
                break;
            case 'b':
                if (optarg != NULL) {
                    set_batch(configuration, optarg);
                }
                break;
            case 's':
                if (optarg != NULL) {
                    set_sorting(configuration, optarg);
                }
                break;
            case 'h':
                printf("Usage: %s [OPTIONS] [INPUT] [OUTPUT]\n", argv[0]);
                printf("Options:\n");
                printf("  -V<int> \t\t\tSelect specific version. Default: V9\n");
                printf("  -B<int> \t\t\tLog runtime with specified iterations. Default when set: B1\n");
                printf("  -d \t\t\t\tDecompress file. If not set, input file will be compressed\n");
                printf("  -o \t\t\t\tSpecify output file\n");
                printf("  -b <int>, --batchsize <int> \tSet batch size. Default: 16384 Byte\n");
                printf("  -v, --verbose \t\tVerbose mode\n");
                printf("  -s <string>, --sort <string> \tSet sorting algorithm. Valid inputs: radix_binary, radix_decimal, shell. Default: Shell sort\n");
                printf("  -h, --help\t\t\tPrint this help\n");
                printf("Versions:\n");
                printf("  -V1\t\t\t\tRadix sort binary\tBatch size 1\n");
                printf("  -V2\t\t\t\tRadix sort decimal\tBatch size 1\n");
                printf("  -V3\t\t\t\tShell sort\t\tBatch size 1\n");
                printf("  -V4\t\t\t\tRadix sort binary\tBatch size 4096\n");
                printf("  -V5\t\t\t\tRadix sort decimal\tBatch size 4096\n");
                printf("  -V6\t\t\t\tShell sort\t\tBatch size 4096\n");
                printf("  -V7\t\t\t\tRadix sort binary\tBatch size 16384\n");
                printf("  -V8\t\t\t\tRadix sort decimal\tBatch size 16384\n");
                printf("  -V9\t\t\t\tShell sort\t\tBatch size 16384\n");
                return 0;
            default:
                printf("Invalid input\n");
                free(configuration);
                return 0;
        }
    }
    while (optind < argc) {
        input = argv[optind++];
    }
    // Add default file extension for encoding
    if (mode == ENCODE) {
        strncat(output, ".huff", 6);
    }
    if (log_runtime != -1) {
        // Execute with time measurement
        struct timespec start;
        struct timespec end;
        clock_gettime(CLOCK_MONOTONIC, &start);
        for (int i = 0; i < log_runtime; i++) {
            if (mode == ENCODE ? encode(input, output, configuration) : decode(input, output, configuration)) {
                free(configuration);
                return EXIT_FAILURE;
            }
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
        double time = (end.tv_sec - start.tv_sec + 1e-9 * (end.tv_nsec - start.tv_nsec)) / log_runtime;
        printf("\nSample size: %d\n", log_runtime);
        printf("Overall runtime: %fs\n", end.tv_sec - start.tv_sec + 1e-9 * (end.tv_nsec - start.tv_nsec));
        printf("Average runtime: %fs\n", time);
    } else {
        // Execute without time measurement
        if (mode == ENCODE ? encode(input, output, configuration) : decode(input, output, configuration)) {
            free(configuration);
            return EXIT_FAILURE;
        }
    }

    struct stat st_input;
    struct stat st_output;
    stat(input, &st_input);
    stat(output, &st_output);

    if (mode == ENCODE) {
        if (verbose) {
            // Print verbose output
            printf("\nInput file size: %ld bytes\n", st_input.st_size);
            printf("Output file size: %ld bytes\n", st_output.st_size);
            printf("Compression ratio: %f", (double) st_input.st_size / (double) st_output.st_size);
        }
        printf("\nSpace saving: %f%%\n\n", (1 - (double) st_output.st_size / (double) st_input.st_size) * 100);
    }
    if (verbose) {
        // Print verbose output
        if (configuration->sorting == RADIX_SORT_BINARY) {
            printf("Sorting: Radix sort base 2\n");
        } else if (configuration->sorting == RADIX_SORT_DECIMAL) {
            printf("Sorting: Radix sort base 10\n");
        } else if (configuration->sorting == SHELL_SORT) {
            printf("Sorting: Shell sort\n");
        }
        printf("Batch size: %ld\n\n", configuration->batch);
    }
    free(configuration);
    return EXIT_SUCCESS;
}
