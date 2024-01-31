Start=$(date +%s)
# Vérifie si le nombre d'arguments est correct
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 fichier_csv"
    exit 1
fi

# Récupère le nom du fichier en argument
fichier_csv="$1"

# Vérifie si le fichier existe
if [ ! -f "$fichier_csv" ]; then
    echo "Le fichier $fichier_csv n'existe pas."
    exit 1
fi

# Trie le fichier CSV en fonction de la 3ème colonne
fichier_trie=$(mktemp)
sort -t';' -k3,3 "$fichier_csv" > "$fichier_trie"

# Compte les occurrences des mots dans la 3ème colonne et stocke les résultats dans un fichier temporaire
occurrences=$(mktemp)
cut -d';' -f3 "$fichier_trie" | uniq -c | sort -nr > "$occurrences"

# Crée le fichier final en ne conservant que les 10 premières lignes
fichier_final="resultat.csv"
head -n 10 "$occurrences" | awk '{print $2 ";" $1}' > "$fichier_final"

# Affiche le chemin du fichier final
echo "Les 10 mots les plus fréquents ont été enregistrés dans $fichier_final."

# Nettoie les fichiers temporaires
rm "$fichier_trie" "$occurrences"

#Affichage du tmps d'éxecution
End=$(date +%s)
echo "Temps d'execution $(($End-$Start)) sec"
