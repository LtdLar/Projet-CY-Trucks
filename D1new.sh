#!/bin/bash 

file="data.csv"

#Création des fichiers nécéssaires
Start=$(date +%s)
touch output.sh
touch debara.sh
touch new.dat
touch names.dat
touch res.dat

#Tri et coupure de data.csv selon deux colonnes
awk '{print $1 $6}' FS=";" data.csv | head -10 data.csv > debara.sh

#Récupération des nom (dans l'ordre)


#Données à récupérer et à utiliser

tail -10 debara.sh > new.dat

#Création du graphique avec gnuplot
gnuplot gd1.gnu

#Affichage du tmps d'éxecution
End=$(date +%s)
echo "Temps d'execution $(($End-$Start)) sec"




#AWK ça marche bien, il reste à bien trier et faire la boucle !!

