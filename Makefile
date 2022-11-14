all: main.o grid.o cell.o
	g++ main.o grid.o cell.o -o Hitori

main.o: main.cpp
	g++ -c main.cpp

grid.o: grid.cpp
	g++ -c grid.cpp

cell.o: cell.cpp
	g++ -c cell.cpp

clean:
	rm -rf *.o
