CFLAGS=-std=c11 -Ofast -Wall -Wextra -Wpedantic -D_POSIX_C_SOURCE=199309L

all: huffman
huffman: batch_io.c huffman_decode.c deserialize_tree.c huffman_encode.c extract_dictionary.c frequency_analysis.c generator.c huffman.c main.c option_select.c serialize_tree.c sort.c configuration.h tuple_array_size.h write_information.h node.h

	$(CC) $(CFLAGS) -o $@ $^
clean:
	rm huffman
