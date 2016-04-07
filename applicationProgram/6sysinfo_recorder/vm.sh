#!/bin/bash

echo "-----cpu-----" >> ./_file
num=10
while [[ ${num} -ne 0 ]]
do
	`sleep 1`
	`vmstat | sed -n '2,3p'|awk -F' ' '{num=5;while(num--)print $(NF-num)}' >> ./_file`
	let num=${num}-1
done
