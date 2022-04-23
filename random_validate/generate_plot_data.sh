#!/bin/bash
echo "Generating the ploted data"
formulaID=(`seq 1 13`)
prefix=./plot_times_
suffix=.data
dataset_prefix="./times_"
echo "The length of cards is "${formulaID[*]}

for i in "${formulaID[@]}"
do
	cat ${dataset_prefix}${i} | tail -$(expr `cat ${dataset_prefix}${i} | wc -l` - 2) | sed -n 's/://p' > ${prefix}${i}${suffix}
done
