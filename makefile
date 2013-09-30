all: app-quadtree

app-quadtree: main.o structures.o utils.o
	g++ main.o structures.o utils.o -o app-quadtree

main.o: main.cpp
	g++ -c main.cpp

structures.o: structures.cpp structures.h
	g++ -c structures.cpp structures.h

utils.o: utils.cpp utils.h
	g++ -c utils.cpp utils.h

clean:
	rm -rf *.o *.gch app-quadtree
