#!/bin/bash
g++ -O3 -Wall --std=c++11 -march=native -Ofast SAT-alumnes.cpp -Wno-sign-compare -o bin.exe

iters=${1:-5}
rm resultat.txt
cd data
for f in *; do
	if [ $iters -ge 1 ]; then
		echo -n $f "" | tee -ai ../resultat.txt
		../bin.exe < $f | tee -ai ../resultat.txt
	fi

	iters=$((iters-1))

done
cd ..
