all:
	gcc -c node.c -I cnode
	gcc -c func.c -I cnode
	gcc -c main.c
	gcc node.o func.o main.o -o app

expand:
	gcc -c -E node.c -I cnode
	gcc -c -E func.c -I cnode
	gcc -c -E main.c -I cnode
	gcc node.c func.o main.o -o app

.PHONY: clean
clean:
	rm -f *.o *.h.gch app
