gcc:
	gcc main.c hashtab.c bstree.c -o demo.o 
clean:
	rm -f demo.o
run: gcc
	./demo.o
