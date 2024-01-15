#!/bin/bash 

Start=$(date +%s)
touch output.sh
touch debara.sh
touch new.dat


sort -r -o output.sh data.csv
cut -d ";" -f 1,6 output.sh > debara.sh
tail -10 debara.sh > new.dat


gnuplot gd1.gnu

End=$(date +%s)
echo "Temps d'execution $(($End-$Start)) sec"

#regarder cmb de personnes ont le plus de route ID
