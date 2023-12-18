#!/bin/bash

touch outut.sh
#sort -r -o outut.sh data.csv
#cut -d ";"  data.csv

tail -9 data.csv > new.dat
cut -d ";" -f 1,5 new.dat > new.dat 







