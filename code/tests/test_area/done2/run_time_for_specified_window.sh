#! /bin/bash

./translate kd_vs_ort_vertical.dat $1 > temp.dat
gnuplot -e "filename='temp.dat'; xtitle='lg n'; ytitle='time'; toptitle='vertical with size = $1'" plot.pg > specified_window_size_$1_vertical.png

./translate kd_vs_ort_horizontal.dat $1 > temp.dat
gnuplot -e "filename='temp.dat'; xtitle='lg n'; ytitle='time'; toptitle='horizontal with size = $1'" plot.pg > specified_window_size_$1_horizontal.png


