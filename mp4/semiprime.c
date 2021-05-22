/* partners: ahchin2, iakella2
 In total, four changes were made to the semiprime.c file. First, in is_prime (), the return values were initially switched to return zero if the number was prime
 and one if it was not, so to fix this, the return values were simply swapped. Next, in print_semiprimes (), in the second if statement, the 'k = i%j' was switched
 to 'k = i/j' because otherwise, it was discovered that if i%j was equal to zero and j was a prime number, the value of i would print regardless of whether or not 
 it was a product of two prime numbers. This was because in order for the first for loop to be true, i%j must be zero, then, if j was a prime number, k was set 
 equal to i%j which was zero, causing the last if statement to be true and print i regardless of if the other multiple was also a prime number. The next change was
 adding a 'break' statement in an if statement in order to ensure that a semiprime number would not print multiple times. The 'break' statement ensured that after
 a semiprime number was printed, the code would exit and return back to the first loop so that the same i value would not continue to be tested. The final change
 was setting ret equal to one after anything was printed because otherwise, at the end of the program whenret is returned, a zero would have been returned even if 
 a semiprime was printed. */


#include <stdlib.h>
#include <stdio.h>

/*
 * is_prime: determines whether the provided number is prime or not
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
    int i;
    if (number == 1) {return 0;}
    for (i = 2; i < number; i++) { //for each number smaller than it
        if (number % i == 0) { //check if the remainder is 0
            return 0;
        }

    }
    return 1;
}


/*
 * print_semiprimes: prints all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
    int i, j, k;
    int ret = 0;
    for (i = a; i <=b; i++) { //for each item in interval
        //check if semiprime
        for (j =2 ; j < i; j++) {
            if (i%j == 0) {
                if (is_prime(j)) {
                    k = i/j;
                    if (is_prime(k)) {
                        printf("%d ", i);
			ret = 1;
			break;
                    }
                }
            }
		
        }
 
    }
    printf("\n");
    return ret;

}
