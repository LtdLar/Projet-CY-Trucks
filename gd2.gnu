#!/usr/bin/gnuplot -persist

set terminal jpeg
set output 'output2.jpeg'

set xtics rotate by -45
set yrange[0:1500]
set ylabel "Distance parcourue"
set xlabel "Noms"
set title "D2"
set style fill solid
set style data histograms
plot "new2.dat" using 1:xtic(2)

