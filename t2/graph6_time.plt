set terminal png size 900,600
set output "graph6_time.png"

set title "Зависимость времени поиска от числа элементов (KR vs ELF)"
set xlabel "Количество элементов n"
set ylabel "Время поиска t, с"

set grid
set key left top

set xrange [20000:400000]
set yrange [*:*]

plot "data6_time.txt" using 1:2 with lines lw 2 title "KR", \
     "data6_time.txt" using 1:3 with lines lw 2 title "ELF"