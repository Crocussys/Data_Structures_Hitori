all: main.o grid.o stack.o cell.o
	g++ main.o grid.o stack.o cell.o -o Hitori

main.o: main.cpp
	g++ -c main.cpp

grid.o: grid.cpp
	g++ -c grid.cpp

cell.o: cell.cpp
	g++ -c cell.cpp

stack.o: stack.cpp
	g++ -c stack.cpp

clean:
	rm -rf *.o