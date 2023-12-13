#!/bin/bash

for arg in "$@"; do
    shift
    case "$arg" in
    --d1) 
    sort -r
    #head -10 data.csv
    echo "Traitementd1"
    gnuplot "gd1.gnu"
    
    
    

    ;;
    --d2) echo "TraitementD2"
    ;;
    --l) echo "Traiteentl"
    ;;
    --s) echo "TraitementS"
    ;;
    --t) echo "TraitementT"
    ;;
    *) echo "Aucune option"
        exit 1
    ;;
    esac
done
