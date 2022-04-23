# gnuplot -e "input=generatd data file" -e "filename=output file name" -e "Title=title" stackedH0_13.gnuplot
set terminal eps font "Helvetica"

# if(!exists("input")) exit gnuplot
# if(!exists("filename")) filename='test.eps'
# if(!exists("Title")) title='Experiment'

set output filename
set multiplot layout 1, 1
set rmargin 10
set key at screen 1, graph 1
set key invert
set title Title


set style line 1 lt rgb '#ffd700'
set style line 2 lt rgb '#006400'
set style line 3 lt rgb '#00008b'
set style line 4 lt rgb '#ee82ee'
set style line 5 lt rgb '#d2b48c'
set style line 6 lt rgb '#fa8072'
set style line 7 lt rgb '#800080'
set style line 8 lt rgb '#ff00ff'
set style line 9 lt rgb '#800000'
set style line 10 lt rgb '#00ffff'
set style line 11 lt rgb '#a52a2a'
set style line 12 lt rgb '#000080'
set style line 13 lt rgb '#4b0082'
set style line 14 lt rgb '#da70d6'


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

plot input using 2 ls 1 t "0", ''using 3 ls 2 t "1", '' using 4 ls 3 t "2", '' using 5 ls 4 t "3", '' using 6 ls 5 t "4", '' using 7 ls 6 t "5", '' using 8 ls 7 t "6", '' using 9 ls 8 t "7", '' using 10 ls 9 t "8", '' using 11 ls 10 t "9", '' using 12 ls 11 t "10", '' using 13 ls 12 t "11", '' using 14 ls 13 t "12", '' using 15:xtic(1) ls 14 t "13"
