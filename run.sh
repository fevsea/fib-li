#!/bin/bash
g++ -O3 -Wall -march=native -Ofast SAT-alumnes.cpp -o bin.exe

iters=${1:-5}
cd data
for f in *; do
	if [ $iters -ge 1 ]; then
		echo $f
		echo "========================"
		/usr/bin/time --quiet -f "Time: %e" ../bin.exe < $f | tee ../resultat.txt
		echo ""
	fi

	iters=$((iters-1))

  
done
cd ..
