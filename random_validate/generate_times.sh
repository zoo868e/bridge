#!/bin/bash
echo "Generating the times of combination"
formulaID=(`seq 1 5`)
prefix=./times_linyy_
dataset="./times_linyy.ATOC"
echo "The length of cards is "${formulaID[*]}

for i in "${formulaID[@]}"
do
	echo "./RandomConclusion ${dataset} ${i} > ${prefix}${i}"
	./RandomConclusion ${dataset} ${i} > ${prefix}${i}
done
