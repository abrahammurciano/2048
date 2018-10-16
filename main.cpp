#include <iostream>
using namespace std;

int rotate (int times);
int populate (int grid);
void display (int grid);
int move (int relativeGrid);
int joinSquares (int currentGrid, int grid);
int updateGrid (int currentGrid, int grid, int relativeGrid);
bool gameOver (int grid);

int main () {

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
	int grid [gridSize][gridSize];

	for (int x = 0; x < gridSize; x++) {
		for (int y = 0; y < gridSize; y++) {
			grid[x][y] = 0;
		}
	}
	
	//	Define relativeGrid as an array with 4 elements. Each element will contain a multidimensional
	//	array similar to grid just that instead of containing the number that goes in each square, it 
	//	will contain another array with the coordinates to get the actual value from grid. The purpose 
	//	of this variable is to be able to manipulate the grid in the same way, no matter which direction 
	//	the user wants to click
	int relativeGrid[4][gridSize][gridSize][2];

	return 0;
}

int rotate (int times) {
	/*
	 * will put the coordinates of each square in grid into a newGrid to return, 
	 * but as if newGrid was rotated 90*times degrees clockwise. 
	 * meaning, newGrid[1][2] will contain the coordinates to grid[2][2]. 
	 * (as if you were looking at the grid from the left of it) 
	 * return newGrid
	 */ }

int populate (int grid) {
	/*
	 * stick some new squares into grid (according to rules of the game). returns grid
	 */ }

void display (int grid) {
	/*
	 * Output the grid onto the terminal
	 * (Possibly can detect size of terminal and acomodate the grid accordingly)
	 * (Possibly use colours)
	 */ }

int move (int relativeGrid) {
	/*
	 * moves all squares as far as it can in the direction direction.
	 * Will do so by swapping the coordinates of every non-zero square in relativeGrid
	 * (starting from bottom) with that of the lowest zero square below it and storing that 
	 * in currentGrid.
	 * return currentGrid
	 */ }

int joinSquares (int currentGrid, int grid) {
	/*
	 * joins squares when moved towards a square of the same value.
	 * will do so by iterating through the squares from bottom to top 
	 * (using relative coordinates provided by currentGrid), 
	 * if square above is the same, square*=2 and square above=0, 
	 * and write those new values into grid. 
	 * return grid
	 */ }

int updateGrid (int currentGrid, int grid, int relativeGrid) {
	/*
	 * uses coordinates from currentGrid to get values from grid 
	 * and assign them to newGrid by taking corresponding coordinates from relativeGrid.
	 * returns newGrid
	 */ }

bool gameOver (int grid) {
	/*
	 * if empty squares in grid, return false.
	 * if any 2 adjacent squares in grid are the same, return false.
	 * return true 
	 */ }