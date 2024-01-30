
#!/usr/bin/gnuplot -persist

set terminal jpeg
set output 'output1.jpeg'

set xtics rotate by -45
set yrange[0:200000]
set title "D1"
set style fill solid
set style data histograms
plot "new.dat" using 1:xtic(2)

