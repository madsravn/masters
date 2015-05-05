#!/bin/bash

UPTO=$1
let UPTO=UPTO+1
COUNTER=17

while [ $COUNTER -lt $UPTO ]; do

    gnuplot -e "filename='hori_$COUNTER.dat'; xtitle='Size of window'; ytitle='Average time in microseconds'; toptitle='KDTree vs Ort - horizontal $COUNTER'; name1='Ort'; name2='KDTree'" plot123.pg > hori_$COUNTER.png

    gnuplot -e "filename='vert_$COUNTER.dat'; xtitle='Size of window'; ytitle='Average time in microseconds'; toptitle='KDTree vs Ort - vertical $COUNTER'; name1='Ort'; name2='KDTree'" plot123.pg > vert_$COUNTER.png

    gnuplot -e "filename='hori_$COUNTER.dat'; xtitle='Size of window'; ytitle='Jumps'; toptitle='horizontal $COUNTER'; name1='Average jumps'; name2='Maximum jump'" plot145.pg > jump_hori_$COUNTER.png

    gnuplot -e "filename='vert_$COUNTER.dat'; xtitle='Size of window'; ytitle='Jumps'; toptitle='vertical $COUNTER'; name1='Average jumps'; name2='Maximum jump'" plot145.pg > jump_vert_$COUNTER.png

    gnuplot -e "filename='hori_$COUNTER.dat'; xtitle='Size of window'; ytitle='Level'; toptitle='horizontal $COUNTER'; name1='Average level'; name2='Maximum level'; name3='Minimum level'; name4='amount of tens'" plot16789.pg > level_hori_$COUNTER.png

    gnuplot -e "filename='vert_$COUNTER.dat'; xtitle='Size of window'; ytitle='Level'; toptitle='vertical $COUNTER'; name1='Average level'; name2='Maximum level'; name3='Minimum level'; name4='amount of tens'" plot16789.pg > level_vert_$COUNTER.png
    
    let COUNTER=COUNTER+1



done
