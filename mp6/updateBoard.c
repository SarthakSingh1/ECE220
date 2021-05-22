/*The mp has us work on three functions used for the main file: countLiveNeighbor, updateBoard, aliveStable. 
countLiveNeighbor does as it’s defined: counts all live neighbors at a cell. 
The algorithm works by using for statements to check each cell surrounding the base cell, including diagonals (i-1 to i+1, j-1 to j+1). 
The if then statements then check if that cell has a one or zero. Since we use a 1-D array, we need to use an equation to check for that location. 
Finally, to make sure we do not count the same cell, we use And in an if statement. 
After passing the conditions, the liveneighbor count increases by 1 and moves to check the next cell. 
If we happen to be checking the same cell as the one we are checking neighbors for, the function encounters a continue. 
At the end, the function returns the liveneighbor count. 
To update the board, we must create a new array that checks for the condition of the game (ex. 3 neighbors, dead cell becomes alive). 
We make a new array using for statements and call the countLiveNeighbor function to check how certain cells react in the new board. 
At the end, the “new board” is equated to the original. 
The aliveStable function checks if anything has changed, returning 0 if there are any changes and 1 if there are. 
The function works in a similar way to the update board function. 
It uses for statements to check each row and board and if statements to see if there are any changes using the same conditions for if the cell stays alive or dead.
partners: iakella2 ahchin2

 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
    int liveneighbors = 0;                                                         // Initializing liveneighbor count to 0
  for (int i = row-1; i <= row+1; i++) {
    if ((i <= boardRowSize-1) && (i >= 0)) {                                       // Make sure row is in bounds of board
      for (int j = col-1; j <= col+1; j++) {                                       // Loop to check every surrounding column of the cell
        if ((j <= boardColSize-1) && (j >= 0)) {                                   // Make sure col is in bounds of board
          if ( (i==row) && (j==col)) {                                             // Makes sure the cell for which you are counting alive neighbors is not checked
            continue;
          }
          else {
             if (board[i*boardColSize+j] == 1) {                                    // If cell is alive
                   liveneighbors = liveneighbors+1;                                 // Increments liveneighbor count
            }
          }
        }
      }
    }
  }  
  return liveneighbors;                                                              // Returns final count of liveneighbors
}

int Index(int x, int y, int width){
    return x+y*width;
}

/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
  int newBoard [boardRowSize * boardColSize];                                                // Creating new array of same size called 'oldboard'
  int liveneighbors = 0;
  for (int i=0; i <= boardRowSize-1; i++) {                                                 // Traversing through every row and column in board
    for (int j=0; j <= boardColSize-1; j++) {
        int index = Index(j, i,boardColSize);                                               // Tranforms a 2d array into one index using the Index function
        liveneighbors = countLiveNeighbor(board, boardRowSize, boardColSize, i, j);         // Get the number of neighbors for each index
        if (liveneighbors == 3) {                                                           // Cases for whether cell will be alive or dead in the next step
            newBoard[index] = 1;
            }
        else if (liveneighbors < 2 || liveneighbors > 3) {
                        newBoard[index] = 0;
            }
        else {
                        newBoard[index] = board[index];
            }
        
        }
  }
    int k = 0;
    while(k < (boardRowSize * boardColSize)){                                                 // Copyinng newBoard into old board
        board[k]=newBoard[k];
        k++;
    }
    
}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize) {
    int liveneighbors = 0;
    for (int i=0; i <= boardRowSize-1; i++){                                                   // Traversing through every row and column in board
        for (int j=0; j <= boardColSize-1; j++) {
            int index = Index(j, i, boardColSize) ;                                            // Convert a [i][j] into a single index
            liveneighbors = countLiveNeighbor(board, boardRowSize, boardColSize, i, j) ;  
            if (liveneighbors==2){                                                             // If the # of neighbors is 2 the cell does not change
                continue;
            }
            else if(board[index]==1 && liveneighbors ==3 ){                                    // If it is alive and have 3 neighbors it stays the same
                continue;
            }
            else if (board[index]==0 && (liveneighbors <2 || liveneighbors >3)){               // If its dead and has under 2 or over 3 neighbors it stays dead 
                continue;
            }
            else{
                return 0;                                               // If the above statments are ever false then the board needs to needs to be changed again
            }
        }
    }
    return 1;                                                                   // If all elements of the array fit the criteria then nothing needs to be changed
} 



