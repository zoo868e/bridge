#!/bin/bash
formulaID=(`seq 1 13`)
echo "Plotting the graphs with len = "${formulaID[*]}

for i in "${formulaID[@]}"
do
	gnuplot -e "input_file='plot_times_${i}.data'" -e "output_file='times_${i}.eps'" -e "Title='len(card)=${i}'" stackedH.gnuplot
done
