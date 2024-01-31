#!/bin/bash

echo "Bienvenue dans CY-Trucks, le logiciel de confiance des transporteurs
    Veuillez choisir l'option choisie en démarrant le programme"

for arg in "$@"; do
    shift
    case "$arg" in
    -d1)
    echo "Traitement d1"
    bash D1new.sh
    ;;
    -d2) 
    echo "Traitementd2"
    bash D2.sh
    ;;
    -l) 
    echo "Traitementl"
    bash l.sh
    ;;
    -s) 
    echo "TraitementS"
    ;;
    -t) 
    echo "TraitementT"
    bash T.sh data.csv
    ;;
    -h)
    echo "Help"
    bash h.sh
    ;;
    *) 
    echo "option invalide"
    ;;
    esac
done
