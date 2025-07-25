#include "Pathfinding.h"

Node::Node(int xp, int yp, int d, int p) {
	posNode.x = xp; posNode.y = yp; level = d; priority = p;
}

Vector2f Node::get_pos() const {
	return posNode;
}
int Node::get_level() const {
	return level;
}
int Node::get_priority() const {
	return priority;
}

void Node::updatePriority(const int & xDest, const int & yDest) {
	priority = level + estimate(xDest, yDest) * 10; //A*
}

// give better priority to going strait instead of diagonally
void Node::nextLevel(const int & i) { // i: direction
	level += (DIR == 8 ? (i % 2 == 0 ? 10 : 14) : 10);
}

// Estimation function for the remaining distance to the goal.
const int & Node::estimate(const int & xDest, const int & yDest) const {
	static int xd, yd, d;
	xd = xDest - posNode.x;
	yd = yDest - posNode.y;

	// Euclidian Distance
	d = static_cast<int>(sqrt(xd*xd + yd * yd));

	return(d);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

Pathfinding::Pathfinding() {

}

string Pathfinding::pathfinding(vector<vector<int>> map, const int & xStart, const int & yStart,
	const int & xFinish, const int & yFinish) {
	static priority_queue<Node> pq[2]; // list of open (not-yet-tried) nodes
	static int pqi; // pq index
	static Node* n0;
	static Node* m0;
	static int i, j, x, y, xdx, ydy;
	static char c;
	pqi = 0;

	map_pass.clear();
	closed_nodes_map.clear();
	open_nodes_map.clear();
	dir_map.clear();

	for (int i = 0; i < map.size(); i++) {
		map_pass.push_back({});
		closed_nodes_map.push_back({});
		open_nodes_map.push_back({});
		dir_map.push_back({});
		for (int j = 0; j < map[0].size(); j++) {
			if (map[i][j] > 1) map_pass[i].push_back(1);
			else map_pass[i].push_back(0);
			closed_nodes_map[i].push_back(0);
			open_nodes_map[i].push_back(0);
			dir_map[i].push_back(0);
		}
	}

	// create the start node and push into list of open nodes
	n0 = new Node(xStart, yStart, 0, 0);
	n0->updatePriority(xFinish, yFinish);
	pq[pqi].push(*n0);
	open_nodes_map[y][x] = n0->get_priority(); // mark it on the open nodes map

	// A* search
	while (!pq[pqi].empty()) {
		// get the current node w/ the highest priority
		// from the list of open nodes
		n0 = new Node(pq[pqi].top().get_pos().x, pq[pqi].top().get_pos().y,
			pq[pqi].top().get_level(), pq[pqi].top().get_priority());

		x = n0->get_pos().x; y = n0->get_pos().y;

		pq[pqi].pop(); // remove the node from the open list
		open_nodes_map[y][x] = 0;
		// mark it on the closed nodes map
		closed_nodes_map[y][x] = 1;

		// quit searching when the goal state is reached
		//if((*n0).estimate(xFinish, yFinish) == 0)
		if (x == xFinish && y == yFinish)
		{
			// generate the path from finish to start
			// by following the directions
			string path = "";
			while (!(x == xStart && y == yStart))
			{
				j = dir_map[y][x];
				c = '0' + (j + DIR / 2) % DIR;
				path = c + path;
				x += dx[j];
				y += dy[j];
			}

			// garbage collection
			delete n0;
			// empty the leftover nodes
			while (!pq[pqi].empty()) pq[pqi].pop();
			return path;
		}

		// generate moves (child nodes) in all possible directions
		for (i = 0; i < DIR; i++) {

			xdx = x + dx[i]; ydy = y + dy[i];

			if (!(xdx<0 || xdx> map[0].size() - 1 || ydy<0 || ydy>map.size() - 1 || map_pass[ydy][xdx] == 1
				|| closed_nodes_map[ydy][xdx] == 1)) {
				// generate a child node

				m0 = new Node(xdx, ydy, n0->get_level(),
					n0->get_priority());
				m0->nextLevel(i);
				m0->updatePriority(xFinish, yFinish);

				// if it is not in the open list then add into that
				if (open_nodes_map[ydy][xdx] == 0) {
					open_nodes_map[ydy][xdx] = m0->get_priority();
					pq[pqi].push(*m0);
					// mark its parent node direction
					dir_map[ydy][xdx] = (i + DIR / 2) % DIR;
				}
				else if (open_nodes_map[ydy][xdx] > m0->get_priority()) {
					// update the priority info
					open_nodes_map[ydy][xdx] = m0->get_priority();
					// update the parent direction info
					dir_map[ydy][xdx] = (i + DIR / 2) % DIR;

					// replace the node
					// by emptying one pq to the other one
					// except the node to be replaced will be ignored
					// and the new node will be pushed in instead
					while (!(pq[pqi].top().get_pos().x == xdx &&
						pq[pqi].top().get_pos().y == ydy)) {
						//cout << "1" << endl;
						pq[1 - pqi].push(pq[pqi].top());
						//cout << "2" << endl;
						pq[pqi].pop();
						//cout << "3" << endl;
					}

					pq[pqi].pop(); // remove the wanted node

					// empty the larger size pq to the smaller one
					if (pq[pqi].size() > pq[1 - pqi].size()) pqi = 1 - pqi;
					while (!pq[pqi].empty())
					{
						pq[1 - pqi].push(pq[pqi].top());
						pq[pqi].pop();
					}
					pqi = 1 - pqi;
					pq[pqi].push(*m0); // add the better node instead
				}
				else delete m0; // garbage collection
			}
		}
		delete n0; // garbage collection
	}
	return ""; // no route found
}