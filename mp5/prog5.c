 /*
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/* The MP asks us to code functions used within function main.c. This MP can be simplified into three functions: set_seed, start_game, and make_guess. The set_seed function 
initializes the "random" number generator with srand by asking for a seed umber (integer). Function start_game sets up the solutions for which we want to find. 
We use modulus 8 on some "random" variables because we do not want a number greater than the size of the array pool. The random variables then decide what value from the pool
array it will take from and put it into the solutions array. The solutions array is a 2d array where the row number is the start of a new word and columns representing each
letter. We can now move on to make_guess which checks whether the inputted solution is correct and gives us the score. The algorithm is made up of multiple for and if statements. 
The for statements allow us to iteratively check if all the words match while the if statement checks if the row array value of solution is the same as the guess array's.
If two values of same index are the same the first time, we set two arrays to 1 and skip the comparison of mismatches using continue and increment perfmatch by 1. 
If we have 4 perfmatches we are done. Finally we check for mismatches by using loops to compare every array index value with another. Then to compute score the we use an
equation which is the sum of the mismatch and perfect score. The mismatch score is the # of mismatches times 100 and # of perfmatches times 1000. To keep max score, 
we use an inequality to check past scores with current. After the calculation the values are printed out. This process repeats until perfmatch is 4. 
partners: iakella2 ahchin2
*/



#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"

int guess_number;                                               
int max_score;                                                                                 // Creates integers max_score, guess_number and 2D array solutions      
char solutions[4][10];
char* pool[] = {"Vader", "Padme", "R2-D2", "C-3PO", "Jabba", "Dooku", "Lando", "Snoke",};      // Initializes pool array to accepatable guesses
/* Show guessing pool -- This function prints "pool" to stdout
 * INPUT: none
 * OUTPUT: none
 */
void print_pool() {
    printf("Valid term to guess:\n\t");                                                        // Prints to screen
    for(int i = 0; i < 8 ; ++i) {
        printf("%s ", pool[i]);                                                                // Loops 8 times to print all pool[i], aka the valid guesses 
    }
    printf("\n");
}

/*
 * is_valid -- This function checks whether a string is valid
 * INPUTS: str -- a string to be checked
 * OUTPUTS: none
 * RETURN VALUE: 0 if str is invalid, or 1 if str is valid
 * SIDE EFFECTS: none
 */
