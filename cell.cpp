#include "cell.hpp"

Cell::Cell(unsigned x, unsigned y, int type) {
	this->x = x;
	this->y = y;
	this->type = type;
	this->revealed = false;
	this->minesAround = 0;
}

int Cell::getType(void) {
	return this->type;
}

void Cell::setType(int type) {
	this->type = type;
}

bool Cell::isRevealed(void) {
	return this->revealed;
}

void Cell::reveal(void) {
	this->revealed = true;
}

unsigned Cell::getX(void) {
	return this->x;
}

unsigned Cell::getY(void) {
	return this->y;
}
