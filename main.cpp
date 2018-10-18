#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
using namespace std;

typedef vector<int> int1D;
typedef vector<int1D> int2D;
typedef vector<int2D> int3D;
typedef vector<int3D> int4D;

int2D populate (int2D grid, int gridSize);
void display (int2D grid, int gridSize);
bool gameOver (int2D grid, int gridSize);
int move (int4D relativeGrid);
int joinSquares (int currentGrid, int2D grid);
int updateGrid (int currentGrid, int2D grid, int4D relativeGrid);

// Function purely for testing purposes during production

void printGrid (int2D grid, int gridSize) {
	for (int x = 0; x < gridSize; x++) {
		for (int y = 0; y < gridSize; y++) {
			cout << grid[x][y] << " ";
		}
		cout << endl;
	}
}

int main () {
	srand(time(0));

	//	Ask for grid size gridSize
	int gridSize;
	int const limit = 10;
	cout << "Enter a grid size:" << endl;
	cout << "Example: For a 4x4 grid, type \"4\"" << endl;
	cin >> gridSize;

	//	Is gridSize more than 1 (and less than limit)?
	while (gridSize < 2 || gridSize > limit) {
		cout << "Size must be between 2 and " << limit << endl;
		cin >> gridSize;
	}

	//	Define grid as mutidimentional array with the size from gridSize where the first level of the 
	//	array will have the columns of the grid, and the second level will have rows. So for example, 
	//	grid[0][2] will refer to the square which is in the 3rd column from the left and the first row 
	//	from the bottom, and the value will be the number that should be in that square.
	int2D grid(gridSize, int1D(gridSize, 0));

	//	Define relativeGrid as an array with 4 elements. Each element will contain a multidimensional
	//	array similar to grid just that instead of containing the number that goes in each square, it 
	//	will contain another array with the coordinates to get the actual value from grid, just as if 
	//	the relativeGrid was rotated r times clockwise. The purpose of this variable is to be able to 
	//	manipulate the grid in the same way, no matter which direction the user wants to click
	int4D relativeGrid(4, int3D(gridSize, int2D(gridSize, int1D(2, 0))));
	for (int r = 0; r < 4; r++) {
		for (int x = 0; x < gridSize; x++) {
			for (int y = 0; y < gridSize; y++) {
				if (r == 0) {
					relativeGrid[r][x][y][0] = x;
					relativeGrid[r][x][y][1] = y;
				} else {
					relativeGrid[r][x][y][0] = relativeGrid[r - 1][x][y][1];
					relativeGrid[r][x][y][1] = gridSize - 1 - relativeGrid[r - 1][x][y][0];
				}
			}
		}
	}

	grid = populate(grid, gridSize);
	//	while (true) {
	//	every move is a new iteration of this loop.
	//	continue this loop until player has lost.
	grid = populate(grid, gridSize);
	display(grid, gridSize);
	if (gameOver(grid, gridSize)) {
		//	break;
	}
	//	}

	return 0;
}

/*
 * stick some new squares into grid (according to rules of the game). returns grid
 */
int2D populate (int2D grid, int gridSize) {
	int2D emptySquares;
	for (int x = 0; x < gridSize; x++) {
		for (int y = 0; y < gridSize; y++) {
			int value = grid[x][y];
			if (value == 0) {
				int1D coordinates;
				coordinates.push_back(x);
				coordinates.push_back(y);
				emptySquares.push_back(coordinates);
			}
		}
	}
	int noOfEmptySquares = emptySquares.size();
	if (noOfEmptySquares) {
		int randomSquare = rand() % noOfEmptySquares;
		int rand0to9 = rand() % 10;
		int value;
		if (rand0to9 % 10 != 9) {
			value = 2;
		} else {
			value = 4;
		}
		int x = emptySquares[randomSquare][0];
		int y = emptySquares[randomSquare][1];
		grid[x][y] = value;
	}
	return grid;
}

/*
 * Output the grid onto the terminal
 * (Possibly can detect size of terminal and acomodate the grid accordingly)
 * (Possibly use colours)
 */
void display (int2D grid, int gridSize) {
	for (int i = 0; i < gridSize; i++) {
		cout << ".______";
	}
	cout << "." << endl;
	for (int x = 0; x < gridSize; x++) {
		for (int i = 0; i < gridSize; i++) {
			cout << "|      ";
		}
		cout << "|" << endl;
		for (int y = 0; y < gridSize; y++) {
			//	Get number of digits in value
			int value = grid[x][y];
			int length = 1;
			for (int i = 1; value / (int) (pow(10, i)) != 0; i++) {
				length = i + 1;
			}
			cout << "|";
			for (int i = 0; i < (6 - length) / 2 + length % 2; i++) {
				cout << " ";
			}
			cout << value;
			for (int i = 0; i < (6 - length) / 2; i++) {
				cout << " ";
			}
		}
		cout << "|" << endl;
		for (int i = 0; i < gridSize; i++) {
			cout << "|______";
		}
		cout << "|" << endl;
	}
}

/*
 * if empty squares in grid, return false.
 * if any 2 adjacent squares in grid are the same, return false.
 * return true 
 */
bool gameOver (int2D grid, int gridSize) {
	for (int x = 0; x < gridSize; x++) {
		for (int y = 0; y < gridSize; y++) {
			if (!grid[x][y]) {
				return false;
			}
		}
	}
	for (int x = 0; x < gridSize; x++) {
		for (int y = 0; y < gridSize; y++) {
			if (grid[x][y] == grid[x + 1][y] || grid[x][y] == grid[x][y + 1]) {
				return false;
			}
		}
	}
}

/*
 * moves all squares as far as it can in the direction direction.
 * Will do so by swapping the coordinates of every non-zero square in relativeGrid
 * (starting from bottom) with that of the lowest zero square below it and storing that 
 * in currentGrid.
 * return currentGrid
 */
int move (int4D relativeGrid) { }

/*
 * joins squares when moved towards a square of the same value.
 * will do so by iterating through the squares from bottom to top 
 * (using relative coordinates provided by currentGrid), 
 * if square above is the same, square*=2 and square above=0, 
 * and write those new values into grid. 
 * return grid
 */
int joinSquares (int currentGrid, int2D grid) { }

/*
 * uses coordinates from currentGrid to get values from grid 
 * and assign them to newGrid by taking corresponding coordinates from relativeGrid.
 * returns newGrid
 */
int updateGrid (int currentGrid, int2D grid, int4D relativeGrid) { }
