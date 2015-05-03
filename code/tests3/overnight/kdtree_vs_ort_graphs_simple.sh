#!/bin/bash

gnuplot -e "filename='hori_17.dat'; xtitle='Size of window'; ytitle='Average time in microseconds'; toptitle='KDTree vs Ort - horizontal 17'; name1='Ort'; name2='KDTree'" plot123.pg > hori_17.png
gnuplot -e "filename='hori_18.dat'; xtitle='Size of window'; ytitle='Average time in microseconds'; toptitle='KDTree vs Ort - horizontal 18'; name1='Ort'; name2='KDTree'" plot123.pg > hori_18.png
gnuplot -e "filename='hori_19.dat'; xtitle='Size of window'; ytitle='Average time in microseconds'; toptitle='KDTree vs Ort - horizontal 19'; name1='Ort'; name2='KDTree'" plot123.pg > hori_19.png
gnuplot -e "filename='hori_20.dat'; xtitle='Size of window'; ytitle='Average time in microseconds'; toptitle='KDTree vs Ort - horizontal 20'; name1='Ort'; name2='KDTree'" plot123.pg > hori_20.png
gnuplot -e "filename='hori_21.dat'; xtitle='Size of window'; ytitle='Average time in microseconds'; toptitle='KDTree vs Ort - horizontal 21'; name1='Ort'; name2='KDTree'" plot123.pg > hori_21.png
gnuplot -e "filename='hori_22.dat'; xtitle='Size of window'; ytitle='Average time in microseconds'; toptitle='KDTree vs Ort - horizontal 22'; name1='Ort'; name2='KDTree'" plot123.pg > hori_22.png
gnuplot -e "filename='hori_23.dat'; xtitle='Size of window'; ytitle='Average time in microseconds'; toptitle='KDTree vs Ort - horizontal 23'; name1='Ort'; name2='KDTree'" plot123.pg > hori_23.png
gnuplot -e "filename='hori_24.dat'; xtitle='Size of window'; ytitle='Average time in microseconds'; toptitle='KDTree vs Ort - horizontal 24'; name1='Ort'; name2='KDTree'" plot123.pg > hori_24.png


gnuplot -e "filename='vert_17.dat'; xtitle='Size of window'; ytitle='Average time in microseconds'; toptitle='KDTree vs Ort - vertical 17'; name1='Ort'; name2='KDTree'" plot123.pg > vert_17.png
gnuplot -e "filename='vert_18.dat'; xtitle='Size of window'; ytitle='Average time in microseconds'; toptitle='KDTree vs Ort - vertical 18'; name1='Ort'; name2='KDTree'" plot123.pg > vert_18.png
gnuplot -e "filename='vert_19.dat'; xtitle='Size of window'; ytitle='Average time in microseconds'; toptitle='KDTree vs Ort - vertical 19'; name1='Ort'; name2='KDTree'" plot123.pg > vert_19.png
gnuplot -e "filename='vert_20.dat'; xtitle='Size of window'; ytitle='Average time in microseconds'; toptitle='KDTree vs Ort - vertical 20'; name1='Ort'; name2='KDTree'" plot123.pg > vert_20.png
gnuplot -e "filename='vert_21.dat'; xtitle='Size of window'; ytitle='Average time in microseconds'; toptitle='KDTree vs Ort - vertical 21'; name1='Ort'; name2='KDTree'" plot123.pg > vert_21.png
gnuplot -e "filename='vert_22.dat'; xtitle='Size of window'; ytitle='Average time in microseconds'; toptitle='KDTree vs Ort - vertical 22'; name1='Ort'; name2='KDTree'" plot123.pg > vert_22.png
gnuplot -e "filename='vert_23.dat'; xtitle='Size of window'; ytitle='Average time in microseconds'; toptitle='KDTree vs Ort - vertical 23'; name1='Ort'; name2='KDTree'" plot123.pg > vert_23.png
gnuplot -e "filename='vert_24.dat'; xtitle='Size of window'; ytitle='Average time in microseconds'; toptitle='KDTree vs Ort - vertical 24'; name1='Ort'; name2='KDTree'" plot123.pg > vert_24.png

