set terminal eps font "Helvetica"

# gnuplot -e "input_file=generated data file" -e "output_file=output file name" -e "Title=your title" stackedH.gnuplot

# if(!exists("input_file")) exit gnuplot
# if(!exists("output_file")) output_file='test.eps'
# if(!exists("Title")) title='Experiment'

set output output_file
set title Title

set style data histograms
set style fill solid 1.0 border -1
set yrange [0:1000]
set ylabel "Appear times"
unset xtics

plot input_file using 2 notitle
