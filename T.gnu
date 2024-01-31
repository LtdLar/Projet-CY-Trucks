#!/usr/bin/gnuplot -persist

set terminal jpeg
set output 'outputT.jpeg'
set xlabel "Villes"
set ylabel "Nombre de visites"
set xtics () rotate by -45
datafile = "resultats.dat"



set xrange [0:*]
set yrange[0:5000]
set title "T"


set style fill solid
set style data histograms
plot datafile using 1:xtic(2)


