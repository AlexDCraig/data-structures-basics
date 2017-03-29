/* 
 * Solution description: exemplify differences between pass by pointer and pass by reference
 * z's copy is modified in foo but this does not impact z itself
 */
 
#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c)
{
	*a = *a * 2;
	*b = *b / 2;
	c = *a + *b;
	return c;  
}

int main()
{
 	int x, y, z;
	x = 7;
	y = 8;
	z = 9;
	
	printf("\nx: %d y: %d z: %d", x, y, z);
	printf("\nReturn value: %d", foo(&x, &y, z));

	printf("\nx: %d y: %d z: %d \n", x, y, z);	

    	return 0;
}
    
/* Yes, the return value is different than the value of z. x and y are passed by pointer
 * so foo is allowed to access the original contents of x and y. meanwhile z is passed
 * by value and therefore a copy of z is used to perform the return calculations. z's 
 * original data is not impacted by these calculations.*/    
