#!/bin/bash

gnuplot -e "filename='hori_17.dat'; xtitle='Size of window'; ytitle='Average time in microseconds'; toptitle='KDTree vs Ort - horizontal 17'; name1='Ort'; name2='KDTree'" plot123.pg > hori_17.png


gnuplot -e "filename='vert_17.dat'; xtitle='Size of window'; ytitle='Average time in microseconds'; toptitle='KDTree vs Ort - vertical 17'; name1='Ort'; name2='KDTree'" plot123.pg > vert_17.png

gnuplot -e "filename='hori_17.dat'; xtitle='Size of window'; ytitle='Jumps'; toptitle='horizontal 17'; name1='Average jumps'; name2='Maximum jump'" plot145.pg > jump_hori_17.png

gnuplot -e "filename='vert_17.dat'; xtitle='Size of window'; ytitle='Jumps'; toptitle='vertical 17'; name1='Average jumps'; name2='Maximum jump'" plot145.pg > jump_vert_17.png

gnuplot -e "filename='hori_17.dat'; xtitle='Size of window'; ytitle='Level'; toptitle='horizontal 17'; name1='Average level'; name2='Maximum level'; name3='Minimum level'" plot1678.pg > level_hori_17.png

gnuplot -e "filename='vert_17.dat'; xtitle='Size of window'; ytitle='Level'; toptitle='vertical 17'; name1='Average level'; name2='Maximum level'; name3='Minimum level'" plot1678.pg > level_vert_17.png


