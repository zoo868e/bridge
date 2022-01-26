#!/bin/bash
echo "Setting training formula"
formulaID=( 2 3 4 5 7 8 )
prefix=./result/2022/0119_formula_
dataset="./data/DDSresult.txt"
echo "The training formula is "${formulaID[*]}

for i in "${formulaID[@]}"
do
	echo "python Objfunc.py ${i} ${dataset} > ${prefix}${i}"
	python Objfunc.py ${i} ${dataset} > ${prefix}${i}
done
