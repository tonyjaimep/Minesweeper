#pragma once

#define CELL_TYPE_MINE 1
#define CELL_TYPE_FREE 2

class Cell {
	private:
		bool revealed;
		int type;
		unsigned x;
		unsigned y;
	public:
		unsigned minesAround;
		Cell(unsigned, unsigned, int);
		void reveal(void);
		int getType(void);
		void setType(int);
		bool isRevealed(void);
		unsigned getX(void);
		unsigned getY(void);
};
