#!/bin/bash 

file="data.csv"


Start=$(date +%s)
touch output.sh
touch debara.sh
touch new.dat
touch names.dat
touch res.dat

sort -r -o output.sh data.csv
cut -d ";" -f 1,6 output.sh > debara.sh
cut -d ";" -f 6 output.sh > names.dat

for i in "names.dat";do
	grep -c "names.dat"[i] data.csv > res.dat
done

tail -10 output.sh > new.dat


gnuplot gd1.gnu

End=$(date +%s)
echo "Temps d'execution $(($End-$Start)) sec"

#problème de valeur, vérifier new.dat

