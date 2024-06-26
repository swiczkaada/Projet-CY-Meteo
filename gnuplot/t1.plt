reset
set terminal png
set output '../data/t1.png'
set datafile separator ","

set key bmargin center horizontal
set title "Graphique t1" font ",20"
set xlabel "Id station"
set ylabel "Temp moyenne, min, max"
set autoscale

Shadecolor = "#80E0A080"

plot [*:*] [*:*] '../data/tri_t1.csv' using 1:3:4 with filledcurve fc rgb Shadecolor title "Temperature minimum et maximum", '' using 1:2 smooth mcspline title "Temperature moyenne"
