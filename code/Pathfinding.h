#pragma once
#define PASSFINDING_H
#ifdef PASSFINDING_H

#include "Jeu.h"

const int DIR = 8; // number of possible directions to go at any position

class Node {
private:
	Vector2f posNode;
	// total distance already travelled to reach the node
	int level;
	// priority=level+remaining distance estimate
	int priority;  // smaller: higher priority

public:
	Node(int, int, int, int);

	Vector2f get_pos() const;
	int get_level() const;
	int get_priority() const;

	void updatePriority(const int & xDest, const int & yDest);

	// give better priority to going strait instead of diagonally
	void nextLevel(const int & i); // i: direction

	// Estimation function for the remaining distance to the goal.
	const int & estimate(const int & xDest, const int & yDest) const;
};

inline bool operator<(const Node & a, const Node & b)
{
	return a.get_priority() > b.get_priority();
}

//////////////////////////////////////////////////////////////////////////////

class Pathfinding {
private:
	vector<vector<int>> map_pass;
	vector<vector<int>> closed_nodes_map;
	vector<vector<int>> open_nodes_map;
	vector<vector<int>> dir_map;
	int dx[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };
	int dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
public:
	Pathfinding();

	string pathfinding(vector<vector<int>>, const int &, const int &, const int &, const int &);
};

#endif // PASSFINDING_H