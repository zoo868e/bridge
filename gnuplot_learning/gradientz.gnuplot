##
## Argument:
##		X	:	xlabel
##		Y	:	ylabel
##		xmin:	minimum of xrange
##		ymin:	minimum of yrange
##		xmax:	maximum of xrange
##		ymax:	maximum of yrange
##	filename:	output file name
##		IN	:	input data file name
##
set terminal eps font "Helvetica"

unset key
set output filename
set palette defined (0 "blue", 0.25 "green", 0.50 "yellow", 0.75 "orange",  1 "red")

set xrange[xmin:xmax]
set xlabel X
set yrange[ymin:ymax]
set ylabel Y
#set cbrange[0.6:0.95]
set title "correlation coefficient"
plot IN u 1:2:3 w p pt 7 ps 0.5 lc palette z
#set cbrange[25:60]
set title "Distance = 0"
plot IN u 1:2:4 w p pt 7 ps 0.5 lc palette z
#set cbrange[65:100]
set title "Distance <= 1"
plot IN u 1:2:5 w p pt 7 ps 0.5 lc palette z
#set cbrange[90:100]
set title "Distance <= 2"
plot IN u 1:2:6 w p pt 7 ps 0.5 lc palette z
