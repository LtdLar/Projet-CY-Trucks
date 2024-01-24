awk -F';' '{tab[$1]+=$5} END {for (i in tab) printf "%d;%d\n", i, tab[i]}' data.csv | sort -t';' -r -n -k2 | head -10 | sort -t';' -r -n -k1 > datadistance.csv
cat datadistance.csv

295579;2500
256594;2323
252014;2341
227572;2504
137171;2832
91908;2317
66827;2355
31409;2790
23484;2307
9858;2431
