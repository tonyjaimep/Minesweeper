#pragma once

#include "cell.hpp"
#include <array>

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
		void revealAllCells(void);
		~Board(void);
};
