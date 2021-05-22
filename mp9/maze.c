#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

/*Partners: iakella2 ahchin2
The MP asks us to code functions used within function main.c to create and solve a maze. This MP can be simplified into four functions: createMaze, 
destroyMaze, printMaze, and solveMazeDFS. The createMaze function allocates memory for the maze structure, then the cells, then the rows of the maze
by using malloc. After that, it traverses through the rows and columns to initialize the starting, 'S', and ending, 'E', cell of the maze. The next 
function destroyMaze frees memory in the opposite order that it was allocated to ensure that no memory leaks occur; so first, the rows are freed,
then the cells, and finally the maze structure. printMaze simply traverses through the rows and columns in row-major order and prints the character
at each cell. After the end of each row, it will print the new line feed and then continue onto the next row. The final function is solveMazeDFS.
This function recursively solves the maze by first checking that it isn't the ending cell, out of bounds, or an invalid cell - wall, visited, or
already part of the maze. After that it marks the cell as part of the path and then recursively calls solveMazeDFS to check whether the next
cell in the path should be to the right, left, above, or below the current cell. If all four calls fail, it sets the cell to visited and returns 0.
*/

/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
  FILE *bruh = fopen(fileName, "r");
  if(bruh == NULL) {
    return NULL;
  }
  
  maze_t * thisMaze = malloc(sizeof(maze_t));            // Allocating memory for the maze structure
  
  int i, j, width, height;
  char x;
  
  fscanf(bruh, "%d %d", &width, &height); //the dimensions at the top of the .txt file are copied into width and height
  
        thisMaze->cells = (char **) malloc(sizeof(char *) * height);  //Initialized memory locations for each row
    
  for(i = 0; i<height; i++){
      thisMaze->cells[i] = (char *) malloc (width * sizeof(char));  //for every row  we need to initalize columns for each of those rows

  }
                      
  thisMaze->width = width;    //copy the width and height into "thisMaze"
  thisMaze->height = height;

    //This double loop fills in our 2d array with the pattern from the .TXT file
    // We also initialize the starting and ending index for later use
  
  for(i=0; i<thisMaze->height; i++){
    for(j = 0; j<thisMaze->width; j++){
        x = fgetc(bruh);
                while(x == '\n')
                {
                  x = fgetc(bruh);
                }
            thisMaze->cells[i][j] = x;

                if(thisMaze->cells[i][j] == 'S')
                {
                    thisMaze->startRow = i;
                    thisMaze->startColumn = j;
                }

                if(thisMaze->cells[i][j] == 'E')
                {
                    thisMaze->endRow = i;
                    thisMaze->endColumn = j;
                }
    }
  }
  fclose(bruh);   //close the file and return the pointer
    return thisMaze;
}

 /*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
int i;
  for(i = 0; i< maze->height; i++) {         // Freeing memory in the reverse order that it was created in 'createMaze'
      free(maze->cells[i]);
    }
  free(maze->cells);
  free(maze);
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
  int row = maze->height;
  int col = maze->width;
  int i, j;
    for(i=0; i<row; i++){                            // Traversing through all rows and columns and printing the value there
        for(j=0; j<col; j++){
          printf("%c",maze->cells[i][j]);
        }
      printf("\n");                                    // Printing new line at the end of every row
    }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */
int solveMazeDFS(maze_t * maze, int col, int row)
{
  if (maze->cells[row][col] == 'E') {   
      maze->cells[maze->startRow][maze->startColumn] = 'S';									  // Resetting starting cell as 'S' because it is overwritten later
      return 1;
  }
    if (row >= maze->height || col >= maze->width || col < 0 || row < 0) {   //check to make sure you are within the bounds  of the board
      return 0;
    }
    if (maze->cells[row][col] != 'S' && maze->cells[row][col] != ' ') {     //check if this spot is not a  blank or your starting block(so an invalid space)
      return 0;                                     
    }
    maze->cells[row][col] = '*';
  
    if(solveMazeDFS(maze, col + 1, row)) {													           // Subsequent four 'if' statements recursively call solveMazeDFS for all possible path direction
      return 1;          
    }
    if(solveMazeDFS(maze, col - 1, row)) {     
      return 1;
    }
    if(solveMazeDFS(maze, col, row+1)) {
      return 1;   
    }
    if(solveMazeDFS(maze, col, row-1)) {
      return 1;                    
    }
    maze->cells[row][col] = '~';				//if  you get here that means this is the wrong path and should be set with a ~
    return 0;
}
