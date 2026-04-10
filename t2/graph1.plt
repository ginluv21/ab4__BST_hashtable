set terminal png size 800,600
set output "graph1.png"

set title "Поиск: BST vs Hash"
set xlabel "Количество элементов"
set ylabel "Время (сек)"
set grid
set key left top
set xrange [20000:400000]
set yrange [*:*]

plot "data1.txt" using 1:2 with linespoints title "BST", \
     "data1.txt" using 1:3 with linespoints title "Hash"