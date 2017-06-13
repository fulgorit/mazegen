
#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <vector>

class Cell {
	public:
	std::vector<int> directions;
	bool up, down, right, left;
	int visited;
	int tree;
	Cell ();
};



#endif
