#include "cell.hpp"

Cell::Cell(int type) {
	this->type = type;
	this->revealed = false;
}

int Cell::getType(void) {
	return this->type;
}

bool Cell::isRevealed(void) {
	return this->revealed;
}

void Cell::reveal(void) {
	this->revealed = true;
}
