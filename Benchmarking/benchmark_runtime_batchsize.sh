#!/bin/bash

BATCH_SIZES=(1 2 4 8 16 32 64 128 256 512 768 1024 4096 16384 32768);


cd ./test_files;
DIRECTORY=$(pwd);
TEST_FILES=*;
PATTERN='[0-9]+\.[0-9]+';

echo "Sorting;Batch size;File size;Sample size;Overall runtime;Average runtime;File" > ../log_runtime_batchsize.csv;
for FILE in ${TEST_FILES[@]}; do
	for BATCH in ${BATCH_SIZES[@]}; do
		if [ "$FILE" != "output" ]; then
			FILE_SIZE=$(stat -c%s "$FILE");
			CALLBACK=$(../../huffman "$DIRECTORY/$FILE" -o "$DIRECTORY/output/$FILE$BATCH" -s shell -b $BATCH -B200);
			[[ $(echo "$CALLBACK" | grep "Overall") =~ $PATTERN ]];
			OVERALL=${BASH_REMATCH[0]};
			[[ $(echo "$CALLBACK" | grep "Average") =~ $PATTERN ]];
			AVERAGE=${BASH_REMATCH[0]};
			echo "shell;$BATCH;$FILE_SIZE;1000;$OVERALL;$AVERAGE;$FILE" &>> ../log_runtime_batchsize.csv;
		fi
	done
	echo "" &>> ../log_runtime_batchsize.csv;
done

echo "Batch size;File size;Sample size;Overall runtime;Average runtime;File" >> ../log_runtime_batchsize.csv;
for FILE in ${TEST_FILES[@]}; do
	for BATCH in ${BATCH_SIZES[@]}; do
		if [ "$FILE" != "output" ]; then
			FILE_SIZE=$(stat -c%s "$DIRECTORY/output/$FILE$BATCH.huff");
			CALLBACK=$(../../huffman "$DIRECTORY/output/$FILE$BATCH.huff" -o "$DIRECTORY/output/out" -d -b $BATCH -B200);
			[[ $(echo "$CALLBACK" | grep "Overall") =~ $PATTERN ]];
			OVERALL=${BASH_REMATCH[0]};
			[[ $(echo "$CALLBACK" | grep "Average") =~ $PATTERN ]];
			AVERAGE=${BASH_REMATCH[0]};
			echo "$BATCH;$FILE_SIZE;1000;$OVERALL;$AVERAGE;$FILE" &>> ../log_runtime_batchsize.csv;
		fi
	done
	echo "" &>> ../log_runtime_batchsize.csv;
done
exit 0;
