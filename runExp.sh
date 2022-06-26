#!/bin/bash
echo "Setting training formula"
# the formula id 13 and 14 is for east called situation
# the remain formula are without any information of opponents
formulaID=( 2 )
called_formulaID=(  )
year=$(date +"%F" | cut -d - -f 1)
month=$(date +"%F" | cut -d - -f 2)
date=$(date +"%F" | cut -d - -f 3)
folder=./result/${year}
prefix=${folder}/${month}${date}_formula_
dataset="./data/wholeStaticForC"
called_dataset="./data/EastOpened.exp"

if [ -d "${folder}" ]; then
	echo "${folder} exist. Starting the experiment..."
else
	echo "${folder} doesn't exist. Creating the folder..."
	mkdir -p ${folder}
	if [ -d "${folder}" ]; then
		echo "${folder} exist. Starting the experiment..."
	else
		echo "Failed to create the folder..."
		echo "Exit the script"
		return 1;
	fi
fi


echo "The training formula is "${formulaID[*]}
echo "The training called_formula is "${called_formulaID[*]}

for i in "${formulaID[@]}"
do
	FILE=${prefix}${i}
	TEMP=${prefix}${i}
	count=1
	while [ -f "$TEMP" ]
	do
		echo "$FILE exists."
		echo "change file name to ${FILE}_${count}"
		TEMP=${FILE}_${count}
		count=`expr ${count} + 1`
	done
	FILE=${TEMP}
	echo "python StaticO_dis.py ${i} ${dataset} > ${FILE}"
	python StaticO_dis.py ${i} ${dataset} > ${FILE}
	echo "head -n $(expr `grep -ni -r "distance = 0" ${FILE} | sed -n 's/\(.*\):.*\([0-9][0-9]\.[0-9]*\)%.*/\1,\2/p' | sort -t, -k2 | tail -1 | cut -d , -f 1` + 4) ${FILE} | tail -n 22 >> ${prefix}best"
	head -n $(expr `grep -ni -r "distance = 0" ${FILE} | sed -n 's/\(.*\):.*\([0-9][0-9]\.[0-9]*\)%.*/\1,\2/p' | sort -t, -k2 | tail -1 | cut -d , -f 1` + 4) ${FILE} | tail -n 22 >> ${prefix}best
done

for i in "${called_formulaID[@]}"
do
	FILE=${prefix}${i}
	TEMP=${prefix}${i}
	count=1
	while [ -f "$TEMP" ]
	do
		echo "$FILE exists."
		echo "change file name to ${FILE}_${count}"
		TEMP=${FILE}_${count}
		count=`expr ${count} + 1`
	done
	FILE=${TEMP}
	echo "python Called_exp.py ${i} ${called_dataset} > ${FILE}"
	python Called_exp.py ${i} ${called_dataset} > ${FILE}
	echo "head -n $(expr `grep -ni -r "distance = 0" ${FILE} | sed -n 's/\(.*\):.*\([0-9][0-9]\.[0-9]*\)%.*/\1,\2/p' | sort -t, -k2 | tail -1 | cut -d , -f 1` + 4) ${FILE} | tail -n 22 >> ${prefix}best"
	head -n $(expr `grep -ni -r "distance = 0" ${FILE} | sed -n 's/\(.*\):.*\([0-9][0-9]\.[0-9]*\)%.*/\1,\2/p' | sort -t, -k2 | tail -1 | cut -d , -f 1` + 4) ${FILE} | tail -n 22 >> ${prefix}best
done
