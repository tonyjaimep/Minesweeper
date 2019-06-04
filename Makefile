minesweeper: main.cpp board.hpp board.cpp cell.hpp cell.cpp
	g++ -c main.cpp board.cpp cell.cpp
	g++ main.o board.o cell.o -o minesweeper
