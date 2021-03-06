#ifndef MAP_PATHFINDING_HPP_
#define MAP_PATHFINDING_HPP_

#include "Cell.hpp"

enum class Direction { NORTH, EAST, SOUTH, WEST };

class Pathfinding {
public:

	Pathfinding();
	virtual ~Pathfinding();

	static Cell* getCellByDir(Cell* cell, Direction dir);
};

#endif
