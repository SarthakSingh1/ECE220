
#include "sudoku.h"
// partners: iakella2 ahchin2
/*
Introduction Paragraph: This program solves a sudoku puzzle through recursion. 
Given an initial board the program searches for empty spaces which need to be filled and then runs through all the possible combinations of values that would work on that board using recursion. 
For example, if the program cannot fill a cell with a value from 0-9 it backtracks to the previous cell and tries to switch that value before proceeding forward. 
Through recursion the program will  run until each slot has a valid number in it. 
To make sure that a number was valid we utilized 3 functions to check if a certain value was in the same row, column, or 3X3 grid of a specific place on the board. 
*/

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);		// Checks if row is within bounds of puzzle

  // BEG TODO
	for(int x = 0;x<9;x++){
    	if(sudoku[i][x] == val){ // Checks each row to see if 'val' is already in the puzzle
        	return 1;										// If so, return 1
    	}
	}
	return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);											// Checks if column is within bounds of puzzle
  // BEG TODO
 
	for(int y = 0; y<9; y++){
    	if(sudoku[y][j] == val){ 									// Checks each column to see if 'val' is already in the puzzle
        	return 1;										// If so, return 1
    	}
	}
	return 0;
 
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
 
 
  // BEG TODO
	int min_row = (i/3) * 3;			// Setting row and column bounds for the 3x3 zone being checked 
	int max_row = min_row + 2;
	int min_col = (j/3) * 3;
	int max_col = min_col + 2;

	for (int x = min_row; x <= max_row; x ++) {									 // Traverse through the 3x3 zone
    	for (int y = min_col; y <= max_col; y ++) {
        	if (sudoku[x][y] == val) {									// If 'val' is already in zone, return 1
            	return 1;
        	}
    	}
	}
	return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);																																												// Checks to make sure i and j are within bounds

  // BEG TODO
	if (is_val_in_col(val, j, sudoku) || is_val_in_row(val, i, sudoku) || is_val_in_3x3_zone(val, i, j, sudoku)) {	// If value is already in the row, column, or 3x3, it is not valid --> return 0
           	return 0;
   	}

    
  return 1;																																																									// Else, return 1 because number is valid at that cell location
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int done(int sudoku[9][9]){							// Function checks if all cells in the sudoku have been filled 
  int i, j;
  for (i = 0; i < 9; i++){					// Traversing through every row and column in the sudoku puzzle
    for (j = 0; j < 9; j++){
      if (sudoku[i][j] == 0){						// If any cell is equal to 0 - unassigned - return 0
        return 0;
      }
    }
  }
  return 1;						// If not, all cells are assigned and return 1
}
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
  int x,y,num, i, j;
  if (done(sudoku) ==1) {				// Call 'done' function to see if you are done solving 
    return 1;
  }
  else {
    for (i =0; i<9; i++) {				// Traverse through every row and column
      for (j = 0; j<9; j++) {
        if(sudoku[i][j] == 0){				// Once empty cell is found, save the row and column values and break out of loop
          x=i;
          y=j;
          break;
        }
      }
      if(j<9) {								// Force break out of larger loop 
        break;
      }
    }
  }
	for (int num = 1; num <= 9; num++) {				// Find valid number to place in empty cell
  	if(is_val_valid(num, x, y, sudoku) == 1) {   	 
    	sudoku[x][y] = num;
    	if(solve_sudoku(sudoku) == 1){					// Recursively call 'solve_sudoku' to see if sudoku is solved
    		return 1;	
  		}
    	sudoku[x][y] = 0;						// If not, backtrace and set cell value to unassigned
  	}
 	}
  return 0;
}
// END TODO.

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {							// Traverse through all rows and columns and print the value at that cell
	for(j=0; j<9; j++) {
  	printf("%2d", sudoku[i][j]);
	}
	printf("\n");							// At the end of every row, start a new line
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
	for(j=0; j<9; j++) {
  	fscanf(reader, "%d", &sudoku[i][j]);
	}
  }
  fclose(reader);
}



