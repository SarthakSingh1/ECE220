#include "game.h"
/*
  partners: iakella2 and ahchin2
  This code created the game 2048 in the dimentions that the user inputs. The board begins with a random 2 or 4 on the board and it and then based on if you press
  "w" "a" "s" or "d" the cells with values will shift in a certain direction. When a shift happens if 2 cells of the same value are collided they are then combined 
  into  one  cell which has the combined value of the 2 cells. The score is then incremementd by that new  score and then every time the cells  are shifted a new one appears on the screen
  The game ends when all the cells are filled up and nothing can combine. 
  To create out game board we allocation a certain number of memory locations based on how many rows and columns are entered. For example if 3 3 is entered the "cells" pointer points to the 
  top of 9 blank memeory adresses. These adresses are what create the board and how we edit  the values. 
    */

game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure)
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));                                               // Calling malloc function to dynamically allocate memory for game
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
    mygame->rows = rows;                                                                // Creating easily called variables equal to the rows and cols of mygame
    mygame->cols = cols;
    mygame->score = 0;
    for (int i = 0; i < rows * cols; i ++) {                                            // Initializing all cell values to -1 or empty
            mygame->cells[i] = -1;
        }

    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
    game structure to have the given number of rows and columns. Initialize
    the score and all elements in the cells to -1. Make sure that any
    memory previously allocated is not lost in this function.
