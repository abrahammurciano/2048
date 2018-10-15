#include <iostream>
using namespace std;

int function rotate (int times);
int function populate (int grid);
void function display (int grid);
int function move (int relativeGrid);
int function joinSquares (int currentGrid, int grid);
int function updateGrid (int currentGrid, int grid, int relativeGrid);
bool function gameOver (int grid);

int main () {

	

	return 0;
}

int function rotate (int times) {
/*
 * will put the coordinates of each square in grid into a newGrid to return, 
 * but as if newGrid was rotated 90*times degrees clockwise. 
 * meaning, newGrid[1][2] will contain the coordinates to grid[2][2]. 
 * (as if you were looking at the grid from the left of it) 
 * return newGrid
 */

}

int function populate (int grid) {
/*
 * stick some new squares into grid (according to rules of the game). returns grid
 */
	
}

void function display (int grid) {
/*
 * Output the grid onto the terminal
 * (Possibly can detect size of terminal and acomodate the grid accordingly)
 * (Possibly use colours)
 */
	
}

int function move (int relativeGrid) {
/*
 * moves all squares as far as it can in the direction direction.
 * Will do so by swapping the coordinates of every non-zero square in relativeGrid
 * (starting from bottom) with that of the lowest zero square below it and storing that 
 * in currentGrid.
 * return currentGrid
 */
	
}

int function joinSquares (int currentGrid, int grid) {
/*
 * joins squares when moved towards a square of the same value.
 * will do so by iterating through the squares from bottom to top 
 * (using relative coordinates provided by currentGrid), 
 * if square above is the same, square*=2 and square above=0, 
 * and write those new values into grid. 
 * return grid
 */
	
}

int function updateGrid (int currentGrid, int grid, int relativeGrid) {
/*
 * uses coordinates from currentGrid to get values from grid 
 * and assign them to newGrid by taking corresponding coordinates from relativeGrid.
 * returns newGrid
 */
	
}

bool function gameOver (int grid) {
/*
 * if empty squares in grid, return false.
 * if any 2 adjacent squares in grid are the same, return false.
 * return true 
 */
	
}