#!/bin/bash
touch output.sh


sort -r -o output.sh data.csv
cut -d ";" data.csv | head -10 data.csv
content=`sort -r $file | head -30 data.csv`

echo "Traitementd1"

cat > new.csv << $content 



#gnuplot "gd1.gnu"
  


   #faut cut data.csv avant de l'envoyer dans gnuplot
   
    #gcc -o Avl.c Avl && AVL et graphique
    
    
