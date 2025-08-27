#include <iostream>
using namespace std;

#define N 9  // Size of the Sudoku grid

// Function to print Sudoku grid
void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}

// Check if placing num at grid[row][col] is valid
bool isSafe(int grid[N][N], int row, int col, int num) {
    // Check row
    for (int x = 0; x < N; x++)
        if (grid[row][x] == num)
            return false;

    // Check column
    for (int x = 0; x < N; x++)
        if (grid[x][col] == num)
            return false;

    // Check 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;

    return true;
}

// Backtracking function to solve Sudoku
bool solveSudoku(int grid[N][N], int row, int col) {
    // If reached end of grid -> solved
    if (row == N - 1 && col == N)
        return true;

    // Move to next row if column ends
    if (col == N) {
        row++;
        col = 0;
    }

    // Skip already filled cells
    if (grid[row][col] != 0)
        return solveSudoku(grid, row, col + 1);

    // Try placing numbers 1-9
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;  // Place number

            // Recursively solve next cell
            if (solveSudoku(grid, row, col + 1))
                return true;

            grid[row][col] = 0; // Backtrack
        }
    }

    return false; // Trigger backtracking
}

int main() {
    int grid[N][N] = {
        {5,3,0, 0,7,0, 0,0,0},
        {6,0,0, 1,9,5, 0,0,0},
        {0,9,8, 0,0,0, 0,6,0},

        {8,0,0, 0,6,0, 0,0,3},
        {4,0,0, 8,0,3, 0,0,1},
        {7,0,0, 0,2,0, 0,0,6},

        {0,6,0, 0,0,0, 2,8,0},
        {0,0,0, 4,1,9, 0,0,5},
        {0,0,0, 0,8,0, 0,7,9}
    };

    if (solveSudoku(grid, 0, 0))
        printGrid(grid);
    else
        cout << "No solution exists" << endl;

    return 0;
}