gnuplot -e "filename='hori_17.dat'; xtitle='Size of window'; ytitle='Jumps'; toptitle='horizontal 17'; name1='Average jumps'; name2='Maximum jump'" plot145.pg > jump_hori_17.png
gnuplot -e "filename='hori_18.dat'; xtitle='Size of window'; ytitle='Jumps'; toptitle='horizontal 18'; name1='Average jumps'; name2='Maximum jump'" plot145.pg > jump_hori_18.png
gnuplot -e "filename='hori_19.dat'; xtitle='Size of window'; ytitle='Jumps'; toptitle='horizontal 19'; name1='Average jumps'; name2='Maximum jump'" plot145.pg > jump_hori_19.png
gnuplot -e "filename='hori_20.dat'; xtitle='Size of window'; ytitle='Jumps'; toptitle='horizontal 20'; name1='Average jumps'; name2='Maximum jump'" plot145.pg > jump_hori_20.png
gnuplot -e "filename='hori_21.dat'; xtitle='Size of window'; ytitle='Jumps'; toptitle='horizontal 21'; name1='Average jumps'; name2='Maximum jump'" plot145.pg > jump_hori_21.png
gnuplot -e "filename='hori_22.dat'; xtitle='Size of window'; ytitle='Jumps'; toptitle='horizontal 22'; name1='Average jumps'; name2='Maximum jump'" plot145.pg > jump_hori_22.png
gnuplot -e "filename='hori_23.dat'; xtitle='Size of window'; ytitle='Jumps'; toptitle='horizontal 23'; name1='Average jumps'; name2='Maximum jump'" plot145.pg > jump_hori_23.png
gnuplot -e "filename='hori_24.dat'; xtitle='Size of window'; ytitle='Jumps'; toptitle='horizontal 24'; name1='Average jumps'; name2='Maximum jump'" plot145.pg > jump_hori_24.png


gnuplot -e "filename='vert_17.dat'; xtitle='Size of window'; ytitle='Jumps'; toptitle='vertical 17'; name1='Average jumps'; name2='Maximum jump'" plot145.pg > jump_vert_17.png
gnuplot -e "filename='vert_18.dat'; xtitle='Size of window'; ytitle='Jumps'; toptitle='vertical 18'; name1='Average jumps'; name2='Maximum jump'" plot145.pg > jump_vert_18.png
gnuplot -e "filename='vert_19.dat'; xtitle='Size of window'; ytitle='Jumps'; toptitle='vertical 19'; name1='Average jumps'; name2='Maximum jump'" plot145.pg > jump_vert_19.png
gnuplot -e "filename='vert_20.dat'; xtitle='Size of window'; ytitle='Jumps'; toptitle='vertical 20'; name1='Average jumps'; name2='Maximum jump'" plot145.pg > jump_vert_20.png
gnuplot -e "filename='vert_21.dat'; xtitle='Size of window'; ytitle='Jumps'; toptitle='vertical 21'; name1='Average jumps'; name2='Maximum jump'" plot145.pg > jump_vert_21.png
gnuplot -e "filename='vert_22.dat'; xtitle='Size of window'; ytitle='Jumps'; toptitle='vertical 22'; name1='Average jumps'; name2='Maximum jump'" plot145.pg > jump_vert_22.png
gnuplot -e "filename='vert_23.dat'; xtitle='Size of window'; ytitle='Jumps'; toptitle='vertical 23'; name1='Average jumps'; name2='Maximum jump'" plot145.pg > jump_vert_23.png
gnuplot -e "filename='vert_24.dat'; xtitle='Size of window'; ytitle='Jumps'; toptitle='vertical 24'; name1='Average jumps'; name2='Maximum jump'" plot145.pg > jump_vert_24.png


