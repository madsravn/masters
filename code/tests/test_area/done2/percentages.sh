#! /bin/bash

./find_percentage kd_vs_ort_vertical.dat $1 > temp.dat
gnuplot -e "filename='temp.dat'; xtitle='lg n'; ytitle='size of slices'; toptitle='$1 % vertical'" plot.pg > percentage_$1_vertical.png

./find_percentage kd_vs_ort_horizontal.dat $1 > temp.dat
gnuplot -e "filename='temp.dat'; xtitle='lg n'; ytitle='size of slices'; toptitle='$1 % horizontal'" plot.pg > percentage_$1_horizontal.png


