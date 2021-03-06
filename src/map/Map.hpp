#ifndef MAP_HPP_
#define MAP_HPP_

#include <ostream>
#include <string>
#include <vector>
#include <map>
class Team;
class Attack;
#include "Cell.hpp"

class Map {
public:

	struct Node;
	struct NodeComparator;

	std::vector<Cell*> cells;
	int height;
	int width;
	int sx;
	int sy;

	std::map<std::string, std::vector<Cell*>> path_cache;

	int nb_cells;
	int type;

	std::vector<std::vector<Cell*>> coord;
	std::vector<Cell*> obstacles;

	int min_x = -1;
	int max_x = -1;
	int min_y = -1;
	int max_y = -1;

	Map(int width, int height, int obstacles, const std::vector<Team*>& teams);
	virtual ~Map();

	Cell* getCell(int id);
	Cell* getCell(int x, int y);
	std::vector<Cell*> getObstacles();
	Cell* getRandomCell();
	Cell* getRandomCell(int part);

	void generate(int obstacles, const std::vector<Team*>& teams);
	void clear();
	void positionChanged();

	void drawMap();
	void drawMap(std::vector<Cell*> path);

	bool canUseAttack(const Cell* caster, const Cell* target, const Attack* attack) const;

	int getDistance2(const Cell* c1, const Cell* c2) const;
	double getDistance(const Cell* c1, const Cell* c2) const;
	int getCellDistance(const Cell* c1, const Cell* c2) const;
	int getCellDistance(const Cell* c1, const std::vector<const Cell*> cells) const;

	bool line_of_sight(const Cell* start, const Cell* end) const;
	bool line_of_sight_attack(const Cell* start, const Cell* end, const Attack* attack, const std::vector<const Cell*> ignoredCells) const;
	bool line_of_sight_ignored(const Cell* start, const Cell* end, std::vector<const Cell*> ignored) const;

	const std::vector<const Cell*> get_cells_around(const Cell* const c) const;

	std::vector<const Cell*> get_path_between(const Cell* start, const Cell* end, std::vector<const Cell*> ignored_cells) const;

	std::vector<const Cell*> get_path(const Cell* start, std::vector<const Cell*> end_cells, std::vector<const Cell*> ignored_cells) const;

	const Cell* int_to_cell(int cell);

	void print() const;
	void draw_path(const std::vector<const Cell*> path, const Cell* cell1, const Cell* cell2) const;

	Json json() const;

	friend std::ostream& operator << (std::ostream& os, const Map& map);

	static std::vector<Node> visited;
	static std::vector<bool> opened;
};

struct Map::Node {
	const Cell* cell = nullptr;
	unsigned short parent = 0;
	unsigned short cost = std::numeric_limits<unsigned short>::max();
	unsigned short weight = std::numeric_limits<unsigned short>::max();

	Node() {};
	Node(const Cell* cell, int cost) : cell(cell), cost(cost) {};
};

struct Map::NodeComparator {
	bool operator () (const Node& o1, const Node& o2) {
		return o1.weight > o2.weight;
	}
};

#endif
