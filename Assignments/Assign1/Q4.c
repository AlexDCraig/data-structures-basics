/* CS261- Assignment 1 - Q.4*/
/* Name: Alex Hoffer
 * Date: 1/7/2016
 * Solution description: Uses the bubble sort from Q3 to sort students based on their
 * score [ascending]. Considers the ID when swapping.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct student
{
	int id;
	int score;
};

void sort(struct student* students, int n)
{
	int k;
	int j;

	for (k = n - 1; k > 0; k--)
	{
		for (j = 0; j < k; j++)	
		{
			if (students[j].score > students[j + 1].score)
			{
				int scoreTemp = students[j].score;
				int idTemp = students[j].id;
				students[j].score = students[j + 1].score;
				students[j].id = students[j + 1].id;
				students[j + 1].score = scoreTemp;
				students[j + 1].id = idTemp;
			}
		}
	}

}

int main()
{
	srand(time(0));

	int n = 10;
	struct student* students = malloc(n * sizeof(struct student));
		
	int i;

	for (i = 0; i < 10; i++)
	{
		int myID = rand() % 10 + 1;
		int myScore = rand() % 101;
		students[i].id = myID;
		students[i].score = myScore;
	}

	printf("\nThe contents of the array are as follows: ");

	for (i = 0; i < 10; i++)
	{
		printf("\nID: %d ", students[i].id);
		printf("SCORE: %d ", students[i].score);
	}

	sort(students, n);

	printf("\n\nThe contents of the sorted array are as follows: ");

	for (i = 0; i < 10; i++)
	{
		printf("\nID: %d ", students[i].id);
		printf("SCORE: %d ", students[i].score);
	}

	printf("\n");
				
	return 0;
}
