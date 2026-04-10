gcc:
	gcc main.c hashtab.c bstree.c -o 1
clean:
	rm -f 1
run: gcc
	./1