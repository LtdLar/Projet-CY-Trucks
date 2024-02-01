#!/bin/bash 

#Création des fichiers tampons
Start=$(date +%s)
touch output2.sh
touch debara2.sh
touch new2.dat

#Tri des données nécessaire (colonne 5 et 6)
sort -r -k5 -t";" -n -o output2.sh data.csv
cut -d ";" -f "5,6" output2.sh > debara2.sh
#Extraire les 10 premières lignes
head -10 debara2.sh > new2.dat

#Création du graphique
gnuplot gd2.gnu

#Affichage du graphique et du temps d'execution
End=$(date +%s)
echo "Temps d'execution $(($End-$Start)) sec"

display output2.jpeg