int is_valid(char* str) {
    int i = 0;
    if (str == NULL) {                                                                         // If string is null, return 0
        return 0;
    }
    for (i = 0; i < 8; i++) {
        if (strcmp(str, pool[i]) == 0) {                                                       // Loops through to make sure guess is valid
            return 1;                                                                          // If so, returns 1
        }
    }
    return 0;                                                                                  // Return 0 
}


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid.
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int set_seed (const char seed_str[]) {
//    Example of how to use sscanf to read a single integer and check for anything other than the integer
//    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
//    The user should enter only an integer, and nothing else, so we will check that only "seed" is read.
//    We declare
//    int seed;
//    char post[2];
//    The sscanf statement below reads the integer into seed.
//    sscanf (seed_str, "%d%1s", &seed, post)
//    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
//    The return value of sscanf indicates the number of items read succesfully.
//    When the user has typed in only an integer, only 1 item should be read sucessfully.
//    Check that the return value is 1 to ensure the user enters only an integer.
//    Feel free to uncomment these statements, modify them, or delete these comments as necessary.
//    You may need to change the return statement below
    int seed;       
    char post[2];                                        // Creates post array         
    if (sscanf (seed_str, "%d%1s", &seed, post) != 1) {     // Checks if input is an integer
      printf("set_seed: invalid seed\n");									// Invalid Input
      return 0;
    }
  else
      srand(seed);																			//Initializes Random Number Generating (sets the seed used to rand)
    return 1;
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above.
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 *               The score should be initialized to -1.
 * INPUTS: none
 * OUTPUTS: none
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void start_game () {
    
    max_score = -1;					                               // Initializing max_score to -1
    guess_number = 1;				                             	// Initiallizing guess_number to 1
      
    int solution0= rand() % 8;				                     // The next four lines generate random solutions and store them 
    int solution1= rand() % 8;
    int solution2= rand() % 8;
    int solution3= rand() % 8;
      
    
    
    strcpy( solutions[0], pool[solution0] )   ;        // The next four lines copy the generated string into the pool solutions     
    strcpy( solutions[1], pool[solution1] )   ;
    strcpy( solutions[2], pool[solution2] )   ;
    strcpy( solutions[3], pool[solution3] )   ;
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str.
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 strings from pool). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: none
 * RETURN VALUE: 2 if guess string is valid and got all 4 perfect matches, or 1 if the guess string is valid,
 *               or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess)
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int make_guess (const char guess_str[]) {
    int ret = 0;				 			  				                         							                                  // Initializing the return value to 0
    char garbage [2];			  				                                                                  // Creating garbage array 
    char guess[4][10];                                 			  				                                // Creating guess 2D array
    int sol[4] = {0,0,0,0};                            			  				                                // Creating and initializing sol array to all zeros
    int gus[4] = {0,0,0,0};   				                     			  				                                // Creating and initializing gus array to all zeros
    int perfmatch = 0;  				                           			  				                                // Initializing perfmatch number to 0
    int mismatch = 0;				                              			  				                                // Initializing mismatch number to 0 

 if(sscanf(guess_str, "%s%s%s%s%1s", guess[0],guess[1], guess[2], guess[3], garbage) == 4) {    // Checks to make sure only four words were inputted

     for(int start = 0; start<4;start++)          				                            				          // Checks to see if all four words are valid by calling is_valid
     {
         if(is_valid(guess[start]) == 0){                                                       // If statement for if it is not valid
            
             printf("make guess: invalid guess\n");                                             // If so, it will print the invalid string, set ret equal to 
             ret = 0;                                                                           // zero, and return 0
             return 0;
         }
             ret = 1;       				                            				                                // If it is valid, it will set ret equal to 1
     
     }
     guess_number = guess_number + 1 ;				                            				                      // Increments the guess_number
     for(int i =  0; i < 4; i++) {                               				                           // Loops three times
         if (strcmp(guess[i], solutions[i]) == 0)                                               // Checks if the guess word is equal to the solution of same index
             {
                 perfmatch = perfmatch + 1;                                                     // If a match, increment perfmatch number
                 sol[i] = 1;                                                                    // Marks sol[i] as matched
                 gus[i] = 1;                                                                    // Marks gus[i] as matched 
         }
     }
     
     for(int j = 0; j<4;j++){                                                                   // The next two lines create a nested for loop to check for the 
         for(int k=0; k<4; k++){                                                                // mismatched guesses 
             if(sol[k] == 1 || gus[j] == 1){                                                    // If either sol[k] or gus[j] is set as matched, continue 
                 continue;                                                                      // to the next iteration
             }
             if(strcmp(guess[j], solutions[k]) == 0){                                          // If guess[j] has the same string as solutions[k]
                 gus[j] =1 ;                                                                   // Mark gus[j] as matched
                 sol[k] =1 ;                                                                   // Matk sol[k] as matched
                 mismatch = mismatch + 1;                                                      // Increment mismatch count
             }
         }
     }
     if(perfmatch == 4){                                                                       // Sets ret equal to 2 if all words in the guess are matches
         ret = 2;
         
     }
 
 }
 else{
     printf("make guess: invalid guess\n");                                                   // If invalid, print invalid string and return 0
     return 0;
 }

       int matchscore = 1000 * perfmatch;          			  				                         			  			// The next segment of lines calculates the final score by 
       int mismatchscore = 100 * mismatch;			  				                                          // multiplying the number of perfmatches by 1000 and adding
       int finscore = matchscore + mismatchscore; 			  				                                  // it to the number of mismatches * 100 and storing in finscore
       if (finscore > max_score)			  				                         			  				                  // Checks if finscore is greater than the max score
     {
       max_score = finscore;                           			  				                             // If so, update max_score
     }
    printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n" , guess_number - 1, perfmatch, mismatch);  // Prints number of mismatches, 
    printf("Your score is %d and cur max score is %d.\n", finscore, max_score);           			  				                           // perfect matches, and max_score
    if(ret == 2){
        guess_number = guess_number-1;                                                       // Decrements guess_number so right final guess_number is displayed
    }
     return ret;           
 
}
