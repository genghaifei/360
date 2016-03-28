#!/bin/bash



function use(line)
{

}

while read line
do 
	echo $(line)
	use()
done < $1
