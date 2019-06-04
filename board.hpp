#pragma once

#include "cell.hpp"
#include <vector>

using namespace std;

class Board {
	private:
		unsigned width;
		unsigned height;
		// 2D Cell array
		Cell* **cells;
	public:
		Board(unsigned, unsigned, unsigned);
		Cell* revealCellAt(unsigned, unsigned);
		void show(void);
		vector<Cell*> getCellsAround(unsigned, unsigned);
		void revealAllCells(void);
		~Board(void);
};
