#pragma once

#include <iostream>
#include <vector>
#include <queue>

class AlienMap
{
public:
	//Structure to make easier to select the Board nodes.
	struct node
	{
		int row;
		int col;
	};

	static AlienMap* Instance() {
		if (s_pInstance == 0)
			s_pInstance = new AlienMap();

		return s_pInstance;
	}

	void init();

	static const int numRows = 10;
	static const int numCols = 14;
	int board[numRows][numCols] = { 0 };

	int getValue(int row, int col);
	void setValue(int row, int col, int value);

	//The directions used to search for neighbors
	std::vector<AlienMap::node> dirs = { AlienMap::node{ 1,0 }, AlienMap::node{ 0,-1 }, AlienMap::node{ -1,0 }, AlienMap::node{ 0,1 } };
	
	std::vector<AlienMap::node> findAdjacent(int row, int col);

	bool pushMatrix();
	void pullMatrix(int col);
	bool hasPolled = false;
	bool checkIfColumnIsEmpty(int col);
	void removeEmptySpaces(std::vector<int>col);

private:
	AlienMap();
	~AlienMap();

	static const int colsOnInit = 6; //The number of occupied cols on init

	int getRandAlienType();

	std::vector<node> findNeighbors(node mNode);

	static AlienMap* s_pInstance;
};

typedef AlienMap TheAlienMap;
