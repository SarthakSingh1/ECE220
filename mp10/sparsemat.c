#include "sparsemat.h"
#include <stdio.h>
#include <stdlib.h>
/*
The program stores a sparse matrix as a linked list (tuples) of non-zero values. This program is done using load, gv, set, save, destroy, and add.
In load_tuples, we begin by initializing a pointer that will be used to define other pointers in the data structure. Next, we receive data from the file (row/column) and
initial pointers using the pointer we defined earlier. Finally, we grab the x, y coordinates of the nonzero as well as the value (val) of the element. gv or get value 
receives the value (val) if it exists and returns it. Set which makes up most of the program handles five cases when setting the value in the matrix. If the matrix is 
empty, defined as head being null, we create a new node and set it as the head.  If the value is zero, we remove the corresponding node if it exists or ignore
it otherwise.  If the value is non-zero, we either must update an existing node or create a new one and insert it at the proper location. The general idea of the code, is
to initialize and place the data in a new node and update the pointer. Save is used to write a txt file and is done by opening a File and editing it. Destroy
is used to free or clear all of the data and is done by going through each node and using the command free. Finally we have add which is used when we want to add 
matrices. We do this step by "creating new matrices" (initializing pointers) and adding the correct points of the matrix.
Partners; Iakella2 and Ahchin2
*/


sp_tuples * load_tuples(char* input_file)
{
    int row, col;
  sp_tuples * pointer = (sp_tuples*)malloc(sizeof(sp_tuples)); // New variable of type sp_tuples
  FILE  * bruh = fopen(input_file, "r"); // Opening file to read
  
  fscanf(bruh, "%d %d\n", &row, &col); // Getting dimensions of the matrix
  
  pointer->m =row ;  // Initializing variable 'pointer'
  pointer->n =col ;
  pointer->nz =0 ; // Reads the file line by line and calls set_tuples to create linked list
  pointer->tuples_head = NULL;
    int i,j;
    double k;
    while(feof(bruh) == 0){
       fscanf(bruh, "%d %d %lf", &i,&j,&k); // Gets a non zero value
       set_tuples(pointer, i, j, k);   // Calls set tuples with this value
    }
  
  fclose(bruh);   // Close file and return
  return pointer;
  
}



double gv_tuples(sp_tuples * mat_t,int row,int col) {
  sp_tuples_node * newNode = mat_t -> tuples_head;    // Create new node and set it equal to current node
  while(newNode != NULL) {      // Check that next node exists
    if(newNode -> row == row && newNode -> col == col) {    // If node exists, return the value at that node
      double val = newNode -> value;
      return val;
    }
    newNode = newNode -> next;    // If node does not exist, current node gets set to next node and loop runs until value is found
    }
  return 0;   // If value not found, return 0
}




//set_tuples sets the element at row and col to value. This function will need to do several things:

