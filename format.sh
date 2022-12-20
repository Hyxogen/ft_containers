#!/bin/sh
FILES=$(find . -name "\*.cpp" -or -name "*.hpp")
for file in $FILES
do
	clang-format -i $file
done
