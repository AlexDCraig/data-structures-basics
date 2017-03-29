#include "cirListDeque.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int isNumber(char *s, double *num) // check for 0, pi, e, and basic numbers. Return 1 if number and store number in double.
{
	char *end;
	double returnNum;

	if(strcmp(s, "0") == 0)
	{
		*num = 0;
		return 1;
	}

	if(strcmp(s, "pi") == 0)
	{
		*num = 3.14159;
		return 1;
	}

	else if (strcmp(s, "e") == 0)
	{
		*num = 2.71828;
		return 1;
	}

	else 
	{
		returnNum = strtod(s, &end);
		 //If there's anythin in end, it's bad 
		if((returnNum != 0.0) && (strcmp(end, "") == 0))
		{
			*num = returnNum;
			return 1;
		}

	}
		return 0;  //if got here, it was not a number
}

double* converter(int argc, char* argv[])
{
	int j;
	double* myArr = malloc(argc * sizeof(double));

	for (j = 1; j < argc; j++)
	{
		double* temp = malloc(sizeof(double));
		
		if (strcmp(argv[j], " ") != 0)
		{
			if (isNumber(argv[j], temp) != 0)
				myArr[j] = *temp;			 
		}
	}

	return myArr;
}

int main(int argc, char* argv[])
{
	double* myArr = converter(argc, argv);

	int j;

	printf("\nYOU ENTERED: ");

	for (j = 1; j < argc; j++)
	{
		printf("\n %f", myArr[j]);
	}

	struct cirListDeque* myList = createCirListDeque();

	printf("\n");

	// Test addFront.
	printf("\nTEST ADDFRONT: Adding first four values you entered to the front.");
	addFrontCirListDeque(myList, myArr[1]);
	addFrontCirListDeque(myList, myArr[2]);
	addFrontCirListDeque(myList, myArr[3]);
	addFrontCirListDeque(myList, myArr[4]);
	
	printf("\n");
	// Test addBack.
	printf("\nTEST ADDBACK: Adding the last four values you entered to the back."); 
	addBackCirListDeque(myList, myArr[5]);
	addBackCirListDeque(myList, myArr[6]);
	addBackCirListDeque(myList, myArr[7]);
	addBackCirListDeque(myList, myArr[8]);

	printf("\n");
	printf("\nTEST PRINTLIST: ");
	printCirListDeque(myList);


	printf("\n");
	// Test frontDeque, backdeque
	printf("\nTEST FRONTDEQUE: The value revealed should be %f", myArr[4]);
	printf("\n %f", frontCirListDeque(myList));

	printf("\n");
	printf("\nTEST BACKDEQUE: The value should be %f", myArr[8]);
	printf("\n %f", backCirListDeque(myList));

	// Test removal of front, back.
	printf("\n");
	printf("\nTEST REMOVEFRONT: After removing, peeking at the front should reveal \n the value %f", myArr[3]);
	removeFrontCirListDeque(myList);
	printf("\n %f", frontCirListDeque(myList));

	printf("\n");
	printf("\nTEST REMOVEBACK: After removing, peeking at the back should reveal \n the value %f", myArr[7]);
	removeBackCirListDeque(myList);
	printf("\n %f", backCirListDeque(myList));

	
	printf("\n");
	printf("\nFORWARDS: ");
	printCirListDeque(myList);
	// test reverse, reverse then print
	printf("\n");
	printf("\nIN REVERSE: ");
	reverseCirListDeque(myList);
	printCirListDeque(myList);

	deleteCirListDeque(myList);
	
	printf("\n");
	printf("\nTEST DELETELIST/FREELIST AND ISEMPTY: If the list is deallocated, the isEmpty function will return 1: ");
	printf("\n %d",isEmptyCirListDeque(myList));

	printf("\n");
	return 0;
}


