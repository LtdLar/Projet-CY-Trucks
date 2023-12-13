 #!/usr/bin/gnuplot -persist
#fichier pour gnuplot


set terminal jpeg
set output 'output.jpeg'
set title 'Traitement d1'
set xlabel 'Nb de trajets effectués'
set ylabel 'Nom'
set yrange [0:10]
set xdata time
set timefmt "%Y-%m-%d"
set xtics format "%d-%m"
plot "data.csv" using 1:3 with boxes lc rgb"blue"
    
    #data est trop lourd
