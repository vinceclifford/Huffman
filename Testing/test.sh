#!/bin/bash

cd ./test_files

DIRECTORY=$(pwd)
BATCH_SIZES=(1 4096 16384);
SORTINGS=("radix_binary" "radix_decimal" "shell");
TEST_FILES=*

RED='\033[0;31m'
NC='\033[1;32m'

for SORT in ${SORTINGS[@]}; do
	for BATCH in ${BATCH_SIZES[@]}; do
		for FILE in ${TEST_FILES[@]}; do
			if [ "$FILE" != "out.huff" ] && [ "$FILE" != "output" ]; then
				EN=$(../../huffman "$DIRECTORY/$FILE" -o "$DIRECTORY/output/out" -s $SORT -b $BATCH);
				DE=$(../../huffman "$DIRECTORY/output/out.huff" -o "$DIRECTORY/output/$BATCH$SORT$FILE" -d -b $BATCH);
				if cmp -s "$DIRECTORY/$FILE" "$DIRECTORY/output/$BATCH$SORT$FILE"; then
					printf "${NC}Test {Sort=$SORT, Batch=$BATCH, File=$FILE} passed\n";
				else
					printf "${RED}Test {Sort=$SORT, Batch=$BATCH, File=$FILE} failed\n";
				fi
			fi
		done
	done
done
exit 0;
