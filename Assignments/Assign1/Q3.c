/* CS261- Assignment 1 - Q.3*/
/* Name: Alex Hoffer
 * Date: 1/7/2016
 * Solution description: Given an array of integers and its size, this file uses a bubble
 * sort to arrange the array in ascending order.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void sort(int* number, int n)
{
	int k;
	int j;

	for (k = n - 1; k > 0; k--)
	{
		for (j = 0; j < k; j++)	
		{
			if (number[j] > number[j + 1])
			{
				int temp = number[j];
				number[j] = number[j + 1];
				number[j + 1] = temp;
			}
		}
	}
}

int main()
{
	srand(time(0));

	int n = 20;
	int* myArray = malloc(n * sizeof(int));
		
	int i;

	for (i = 0; i < 20; i++)
	{
		int myRandNum = rand() % 21;
		myArray[i] = myRandNum;
	}

	printf("\nThe contents of the array are as follows: ");

	for (i = 0; i < 20; i++)
		printf("\n %d ", myArray[i]);

	sort(myArray, n);

	printf("\nThe contents of the sorted array are as follows: ");

	for (i = 0; i < 20; i++)
		printf("\n %d ", myArray[i]);			
	
	printf("\n");

   	return 0;
}
