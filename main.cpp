#include <cmath>
#include <ctime>
#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> int1D;
typedef vector<int1D> int2D;
typedef vector<int2D> int3D;
typedef vector<int3D> int4D;

void populate();
void display();
bool gameOver();
void keyPress();
void move();
void joinSquares();
void clear();

int moves, score, gridSize, direction = -3;
int2D grid(0);
int2D gridOld(0);
int4D relativeGrid(0);
int const maxGridSize = 9;
int const minGridSize = 2;

int main() {
	srand(time(0));
	clear();

	while (true) {
		//	Ask for grid size gridSize
		//	Is gridSize more than 1 (and less than max)?
		do {
			cout << "Enter a grid size:" << endl;
			char x;
			cin >> x;
			gridSize = (int)x - (int)'0';
			clear();
		} while ((gridSize < minGridSize || gridSize > maxGridSize)
					 ? (bool)(cout << "Size must be an integer between "
								   << minGridSize
								   << " and "
								   << maxGridSize
								   << endl)
					 : false);

		//	Define grid as mutidimentional array with the size from gridSize
		// where
		// the first level of the 	array will have the columns of the grid, and
		// the
		// second level will have rows. So for example, 	grid[0][2] will
		// refer
		// to
		// the square which is in the 3rd column from the left and the first row
		// from the bottom, and the value will be the number that should be in
		// that
		// square.
		grid.resize(0);
		grid.resize(gridSize, int1D(gridSize, 0));

		//	Define relativeGrid as an array with 4 elements. Each element will
		// contain a multidimensional 	array similar to grid just that instead
		// of containing the number that goes in each square, it 	will contain
		// another array with the coordinates to get the actual value from grid,
		// just
		// as if 	the relativeGrid was rotated r times clockwise. The purpose
		// of
		// this variable is to be able to 	manipulate the grid in the same way,
		// no
		// matter which direction the user wants to click
		relativeGrid.resize(0);
		relativeGrid.resize(4, int3D(gridSize, int2D(gridSize, int1D(2, 0))));
		for (int r = 0; r < 4; r++) {
			for (int x = 0; x < gridSize; x++) {
				for (int y = 0; y < gridSize; y++) {
					if (r == 0) {
						relativeGrid[r][x][y][0] = x;
						relativeGrid[r][x][y][1] = y;
					} else {
						relativeGrid[r][x][y][0] = relativeGrid[r - 1][x][y][1];
						relativeGrid[r][x][y][1] =
							gridSize - 1 - relativeGrid[r - 1][x][y][0];
					}
				}
			}
		}

		moves = 0;
		score = 0;
		populate();
		populate();

		while (true) {
		newTurn:;
			//	every move is a new iteration of this loop.
			//	continue this loop until player has lost.
			display();
			if (gameOver()) {
				break;
			}

			do {
				if (direction == -1 && moves != 0) {
					// Undo
					grid = gridOld;
					direction = -3;
					moves--;
					goto newTurn;
				}
				if (direction == -2) {
					// Quit
					clear();
					direction = -3;
					goto playAgainPrompt;
				}
				keyPress();
			} while (direction < 0);

			gridOld = grid;
			move();
			joinSquares();
			move();
			if (grid != gridOld) {
				populate();
				moves++;
			}
		}

		char yn;
		cout << endl << "Game over!" << endl;
		do {
		playAgainPrompt:
			cout << "Do you want to play again? (Y/N)" << endl;
			cin >> yn;
			clear();
		} while (!(yn == 'Y' || yn == 'y' || yn == 'N' || yn == 'n'));

		if (yn == 'N' || yn == 'n') {
			break;
		}
	}

	return 0;
}

/*
 * Clear the screen
 */
void clear() {
	system("clear||CLS");
}

/*
 * stick some new squares into grid (according to rules of the game). returns
 * grid
 */
void populate() {
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
}

/*
 * Output the grid onto the terminal
 * (Possibly can detect size of terminal and acomodate the grid accordingly)
 * (Possibly use colours)
 */
void display() {
	// Clear Screen
	clear();

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
bool gameOver() {
	// Check if there's an empty square
	for (int x = 0; x < gridSize; x++) {
		for (int y = 0; y < gridSize; y++) {
			if (!grid[x][y]) {
				return false;
			}
		}
	}

	// Check if there are any possible joins
	for (int x = 0; x < gridSize - 1; x++) {
		for (int y = 0; y < gridSize - 1; y++) {
			if (grid[x][y] == grid[x + 1][y] || grid[x][y] == grid[x][y + 1]) {
				return false;
			}
		}
	}
	// Check for possible joins on last row and column
	int last = gridSize - 1;
	for (int i = 0; i < last; i++) {
		if (grid[i][last] == grid[i + 1][last] ||
			grid[last][i] == grid[last][i + 1]) {
			return false;
		}
	}
	return true;
}

/*
 * Awaits for key input. At the moment uses WASD and requires Enter after each
 * input.
 * TODO: change input method to use arrows w/o enter
 */
void keyPress() {
	char key;
	cin >> key;
	if (key == 's') {
		direction = 0;  // Down
	} else if (key == 'a') {
		direction = 1;  // Left
	} else if (key == 'd') {
		direction = 3;  // Rgiht
	} else if (key == 'w') {
		direction = 2;  // Up
	} else if (key == 'z') {
		direction = -1;  // Undo
	} else if (key == 'q') {
		direction = -2;  // Quit
	} else {
		direction = -3;  // Invalid
	}
}

/*
 * moves all squares as far as it can in the direction direction.
 * Will do so by swapping the coordinates of every non-zero square in
 * relativeGrid (starting from bottom) with that of the lowest zero square below
 * it and storing that in currentGrid. return currentGrid
 */
void move() {
	for (int x = 0; x < gridSize; x++) {
		int lowestEmpty = -1;
		for (int y = 0; y < gridSize; y++) {
			int xGrid = relativeGrid[direction][x][y][0];
			int yGrid = relativeGrid[direction][x][y][1];
			if (grid[xGrid][yGrid]) {
				if (lowestEmpty != -1) {
					int newXGrid = relativeGrid[direction][x][lowestEmpty][0];
					int newYGrid = relativeGrid[direction][x][lowestEmpty][1];
					grid[newXGrid][newYGrid] = grid[xGrid][yGrid];
					grid[xGrid][yGrid] = 0;
					lowestEmpty++;
				}
			} else if (lowestEmpty == -1) {
				lowestEmpty = y;
			}
		}
	}
}

/*
 * joins squares when moved towards a square of the same value.
 * will do so by iterating through the squares from bottom to top
 * (using relative coordinates provided by currentGrid),
 * if square above is the same, square*=2 and square above=0,
 * and write those new values into grid.
 * return grid
 */
void joinSquares() {
	for (int x = 0; x < gridSize; x++) {
		for (int y = 0; y < gridSize - 1; y++) {
			int bottomX = relativeGrid[direction][x][y][0];
			int bottomY = relativeGrid[direction][x][y][1];
			if (grid[bottomX][bottomY]) {
				int topX = relativeGrid[direction][x][y + 1][0];
				int topY = relativeGrid[direction][x][y + 1][1];
				if (grid[bottomX][bottomY] == grid[topX][topY]) {
					score += (grid[bottomX][bottomY] *= 2);
					grid[topX][topY] = 0;
				}
			}
		}
	}
}
