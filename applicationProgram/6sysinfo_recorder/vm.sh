#!/bin/bash

echo "-----cpu-----" >> ./_file
num=10
while [[ ${num} -ne 0 ]]
do
	`sleep 1`
	`vmstat | sed -n '2,3p'|awk -F' ' '{print $(NF-4)"\t" $(NF-3)"\t" $(NF-2)"\t" $(NF-1)"\t"$NF}' >> ./_file`
	let num=${num}-1
done
