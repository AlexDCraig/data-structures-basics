/* CS261- Assignment 1 - Q.1*/
/* Name: Alex Hoffer
 * Date: 1/7/2016
 * Solution description: Create a struct which serves as a class of ten students' identifications and scores. Randomly assign scores and IDs within intervals to these students. Print out the results.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct student
{
	int id;
	int score;
};

struct student* allocate()
{
	struct student* myRoster = malloc(10 * sizeof(struct student));
	return myRoster;	
}

int checkForUnique(struct student*, int, int, int);

void generate(struct student* students)
{
 	int i;
	int idSize = 0;
	int scoreSize = 0;

	for (i = 0; i < 10; i++)
	{
		int myUniqueID = rand() % 10 + 1;
		int myUniqueScore = rand() % 101;

		while (checkForUnique(students, myUniqueScore, 0, scoreSize) == 0)
		{
			myUniqueScore = rand() % 101;
		}

		students[i].score = myUniqueScore;
		scoreSize++;

		while (checkForUnique(students, myUniqueID, 1, idSize) == 0)
		{
			myUniqueID = rand() % 10 + 1;
		}

		students[i].id = myUniqueID;
		idSize++;
	}	
}

int checkForUnique(struct student* students, int checkValue, int whichCheck, int size)
{
	// If whichCheck is 0, this function will check the scores 
	// for uniqueness. If it is 1, it will check the ids.
	
	int i;

	if (whichCheck == 0)
	{
		for (i = 0; i < size; i++)
		{
			if (students[i].score == checkValue)
				return 0; // returns false. the value is not unique
		}	

		return 1;		
	}

	else
	{
		for (i = 0; i < size; i++)
		{
			if (students[i].id == checkValue)
				return 0;
		}

		return 1;
	}

}

void output(struct student* students)
{
	int i;
	
	for (i = 0; i < 10; i++)
	{
		int currentID = students[i].id;
		int currentScore = students[i].score;
		printf("\nThe student with the ID %d has the score %d.", currentID, currentScore);
	}
}

void summary(struct student* students)
{
	double avg = 0;
	int lowScore = 101;
	int highScore = -1;

	int i;

	for (i = 0; i < 10; i++)
	{
		int currentScore = students[i].score;
		avg += currentScore;
		
		if (currentScore < lowScore)
			lowScore = currentScore;

		else if (currentScore > highScore)
			highScore = currentScore;
	}

	avg = avg / 10;

	printf("\nThe average score of the ten students is: %f", avg);
	printf("\nThe low score of the ten students is: %d", lowScore);
	printf("\nThe high score of the ten students is: %d", highScore);
	printf("\n");
}

void deallocate(struct student* stud)
{
	if (stud != NULL)
 		free(stud);
}

int main()
{
    	srand(time(0));
    	struct student* stud = NULL;

    	stud = allocate();
    	generate(stud);
	output(stud);
	summary(stud);
	deallocate(stud);
	   
  
    	return 0;
}
