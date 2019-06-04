#include <iostream>
#include <cstdio>
#include "board.hpp"

// TODO: Uncomment and build this darn game a GUI
// #include <SFML/Graphics.hpp>

int main(void) {
	unsigned row;
	unsigned column;

	//	create a board
	Board board = Board(5, 5, 3);
	board.show();

	// game loop
	while (true) {
		// reveal a cell
		cout << "Enter the <row>, <column> to reveal: ";
		scanf("%d, %d", &row, &column);
		while (getchar() != '\n');
		if (board.revealCellAt(column - 1, row - 1)->getType() == CELL_TYPE_MINE) {
			printf("You lost!\n");
			break;
		}
		board.show();
	}

	board.revealAllCells();
	board.show();

	return 0;
}
