reset
set terminal png enhanced font "Helvetica,10"
set title "Option -l : Distance=f(Route)"
set output 'l.png'
set yrange [0:3000]
set xlabel "ROUTE ID"
set ylabel "DISTANCE(Km)"
set boxwidth 0.5
set style fill solid
set datafile separator ";"
plot "l.csv" u 2:xtic(1) w boxes lc rgb "green" notitle



























































































