#!/bin/bash

for arg in "$@"; do
    shift
    case "$arg" in
    --d1)
    echo "Traitement d1"
    bash D1new.sh
    ;;
    --d2) 
    echo "Traitementd2"
    bash D2.sh
    ;;
    --l) 
    echo "Traitementl"
    bash l.sh
    ;;
    --s) 
    echo "TraitementS"
    ;;
    --t) 
    echo "TraitementT"
    bash TraitementT.sh
    ;;
    --h)
    echo "Help"
    bash h.sh
    ;;
    '') 
    echo "Aucune option"
    ;;
    esac
done
