set terminal png size 800,600
set output "graph6_time.png"

set title "Зависимость времени поиска от числа элементов (KR vs ELF)"
set xlabel "Количество элементов"
set ylabel "Время (сек)"

set grid
set key left top
set xrange [20000:400000]

plot "data6_time.txt" using 1:2 with linespoints title "KR", \
     "data6_time.txt" using 1:3 with linespoints title "ELF"