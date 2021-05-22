/* Partners: iakella2 ahchin2
MP3 requires the user to give an input and outputs the corresponding integers from that line of Pascal's Triangle. T
he code begins by asking the user for an input which is then stored into the integer “row”. Then the program assigns 3 variables: k, i, and c. 
The outermost loop is in terms of k and continues to loop until k is greater than the row value. Inside of that loop is the “i” loop which performs 
the equation for a certain “i” and “k” value. Even though “i” is set to 1 in the equation, we have “i” start at zero to account for the case when k=0 otherwise 
the for loop condition would already be true. This is how we are able to print out the ones at the start of the row (using if else statement).
We set c=1 earlier because we want the first calculated c value of the loop to be the given equation. 
After the inner loop is run the value of c is updated and printed and the outer loop is incremented to the next coefficient. 
The program continues to run until all values of the row have been printed. */



#include <stdio.h>
#include <stdlib.h>
int main()
{
  int row;

  printf("Enter a row index: ");
  scanf("%d",&row);

  // Write your code here
  int k; //Equivalent to k in the equation
  int i; //Equivalent to i in the equation
  unsigned long c =1; // coefficient of the binomial set to one for the equation

  for(k=0; k<=row; k++){   //primary loop to move through each term in the row
for(i=0; i<=k; i++){ //nested loop to match the product equation, i starts at one to check if k=0
 	if(i==0 || k==0){ //checking if k=0 if so c=1 if not use equation 
    	c=1; }
 	else{
    	c=c*(row+1-i)/i; } //the products of the current term’s equation and the prior
}
printf("%lu", c); // after finishing with an instance of nested loop print c
printf(" "); // space for the next line
}
printf("\n"); // new line 
  return 0;
}

