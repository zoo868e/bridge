set terminal eps font "Helvetica"

# if(!exists("input")) exit gnuplot
# if(!exists("filename")) filename='test.eps'
# if(!exists("Title")) title='Experiment'

set output filename
set multiplot layout 1, 1
set rmargin 10
set key at screen 1, graph 1
set title Title

set grid y
set style data histograms
set style histogram rowstacked
set boxwidth 0.5
set style fill solid 1.0 border -1
set ytics 10 nomirror
set yrange [:100]
set ylabel "Number of Referrals"
set ytics 10
set xtics rotate
set xtics font ", 5"

plot input using 2 t "0", ''using 3 t "1", '' using 4 t "2", '' using 5 t "3", '' using 6 t "4", '' using 7 t "5", '' using 8 t "6", '' using 9 t "7", '' using 10 t "8", '' using 11 t "9", '' using 12 t "10", '' using 13 t "11", '' using 14 t "12", '' using 15:xtic(1) t "13"
