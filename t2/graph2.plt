set terminal png size 800,600
set output "graph2.png"

set title "Вставка: BST vs Hash"
set xlabel "Количество элементов"
set ylabel "Время (сек)"
set grid
set key left top
set xrange [20000:400000]
set yrange [*:*]

plot "data2.txt" using 1:2 with linespoints title "BST", \
     "data2.txt" using 1:3 with linespoints title "Hash"