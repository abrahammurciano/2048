#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
using namespace std;

typedef vector<int> int1D;
typedef vector<int1D> int2D;
typedef vector<int2D> int3D;
typedef vector<int3D> int4D;

int2D populate(int2D grid, int gridSize);
void display(int2D grid, int gridSize);
bool gameOver(int2D grid, int gridSize);
int keyPress();
int2D move(int3D relativeGrid, int2D grid, int gridSize);
int2D joinSquares(int3D relativeGrid, int2D grid, int gridSize);

int moves, score;

int main() {
	srand(time(0));

	//	Ask for grid size gridSize
	int gridSize;
	int const max = 10;
	int const min = 2;
	system("clear||CLR");
	cout << "Enter a grid size:" << endl;
	cout << "Example: For a 4x4 grid, type \"4\"" << endl;
	cin >> gridSize;

	//	Is gridSize more than 1 (and less than max)?
	while (gridSize < min || gridSize > max) {
		cout << "Size must be between " << min << " and " << max << endl;
		cin >> gridSize;
	}

	//	Define grid as mutidimentional array with the size from gridSize where
	// the first level of the 	array will have the columns of the grid, and the
	// second level will have rows. So for example, 	grid[0][2] will refer to
	// the square which is in the 3rd column from the left and the first row
	// from the bottom, and the value will be the number that should be in that
	// square.
	int2D grid(gridSize, int1D(gridSize, 0));

	//	Define relativeGrid as an array with 4 elements. Each element will
	// contain a multidimensional 	array similar to grid just that instead
	// of containing the number that goes in each square, it 	will contain
	// another array with the coordinates to get the actual value from grid, just
	// as if 	the relativeGrid was rotated r times clockwise. The purpose of
	// this variable is to be able to 	manipulate the grid in the same way, no
	// matter which direction the user wants to click
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
	while (true) {
		//	every move is a new iteration of this loop.
		//	continue this loop until player has lost.
		grid = populate(grid, gridSize);
		display(grid, gridSize);
		if (gameOver(grid, gridSize)) {
			//	break;
		}
		int direction = keyPress();
		grid = move(relativeGrid[direction], grid, gridSize);
		grid = joinSquares(relativeGrid[direction], grid, gridSize);
		grid = move(relativeGrid[direction], grid, gridSize);
		moves++;
	}

	return 0;
}

/*
 * stick some new squares into grid (according to rules of the game). returns
 * grid
 */
int2D populate(int2D grid, int gridSize) {
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
void display(int2D grid, int gridSize) {
	// Clear Screen
	system("clear||CLR");

	// Print Stats
	cout << string(29, '-') << endl;
	cout << "Moves: " << moves << endl;
	cout << "Score: " << score << endl;
	cout << string(29, '-') << endl;
	
	// Print Grid
	cout << " ______";
	for (int i = 1; i < gridSize; i++) {
		cout << "_______";
	}
	cout << endl;
	for (int x = 0; x < gridSize; x++) {
		for (int i = 0; i < gridSize; i++) {
			cout << "|      ";
		}
		cout << '|' << endl;
		for (int y = 0; y < gridSize; y++) {
			//	Get number of digits in value
			int value = grid[y][gridSize - 1 - x];
			int length = 1;
			for (int i = 1; value / (int)(pow(10, i)) != 0; i++) {
				length = i + 1;
			}
			cout << '|';
			for (int i = 0; i < (6 - length) / 2 + length % 2; i++) {
				cout << ' ';
			}
			if (value) {
				cout << value;
			} else {
				cout << ' ';
			}
			for (int i = 0; i < (6 - length) / 2; i++) {
				cout << ' ';
			}
		}
		cout << '|' << endl;
		for (int i = 0; i < gridSize; i++) {
			cout << "|______";
		}
		cout << '|' << endl;
	}
}

/*
 * if empty squares in grid, return false.
 * if any 2 adjacent squares in grid are the same, return false.
 * return true
 */
bool gameOver(int2D grid, int gridSize) {
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
	return true;
}

/*
 * Awaits for key input. At the moment uses WASD and requires Enter after each
 * input.
 * TODO: change input method to use arrows w/o enter
 */
int keyPress() {
	int direction;
	char key;
	do {
		cin >> key;
	} while (key != 's' && key != 'a' && key != 'd' && key != 'w');
	if (key == 's') {
		direction = 0;
	} else if (key == 'a') {
		direction = 1;
	} else if (key == 'd') {
		direction = 3;
	} else if (key == 'w') {
		direction = 2;
	}

	return direction;
}

/*
 * moves all squares as far as it can in the direction direction.
 * Will do so by swapping the coordinates of every non-zero square in
 * relativeGrid (starting from bottom) with that of the lowest zero square below
 * it and storing that in currentGrid. return currentGrid
 */
int2D move(int3D relativeGrid, int2D grid, int gridSize) {
	for (int x = 0; x < gridSize; x++) {
		int lowestEmpty = -1;
		for (int y = 0; y < gridSize; y++) {
			int xGrid = relativeGrid[x][y][0];
			int yGrid = relativeGrid[x][y][1];
			if (grid[xGrid][yGrid]) {
				if (lowestEmpty != -1) {
					int newXGrid = relativeGrid[x][lowestEmpty][0];
					int newYGrid = relativeGrid[x][lowestEmpty][1];
					grid[newXGrid][newYGrid] = grid[xGrid][yGrid];
					grid[xGrid][yGrid] = 0;
					lowestEmpty++;
				}
			} else if (lowestEmpty == -1) {
				lowestEmpty = y;
			}
		}
	}

	return grid;
}

/*
 * joins squares when moved towards a square of the same value.
 * will do so by iterating through the squares from bottom to top
 * (using relative coordinates provided by currentGrid),
 * if square above is the same, square*=2 and square above=0,
 * and write those new values into grid.
 * return grid
 */
int2D joinSquares(int3D relativeGrid, int2D grid, int gridSize) {
	for(int x = 0; x < gridSize; x++) {
		for (int y = 0; y < gridSize-1; y++) {
			int bottomX = relativeGrid[x][y][0];
			int bottomY = relativeGrid[x][y][1];
			if (grid[bottomX][bottomY]) {
				int topX = relativeGrid[x][y+1][0];
				int topY = relativeGrid[x][y+1][1];
				if (grid[bottomX][bottomY] == grid[topX][topY]) {
					score += (grid[bottomX][bottomY] *= 2);
					grid[topX][topY] = 0;
				}
			}
		}
	}
	
	return grid;
}
