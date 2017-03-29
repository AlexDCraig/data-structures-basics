/* CS261- Assignment 1 - Q. 0*/
/* Name: Alex Hoffer
 * Date: 1/7/2016
 * Solution description: Demonstrate the relationship between a variable, a pointer pointing to that variable, and their addresses.
 */
 
#include <stdio.h>
#include <stdlib.h>

/* Function: fooA
 * Input: pointer to an integer
 * Output: Nothing
 * Preconditions: iptr must point to an integer data type
 * Postconditions: none
 */
void fooA(int* iptr)
{
	printf("\nValue of integer pointed to by iptr: %d", *iptr);
	printf("\nAddress pointed to by iptr: %p", &(*iptr));
	printf("\nAddress occupied by iptr itself: %p", &iptr);
}

int main()
{
	int x;
	printf("\nAddress of x: %p", &x);
	fooA(&x);
	printf("\nValue of x: %d \n", x);
	return 0;
}
