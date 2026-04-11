gcc:
	gcc -g main1.c hashtab.c bstree.c -o demo.o 
clean:
	rm -f demo.o
run: gcc
	leaks --atExit -- ./demo.o
