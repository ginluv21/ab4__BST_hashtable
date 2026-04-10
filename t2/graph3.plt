set terminal png size 800,600
set output "graph6.png"

set title "Коллизии: KR vs ELF"
set xlabel "Количество элементов"
set ylabel "Коллизии"
set grid
set key left top
set xrange [20000:400000]
set yrange [*:*]

plot "data6.txt" using 1:2 with linespoints title "KR", \
     "data6.txt" using 1:3 with linespoints title "ELF"