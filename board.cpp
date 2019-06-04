#include <iostream>
#include <vector>
#include "board.hpp"
#include "cell.hpp"

using namespace std;

Board::Board(unsigned width, unsigned height, unsigned mines) {
	// for setting cells
	unsigned i;
	unsigned j;
	// for setting mines
	unsigned x;
	unsigned y;

	this->width = width;
	this->height = height;

	// initialize random number sequence
	srand(time(NULL));

	// initialize cells
	cells = new Cell** [height];

	for (i=0; i < height; i++) {
		cells[i] = new Cell* [width];
		for (j=0; j < width; j++)
			cells[i][j] = new Cell(CELL_TYPE_FREE);
	}

	// add mines at random on the map
	for (i=0; i < mines; i++) {
		x = rand() % width;
		y = rand() % height;

		if (cells[y][x]->getType() == CELL_TYPE_MINE)
			continue;

		cells[y][x]->setType(CELL_TYPE_MINE);

		for (Cell* cellAround : this->getCellsAround(x, y))
			cellAround->minesAround++;
	}
}

vector<Cell*> Board::getCellsAround(unsigned x, unsigned y) {
	vector<Cell*> cellsAround;
	// SIDES
	// left
	if (x > 0) cellsAround.push_back(this->cells[y][x - 1]);
	// right
	if (x < this->width - 1) cellsAround.push_back(this->cells[y][x + 1]);
	// top
	if (y > 0) cellsAround.push_back(this->cells[y - 1][x]);
	// bottom
	if (y < this->width - 1) cellsAround.push_back(this->cells[y + 1][x]);
	// CORNERS
	// top left
	if (x > 0 && y > 0) cellsAround.push_back(this->cells[y - 1][x - 1]);
	// bottom left
	if (x > 0 && y < height - 1) cellsAround.push_back(this->cells[y + 1][x - 1]);
	// top right
	if (x < width - 1 && y > 0) cellsAround.push_back(this->cells[y - 1][x + 1]);
	// bottom right
	if (x < width - 1 && y < height - 1) cellsAround.push_back(this->cells[y + 1][x + 1]);

	return cellsAround;
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
		cout << i + 1 << "┃";
		for (j=0; j< this->width; j++) {
			switch (cells[i][j]->getType()) {
			case CELL_TYPE_FREE:
				if (cells[i][j]->isRevealed()) {
					if (cells[i][j]->minesAround)
						cout << cells[i][j]->minesAround;
					else cout << "░";
				} else {
					cout << "▓";
				}
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

// Here is where most of the magic happens
Cell* Board::revealCellAt(unsigned x, unsigned y) {
	cells[y][x]->reveal();

	// game over, buddy
	if (cells[y][x]->getType() == CELL_TYPE_MINE)
		return cells[y][x];

	// if there are no mines around this cell
	if (cells[y][x]->minesAround == 0) {
		for (Cell* cell : getCellsAround(x, y))
			cell->reveal();
	}

	return cells[y][x];
}

void Board::revealAllCells(void) {
	unsigned i;
	unsigned j;

	for (i=0; i < this->height; i++)
		for (j=0; j < this->width; j++)
			cells[i][j]->reveal();
}

Board::~Board() {
	unsigned i;
	unsigned j;

	for (i=0; i < this->height; i++)
		for (j=0; j < this->width; j++)
			delete cells[i][j];
}
