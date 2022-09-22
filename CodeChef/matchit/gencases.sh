#!/bin/bash

for i in {1..10}
do
	echo "Generating "$i
	python gen.py > $(printf "%02d.in" $i)
done
