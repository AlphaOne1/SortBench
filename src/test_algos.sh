#!/bin/sh

for i in {1..500}
do
	./sortbench $i 2 lib*Sort.so
	if [ ! $? ]
	then
		echo "Found error at $i elements" 1>&2
		exit 1
	fi
done

exit 0
