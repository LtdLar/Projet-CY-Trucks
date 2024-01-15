#!/bin/bash 
touch output2.sh
touch debara2.sh
touch new2.dat

Start=$(date +%s)
touch output2.sh
touch debara2.sh
touch new2.dat

sort -r -k5 -t";" -n -o output2.sh data.csv
cut -d ";" -f "5,6" output2.sh > debara2.sh

head -10 debara2.sh > new2.dat


gnuplot gd2.gnu


End=$(date +%s)
echo "Temps d'execution $(($End-$Start)) sec"

display output2.jpeg

#Fonctionnel, bug des noms sur l'axe X
