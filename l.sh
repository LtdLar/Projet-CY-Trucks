#!/bin/bash
Start=$(date +%s)

#Tri des données à exploiter
awk -F';' '{tab[$1]+=$5} END {for (i in tab) printf "%d;%d\n", i, tab[i]}' data.csv | sort -t';' -r -n -k2 | head -10 | sort -t';' -r -n -k1 > l.csv

#Création du graphique
gnuplot l.gnu

#Affichage du graphique et du temps d'execution
End=$(date +%s)
echo "Temps d'execution $(($End -$Start)) sec"
display l.png
#affichage des 10 trajets les plus longs en fonction de l'identifiant du trajet

