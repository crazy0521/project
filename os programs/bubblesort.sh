#!/bin/bash

arr=(0 1 10 4 0) # Index 0 is dummy for 1-based indexing

for ((i=1; i<=4; i++))
do
	for ((j=1; j<=4-i; j++))
	do 
		if [ ${arr[j]} -gt ${arr[j+1]} ]
		then
			# Swap elements
			temp=${arr[j]}
			arr[j]=${arr[j+1]}
			arr[j+1]=$temp
		fi
	done
done

# Print sorted array
for ((i=1; i<=4; i++))
do
	echo ${arr[i]}
done