*/
{
    /*Frees dynamically allocated memory used by cells in previous game,
     then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
    free((*_cur_game_ptr)->cells);
    (*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

     //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct
      (*_cur_game_ptr)->rows = new_rows;            //set  the row instance equal to new_row
      (*_cur_game_ptr)->cols = new_cols;            //same thing for column
      (*_cur_game_ptr)->score = 0;                  //reset the score
      for (int i = 0; i < new_rows * new_cols; i ++) {
          (*_cur_game_ptr)->cells[i] = -1;          //fill all memeory locations with a negative 1
      }

    return;
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
    if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE
 if (row < 0 || row >= cur_game->rows || col < 0 || col >= cur_game->cols) {            // If invalid row or column passed, return NULL
            return NULL;
        }
  return ((cur_game -> cells) + (row * cur_game->cols) + col);                          // If valid, return the adress of the first memeory location  plus the offset created by row and columns
  
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can
   not merge twice in one turn. If sliding the tiles up does not cause any
   cell to change value, w is an invalid move and return 0. Otherwise, return 1.
*/

{
    //YOUR CODE STARTS HERE
    int i=0, j=0, k=0;
   
    int last_shifted=-1;                                                // Allows you to keep track of last row shifted
    int change = 0;                                                     // Indicated whether shift has been made
    int column = cur_game -> cols;                                      // Creating easily called identifiers
    int rows = cur_game -> rows;
    for (j=0; j < column; j++) {                                        // Traversing in column-major order to check vertically for shift
      last_shifted = -1;
      for (i = 0; i < rows; i++) {                                      
        cell *current_cell = get_cell(cur_game, i, j);                  // Setting pointer equal to the cell at row i and column j
        if(*current_cell == -1){                                        // If that cell is empty, continue
            continue;
          }
        else {
            for(k=0; k<i; k++) {
                cell *bruh = get_cell(cur_game, k, j);                  // If not, set pointer equal to cell represented by row k and column j
                if(*bruh == -1) {                                       // If this cell is empty, set *current_cell value in *bruh, empty *current_cell, 
                    *bruh = *current_cell ;                             // and set the flag 'change' equal to 1
                    *current_cell= -1;
                    change = 1;
                    break;
                }
              }
            
            
            if (k-1 != last_shifted) {                                  // Checks to make sure same row isn't merged twice
                cell *new_cell = get_cell(cur_game, k-1, j);            // Creating easily called pointers for vertically adjacent cells
                cell *old_cell = get_cell(cur_game, k, j);
                
                if(*new_cell == *old_cell){                             // Checks to see if two adjacent cells are equivalent, and, therefore, mergeable
                    *new_cell *= 2 ;                                    // Merging cells by doubling value at cell above
                    cur_game -> score += *new_cell;                     // Adjusts score accordingly
                    *old_cell = -1;                                     // Clears bottom merged cell
                    last_shifted = k-1;                                 // Updates the last_shifted row
                    change = 1;
                }
            }
        }
    }
}
   
  return change;
};
               

int move_s(game * cur_game) //slide down
{
    //YOUR CODE STARTS HERE

    int i=0, j=0, k=0;
   
    int last_shifted=-1;                                            // Allows you to keep track of last row shifted
    int change = 0;                                                 // Indicated whether shift has been made
    int column = cur_game -> cols;                                  // Creating easily called identifiers
    int rows = cur_game -> rows;
    for (j= 0; j < column; j++) {                                   // Traversing in column-major order to check vertically for shift
      last_shifted = rows;
      for (i = rows-1; i >= 0; i--) {                               // Starts from bottom row instead of top
        cell *current_cell = get_cell(cur_game, i, j);
        if(*current_cell == -1){                                    // If pointer to cell represented by row i and column j is empty, continue
            continue;
          }
        else {
            for(k= rows-1; k>i; k--) {                              // Traversing from bottom row until i
                cell *bruh = get_cell(cur_game, k, j);
                if(*bruh == -1) {                                   // If pointer to cell represented by row k and column j is empty, set *current_cell
                    *bruh = *current_cell ;                         // value to *bruh, empty *current_cell, set flag 
                    *current_cell= -1;
                    change = 1;
                    break;
                }
              }
            
            
            if (k+1 != last_shifted) {                              // Ensures same row is not merged twice
                cell *new_cell = get_cell(cur_game, k+1, j);        // Creating easily called pointers to vertically adjacent cells 
                cell *old_cell = get_cell(cur_game, k, j);
                
                if(*new_cell == *old_cell){                         // Checks to see if two adjacent cells are equivalent, and, therefore, mergeable
                    *new_cell *= 2 ;                                // Merging cells by doubling value at cell below
                    cur_game -> score += *new_cell;                 // Adjusts score accordingly
                    *old_cell = -1;                                 // Clears top merged cell
                    last_shifted = k+1;                             // Updates the last_shifted row
                    change = 1;
                }
            }
        }
    }
}
    
    
    
    
    return change;
};

int move_a(game * cur_game) //slide left
{
    int i=0, j=0, k=0;
   
    int last_shifted=-1;                                            // Allows you to keep track of last column shifted
    int change = 0;                                                 // Indicated whether shift has been made
    int column = cur_game -> cols;                                  // Creating easily called identifiers
    int rows = cur_game -> rows;
    for (i=0; i < rows; i++) {                                      // Traversing in row-major order to check horizontally for shift
      last_shifted = -1;
      for (j = 0; j < column; j++) {
        cell *current_cell = get_cell(cur_game, i, j);              // If pointer to cell represented by row i and column j is empty, continue
        if(*current_cell == -1){
            continue;
          }
        else {
            for(k=0; k<j; k++) {
                cell *bruh = get_cell(cur_game, i, k);
                if(*bruh == -1) {                                   // If pointer to cell represented by row k and column j is empty, set *current_cell
                    *bruh = *current_cell ;                         // value into *bruh, empty *current_cell , and set flag
                    *current_cell= -1;
                    change = 1;
                    break;
                }
                }
            
            
            if (k-1 != last_shifted) {
                cell *new_cell = get_cell(cur_game, i, k-1);        // Creating easily called pointers for horizontally adjacent cells
                cell *old_cell = get_cell(cur_game, i, k);
                
                if(*new_cell == *old_cell){                         // Checks to see if two adjacent cells are equivalent, and, therefore, mergeable
                    *new_cell *= 2 ;                                // Merging cells by doubling value at cell to the left
                    cur_game -> score += *new_cell;                 // Adjusts score accordingly
                    *old_cell = -1;                                 // Clears right merged cell
                    last_shifted = k-1;                             // Updates the last_shifted column
                    change =1 ;
                }
            }
        }
    }
}
   
  return change;

};

int move_d(game * cur_game){ //slide to the right
    //YOUR CODE STARTS HERE
    int i=0, j=0, k=0;
    int last_shifted=-1;                                            // Allows you to keep track of last column shifted
    int change = 0;                                                 // Indicated whether shift has been made
    int column = cur_game -> cols;                                  // Creating easily called identifiers
    int rows = cur_game -> rows;
    for (i=0; i < rows; i++) {                                      // Traversing in row-major order to check horizontally for shift
      last_shifted = column;
      for (j = column-1; j >= 0; j--) {                             // Starting at right-most column
        cell *current_cell = get_cell(cur_game, i, j);
        if(*current_cell == -1){                                    // If pointer to cell represented by row i and column j is empty, continue
            continue;                               
          }
        else {
            for(k=column-1; k>j; k--) {                             // Traversing backwards until j
                cell *bruh = get_cell(cur_game, i, k);
                if(*bruh == -1) {                                   // If pointer to cell represented by row k and column j is empty, set *current_cell
                    *bruh = *current_cell ;                         // value to *bruh, empty *current_cell, set flag
                    *current_cell= -1;
                    change = 1;
                    break;
                }
                }
            
            
            if (k+1 != last_shifted) {
                cell *new_cell = get_cell(cur_game, i, k+1);        // Creating easily called pointers for horizontally adjacent cells
                cell *old_cell = get_cell(cur_game, i, k);
                
                if(*new_cell == *old_cell){                         // Checks to see if two adjacent cells are equivalent, and, therefore, mergeable
                    *new_cell *=2 ;                                 // Merging cells by doubling value at cell to the right
                    cur_game -> score += *new_cell;                 // Adjusts score accordingly
                    *old_cell = -1;                                 // Clears left merged cell
                    last_shifted = k+1;                             // Updates the last_shifted column
                    change =1;
                }
            }
        }
    }
}
   
  return change;

};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
    Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    //YOUR CODE STARTS HERE
  int row = cur_game->rows;																														 // Creating easily called identifiers
  int col = cur_game->cols;
  int i,j;
  for(i=0; i<row; i++){																																  // Traversing in row-major order
    for(j=0; j<col; j++){
     if(cur_game->cells[i*col+j] == -1){																								// Return 1 if cell is empty
       return 1;
     }
     if(cur_game->cells[i*col+j] == cur_game->cells[(i+1)*col+j] && i < row-1){         // Return 1 if vertically adjacent cells are equivalent
       return 1;
      }
        if(cur_game->cells[i*col+j] == cur_game->cells[i*col+j+1] && j < col-1){        // Return 1 if horizontallu adjacent cells are equivalent
       return 1;
      }
    }
  }
    return 0;
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
    
    cell * cell_ptr;
    cell_ptr =     cur_game->cells;
    
    if (cell_ptr == NULL){
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
    
    
    //check for an empty cell
    int emptycheck = 0;
    int i;
    
    for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
        if ((*cell_ptr) == -1){
                emptycheck = 1;
                break;
        }
        cell_ptr += 1;
    }
    if (emptycheck == 0){
        printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
        exit(0);
    }
    
    int ind,row,col;
    int num;
    do{
        ind = rand()%((cur_game->rows)*(cur_game->cols));
        col = ind%(cur_game->cols);
        row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
    num = rand()%20;
    if(num <= 1){
        *get_cell(cur_game, row, col) = 4; // 1/10th chance
    }
    else{
        *get_cell(cur_game, row, col) = 2;// 9/10th chance
    }
}

int print_game(game * cur_game)
{
    cell * cell_ptr;
    cell_ptr =     cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
    
    printf("\n\n\nscore:%d\n",cur_game->score);
    
    
    printf("\u2554"); // topleft box char
    for(i = 0; i < cols*5;i++)
        printf("\u2550"); // top box char
    printf("\u2557\n"); //top right char
    
    
    for(i = 0; i < rows; i++){
        printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  ");
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    default:
                        printf("  X  ");

                }

            }
            cell_ptr++;
        }
    printf("\u2551\n"); //print right wall and newline
    }
    
    printf("\u255A"); // print bottom left char
    for(i = 0; i < cols*5;i++)
        printf("\u2550"); // bottom char
    printf("\u255D\n"); //bottom right char
    
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{
    int rows,cols;
    char buf[200];
    char garbage[2];
    int move_success = 0;
    
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
    case 'n':
        //get row and col input for new game
        dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
        while (NULL == fgets(buf,200,stdin)) {
            printf("\nProgram Terminated.\n");
            return 0;
        }
        
        if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
        rows < 0 || cols < 0){
            printf("Invalid dimensions.\n");
            goto dim_prompt;
        }
        
        remake_game(&cur_game,rows,cols);
        
        move_success = 1;
        
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

    
    
    
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game);
         print_game(cur_game);
    }

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}

