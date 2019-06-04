#include <iostream>
#include "board.hpp"
#include "cell.hpp"

using namespace std;

Board::Board(unsigned width, unsigned height, unsigned bombs) {
	unsigned i;
	unsigned j;

	this->width = width;
	this->height = height;

	// initialize random number sequence
	srand(time(NULL));

	// initialize cells
	cells = new Cell** [width];

	for (i=0; i < width; i++) {
		cells[i] = new Cell* [width];
		for (j=0; j < height; j++)
			cells[i][j] = NULL;
	}

	// add mines at random on the map
	for (unsigned i=0; i < bombs; i++) {
		cells[rand() % width][rand() % height] = new Cell(CELL_TYPE_MINE);
	}

	// the rest of the cells are free
	for (i=0; i < width; i++)
		for (j=0; j < height; j++)
			if (NULL == cells[i][j])
				// Sorry for using more than 3 tabs, Linus
				cells[i][j] = new Cell(CELL_TYPE_FREE);
}

/* Board::show
 * Prints board to cout
 *
 * IDEA: here I could add an "output" parameter
 * if output is stream, Board::print there.
 * if output is render target, Board::draw there.
 * Board could be a base class that could be extended
 * to BoardTexture or TextBoard or whatever
 */
void Board::show(void) {
	// iteraton over board
	unsigned i;
	unsigned j;

	cout << "  ";
	for (i=0; i < this->width; i++)
		cout << i + 1;
	cout << endl;

	// print board upper border
	cout << " ┏";
	for (i=0; i < this->width; i++)
		cout << "━";
	cout << "┓" << endl;

	// print board
	for (i=0; i < this->height; i++){
		cout << (char)('A' + i) << "┃";
		for (j=0; j< this->width; j++) {
			switch (cells[i][j]->getType()) {
			case CELL_TYPE_FREE:
				if (cells[i][j]->isRevealed())
					cout << "░";
				else
					cout << "▓";
				break;
			case CELL_TYPE_MINE:
				if (cells[i][j]->isRevealed())
					cout << "*";
				else
					cout << "▓";
				break;
			}
		}
		cout << "┃" << endl;
	}

	// print board lower border
	cout << " ┗";
	for (i=0; i < this->width; i++)
		cout << "━";
	cout << "┛" << endl;
}

Cell* Board::revealCellAt(unsigned x, unsigned y) {
	cells[x][y]->reveal();
	return cells[x][y];
}

void Board::revealAllCells(void) {
	unsigned i;
	unsigned j;

	for (i=0; i < this->width; i++)
		for (j=0; j < this->height; j++)
			this->revealCellAt(i, j);
}

Board::~Board() {
	unsigned i;
	unsigned j;

	for (i=0; i < this->width; i++)
		for (j=0; j < this->height; j++)
			delete cells[i][j];
}
