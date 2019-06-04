#pragma once

#define CELL_TYPE_MINE 1
#define CELL_TYPE_FREE 2

class Cell {
	private:
		bool revealed;
		int type;
	public:
		Cell(int);
		void reveal(void);
		int getType(void);
		bool isRevealed(void);
};
