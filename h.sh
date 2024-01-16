#!/bin/bash 

echo "Besoin d'aide ?
    utilisez -h, sinon -D1; -D2 ou -exit"


for arg in "$@" ; do
   shift
   case "$arg" in
      --D1) echo "Ici on va mettre le programme D1 !"
      ;;
      --D2) echo "Ici on va mettre le programme D2 !"
      ;;
      --S) echo "Ici on va mettre le programme S !"
      ;;
      --h) echo "Aide"
      ;;
      *) echo "aucune option détectée"
         exit 1
      ;;
   esac
done

