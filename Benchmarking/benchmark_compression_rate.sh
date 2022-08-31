#!/bin/bash

cd ./test_files;
DIRECTORY=$(pwd);
TEST_FILES=*;
PATTERN='[0-9]+\.[0-9]+';

echo "File size;Sample size;Overall runtime;Average runtime;Compression;File" > ../log_compression.csv;
for FILE in ${TEST_FILES[@]}; do
	if [ "$FILE" != "output" ]; then
		FILE_SIZE=$(stat -c%s "$FILE");
		CALLBACK=$(../../huffman "$DIRECTORY/$FILE" -o "$DIRECTORY/output/$FILE" -s shell -b 32768 -B200);
		[[ $(echo "$CALLBACK" | grep "Overall") =~ $PATTERN ]];
		OVERALL=${BASH_REMATCH[0]};
		[[ $(echo "$CALLBACK" | grep "Average") =~ $PATTERN ]];
		AVERAGE=${BASH_REMATCH[0]};
		[[ $(echo "$CALLBACK" | grep "saving") =~ $PATTERN ]];
		SAVING=${BASH_REMATCH[0]};
		echo "$FILE_SIZE;1000;$OVERALL;$AVERAGE;$SAVING;$FILE" &>> ../log_compression.csv;
	fi
done
exit 0;
