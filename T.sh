#!/bin/bash
Start=$(date +%s)
# Vérifie si le nombre d'arguments est correct
#if [ "$#" -ne 1 ]; then
 #   echo "Erreur argument introuvable"
  #  exit 1
#fi

# Récupère le fichier CSV en argument
fichier_csv=data.csv

# Vérifie si le fichier existe
if [ ! -f "$fichier_csv" ]; then
    echo "Le fichier $fichier_csv n'existe pas."
    exit 1
fi

# Trie la troisième colonne du fichier CSV
trier_colonne=$(sort -t';' -k3,3 "$fichier_csv")

# Compte les occurrences des mots dans la troisième colonne
occurrences=$(echo "$trier_colonne" | cut -d';' -f3 | uniq -c)

# Trie les occurrences dans l'ordre décroissant
tri_occurrences=$(echo "$occurrences" | sort -nr)

# Sélectionne les 10 premières lignes (les mots les plus fréquents)
top_10_occurrences=$(echo "$tri_occurrences" | head -n 10)

# Crée un nouveau fichier CSV pour stocker les résultats
nouveau_fichier_dat="resultats.dat"

# Affiche les résultats dans le nouveau fichier DAT
echo "$top_10_occurrences" > "$nouveau_fichier_dat"

echo "Les 10 mots les plus fréquents ont été enregistrés dans $nouveau_fichier_dat."


#Création du graphique avec gnuplot
gnuplot T.gnu

#Affichage du tmps d'éxecution
End=$(date +%s)
echo "Temps d'execution $(($End-$Start)) sec"

display outputT.jpeg



#Regler les noms des villes en deux mots
