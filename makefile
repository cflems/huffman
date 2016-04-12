all:
	gcc *.c -o hufftree
debug:
	gcc *.c -g -o hufftree
clean:
	rm -f *.o hufftree *.huff *.dhuff
