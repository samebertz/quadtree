all: app-quadtree

app-quadtree: main.o structures.o utils.o
	g++ main.o structures.o utils.o -o app-quadtree

main.o: main.cpp
	g++ -Wall -c main.cpp

structures.o: structures.cpp structures.h
	g++ -Wall -c structures.cpp structures.h

utils.o: utils.cpp utils.h
	g++ -Wall -c utils.cpp utils.h

clean:
	rm -rf *.o *.gch app-quadtree
