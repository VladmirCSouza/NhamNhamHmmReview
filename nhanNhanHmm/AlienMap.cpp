/**
Class that manage tile Alien map from the game
The singleton function is in the class header.

@author Vladmir C. Souza
*/

#include "AlienMap.h"
#include <stdlib.h>
#include <time.h>

AlienMap* AlienMap::s_pInstance = 0;

/**
Initialize the Alien map class. 
Use it if you need to recreate the stage.
*/
void AlienMap::init()
{
	srand(time(NULL));
	for (int row = 0; row < numRows; row++)
	{
		for (int col = 0; col < numCols; col++)
		{
			if (col < colsOnInit)
				board[row][col] = getRandAlienType();
			else
				board[row][col] = 0;
		}
	}
}

int AlienMap::getRandAlienType()
{
	return rand() % 4 + 1;
}

int AlienMap::getValue(int row, int col)
{
	return board[row][col];
}

void AlienMap::setValue(int row, int col, int value)
{
	board[row][col] = value;
}

/**
Function responsable to find a valid neighbor for each map cell
@param mNode - the map cell that should be analyzed
@return a vector with all valid neighbors
*/
std::vector<AlienMap::node> AlienMap::findNeighbors(node mNode)
{
	//store the neighbors that the funcion find
	std::vector<node> neighborsFinded;

	//search in all directions
	for (int i = 0; i < dirs.size(); i++)
	{
		//store the current neighbor
		node neighbor = { mNode.row + dirs[i].row, mNode.col + dirs[i].col };

		int startValue = board[mNode.row][mNode.col];
		int neighborValue = board[neighbor.row][neighbor.col];

		//if neighbor and current cell have diferent values (alien types) go to the next neighbor
		if (startValue != neighborValue)
			continue;

		//If the neighbor isn't beyhond the board limits store them in neighborsFinded vector
		if (neighbor.row >= 0 && neighbor.row < numRows
			&& neighbor.col >= 0 && neighbor.col < numCols)
			neighborsFinded.push_back(neighbor);
	}
	//Returns all the neighbors finded
	return neighborsFinded;
}

/**
Function used to find similar adjacent aliens.
Used the "Breadth First Search" for it.
@param int row -> the row start point from the Board (usually the mouse position Y)
@param int col -> the colunm start point from the Board (usually the mouse position X)
return all the adjacent neighbors
*/
std::vector<AlienMap::node> AlienMap::findAdjacent(int row, int col)
{
	node mStart = { row, col };

	//Used to do de research by expandind a ring
	std::queue<node> frontier;
	frontier.push(mStart);

	//Used to check if we already have visited a node, that way we prevent from
	//store the same node twice.
	std::vector<node> visited;
	visited.push_back(mStart);

	while (!frontier.empty())
	{
		//Get the node on top then remove it from queue
		node current = frontier.front();
		frontier.pop();

		//Get the current alien type from Board matrix
		int value = board[current.row][current.col];

		//Calls the findNeighbors function passing by the current node and
		//perform a loop in every neighbor founded
		for (node next : findNeighbors(current))
		{
			//bool flag used to check if the node has already been visited
			bool isVisited = false;
			for (int i = 0; i < visited.size(); i++)
			{
				//Convert the coordinates to a single number just to make easier to check 
				//if they are already visited.
				int numberA = (next.row * 100) + next.col;
				int numberB = (visited[i].row * 100) + visited[i].col;

				//If the node have alread been visited exit the loop
				if (numberA == numberB)
				{
					isVisited = true;
					break;
				}
			}

			//If is not visited store on frontier so we can check their neighbors and
			//store on visited vector so we can have a record of all neighbors visited
			if (!isVisited) {
				frontier.push(next);
				visited.push_back(next);
			}
		}
	}
	//return all the valid neighbors
	return visited;
}

/**
Function responsable push the matrix in direction of the Astronaut.
@return True if the matrix had been pushed or false if not and the game should be over
*/
bool AlienMap::pushMatrix()
{
	if (board[numRows -1][numCols - 1] != 0)//It means that the game is over
		return false;

	int tempBoard[numRows][numCols];

	for (int row = 0; row < numRows; row++)
	{
		for (int col = 0; col < numCols; col++)
		{
			if (col == 0)
				tempBoard[row][col] = getRandAlienType();
			else
				tempBoard[row][col] = board[row][col-1];				
		}
	}

	for (int row = 0; row < numRows; row++)
	{
		for (int col = 0; col < numCols; col++)
		{
			board[row][col] = tempBoard[row][col];

		}
	}

	for (int row = 0; row < numRows; row++)
	{
		for (int col = 0; col < numCols; col++)
			std::cout << tempBoard[row][col] << " ";

		std::cout << "\n";
	}
	return true;
}

/**
Function used to make the "std::remove_if" works.
Check if the value is equals to zero
@param i - the value that checked.
*/
bool isZero(int i)
{
	return i == 0;
}

/**
Function responsable to rearrange the column if we remove a Alien from the middle.
@param col - columns that have Aliens removed from.
*/
void AlienMap::removeEmptySpaces(std::vector<int> col)
{
	for (int j = 0; j < col.size(); j++)
	{
		int currCol = col[j];

		std::vector<int> col;

		for (int row = 0; row < numRows; row++)
		{
			col.push_back(board[row][currCol]);
		}

		std::vector<int>::iterator newIter = std::remove_if(col.begin(), col.end(), isZero);
		col.resize(newIter - col.begin());

		while (col.size() < numRows)
		{
			std::vector<int>::iterator it;
			it = col.begin();
			col.insert(it, 0);
		}

		for (int i = 0; i < col.size(); i++)
		{
			board[i][currCol] = col[i];
		}
	}
}

/**
Function responsable to pullback the matrix when we have a empty column.
@param col - the column that should be removed from table.
*/
void AlienMap::pullMatrix(int col)
{
	if (!checkIfColumnIsEmpty(col))
		return;
	
	if (col >= (numCols - 1))
		return;

	for (int row = 0; row < numRows; row++)
	{
		if(board[row][col + 1] != 0)
			hasPolled = true;

		board[row][col] = board[row][col + 1];
		board[row][col+1] = 0;
	}

	pullMatrix(col - 1);
}

/**
Function responsable check if the column is empty.
@param col - the column that should be analyzed.
*/
bool AlienMap::checkIfColumnIsEmpty(int col)
{
	for (int i = 0; i < numRows; i++)
	{
		if (board[i][col] != 0)
			return false;
	}
	return true;
}

AlienMap::AlienMap()
{
}
AlienMap::~AlienMap()
{
}
