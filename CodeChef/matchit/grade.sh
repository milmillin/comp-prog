#!/bin/bash

for input in *.in
do
	echo "Executing "$input
	./matchit.exe < $input > "$(basename "$input" .in).out"
	./grader.exe $input $(basename $input .in).out
done