void set_tuples(sp_tuples * mat_t, int row, int col, double value){

    
if(mat_t->tuples_head == NULL){  //if the head is null that means there are no elements in this list and we need to add one
    if(value != 0){
    sp_tuples_node * newNode =(sp_tuples_node*)malloc(sizeof(sp_tuples_node));
    newNode -> row = row;
    newNode -> col = col;
    newNode -> value = value;
    newNode -> next = NULL;
    mat_t->tuples_head = newNode;
    mat_t->nz++;
    }
    return;
}

if((gv_tuples(mat_t, row, col) ==0)){  //if there is nothing at that row and column
    if(value == 0)
        return;
}
else{   //if this value is not 0 then it exists within our list and we need to check if we need to delete it or update it
        if(value == 0){ //we need to delete the node at row,col
            sp_tuples_node* last = NULL ;
            sp_tuples_node* current = mat_t->tuples_head ; //current holds the head node
            while(current != NULL){
                if((current ->col == col && current ->row == row)){
                    if(last == NULL){
                        mat_t->tuples_head = current ->next;  //new head node delete the old one
                    }
                    else{ //this is the case that it is not the head pointer
                        last -> next = current ->next ;
                    }
                    mat_t -> nz -- ;
                    free(current);
                    return;
                }
                last = current ;
                current = current ->next ;
            } //closes the while loop
        } //closes the if value == 0 statment
        else{  //if your  value is not equal to 0 and it exists
            sp_tuples_node* current = mat_t->tuples_head ; //current holds the head node
            
            while(current != NULL){
                if((current ->col == col && current ->row == row)){
                    current ->value = value ;  //replace the value
                    return;
                }
                current = current ->next ;
            }
                        
        }
    }//closes the else statment

    if((gv_tuples(mat_t, row, col) ==0)){ //There is no value at that row and  column and the value does NOT equal 0 we need to add it
        sp_tuples_node* last = NULL ;
        sp_tuples_node* current = mat_t->tuples_head ;
        sp_tuples_node* new = (sp_tuples_node*)malloc(sizeof(sp_tuples_node));
        new -> col = col  ;
        new -> row = row   ;
        new -> value = value   ;
        mat_t ->nz ++ ;
        int nodeCompare ;
        while(current != NULL){
            if(current ->row != row)
            nodeCompare = (current ->row > row);
            else
                nodeCompare = (current ->col > col);
            
            if(nodeCompare){
                    if(last == NULL){
                        new -> next = current ;
                        mat_t -> tuples_head = new ;
                        }
                        else{
                            last -> next = new ;
                            new ->next = current ;
                        }
                    return ; //it has been added
            
            }
            last = current ;
            current = current ->next ;
        }
        // code for if its an empty list goes here
        last ->next = new ;
        new -> next = NULL ;
        return ;
    }
    return;
} //ends the function

    

    
void save_tuples(char * file_name, sp_tuples * mat_t)
{
if(mat_t == NULL) {
     return;
  }
    FILE * name = fopen(file_name, "w");                                     // Creating new file to write in called 'name'
  fprintf(name,"%d %d\n", mat_t->m, mat_t->n);                                     // Printing row and column as the top line
  sp_tuples_node * current = mat_t -> tuples_head;                                 // New variable set equal to head node to maintain head node
  while(current!= NULL) {
    fprintf(name, "%d %d %f\n", current->row, current-> col, current->value);                     // Printing matrix line by line and updating 'current' node
    current= current->next;
  }
  fclose(name);
  return;
}


sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB)
{
  if(matA->m != matB->m || matA->n != matB->n) {
    return NULL;
  }
  sp_tuples *matC=(sp_tuples*)malloc(sizeof(sp_tuples));                // Creating new matrix C and initializing it to same dimensions as A and B
  matC->m = matA->m;
  matC->n = matA->n;
  matC->nz = 0;
  matC->tuples_head = NULL;
  sp_tuples_node *B = matB->tuples_head;                            // Creating easily called variables equal to the head nodes of each matrix
  sp_tuples_node *A = matA->tuples_head;
  
  while( A!=NULL) {                                                      // Sum at this point will be value of C + value of A
    set_tuples(matC, A->row, A->col, A->value);                        // Calling set_tuples to place new node
    A = A -> next;                                                                // Updating the node in matrix A being added
  }
  while(B!=NULL) {
    double val1 = gv_tuples(matC, B->row, B->col);
    set_tuples(matC, B->row, B->col, val1 + B->value);                    // Calling set_tuples to place new node which contains value of C+A+B
    B = B->next;                                                                    // Updating the node in matrix B being added
  }
    return matC;
}


void destroy_tuples(sp_tuples * mat_t) {
  if(mat_t == NULL) {
     return;
  }                              
  sp_tuples_node * destroy = mat_t -> tuples_head; 
  sp_tuples_node * temp = NULL;
  while(destroy != NULL) {                                // While current node exists, free node and check next node in the list
    temp = destroy;
    destroy = destroy -> next;
    free(temp);
  }
    free(mat_t);                                         // Free entire matrix
}


sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ /* THIS IS OPTIONAL */
	return NULL;
}
