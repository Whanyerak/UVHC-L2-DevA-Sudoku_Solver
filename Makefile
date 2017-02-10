all: main
	
main: main.c grid.o
	gcc -o main main.c grid.o -Wall -Wextra -O2
	
grid.o: grid.c grid.h 
	gcc -c grid.c -Wall -Wextra -O2

clean:
	rm -f *.o main
