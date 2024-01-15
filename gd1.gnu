 #!/usr/bin/gnuplot -persist

set terminal jpeg
set output 'output.jpeg'


set xrange[0:10]
set yrange[0:10]
set xlabel 'Nb de trajets effectués'
set ylabel 'Nom'
set title 'Traitement d1'
set boxwidth 0.9 relative
set style fill solid 1.0

plot "new.dat" with boxes 
