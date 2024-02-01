#!/bin/bash 

file="data.csv"

#Création des fichiers nécéssaires
Start=$(date +%s)
touch output.sh
touch debara.sh
touch new.dat
touch poub.dat
touch res.dat


# Compte les occurrences des mots dans la troisième colonne et sort -r
occurrences=$(cut -d ';' -f 1,6 debara.sh | uniq -c debara.sh > new.dat)
sort -r -t";" -o poub.dat new.dat 


# Sélectionne les 10 premières lignes (les mots les plus fréquents)
top_10_occurrences=$(head -10 new.dat)


# Affiche les résultats dans le nouveau fichier DAT
echo "$top_10_occurrences" > res.dat

End=$(date +%s)
#Création du graphique avec gnuplot
gnuplot gd1.gnu
display output1.jpeg

#Affichage du tmps d'éxecution

echo "Temps d'execution $(($End-$Start)) sec"




#Impossible de placer correctement le delimiter, ce qui empêche de mettre toutes les valeurs sur 1 aussi

