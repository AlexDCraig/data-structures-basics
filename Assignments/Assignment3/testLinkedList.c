#include "linkedList.h"
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

	printf("\n");

	struct linkedList* myList = createLinkedList();

	printf("\nTEST ADDFRONTLIST: Adding the values %f %f %f %f", myArr[1], myArr[2], myArr[3], myArr[4]);
	printf(" to the front of the list in the order they were entered.");

	printf("\n");

	addFrontList(myList, myArr[1]);
	addFrontList(myList, myArr[2]);
	addFrontList(myList, myArr[3]);
	addFrontList(myList, myArr[4]);

	printList(myList);

	printf("\n");
	printf("\nTEST ADDBACKLIST: Adding the values %f %f %f %f", myArr[5], myArr[6], myArr[7], myArr[8]);
	printf(" to the front of the list in the order they were entered.");

	printf("\n");

	addBackList(myList, myArr[5]);
	addBackList(myList, myArr[6]);
	addBackList(myList, myArr[7]);
	addBackList(myList, myArr[8]);

	printList(myList);

	printf("\n");
	printf("\n TEST FRONTLIST: The value returned by frontList should be %f", myArr[4]);
	printf("\nRETURNED VALUE: %d", frontList(myList));


	printf("\n\n TEST BACKLIST: The value returned by backList should be %f", myArr[8]);
	printf("\nRETURNED VALUE: %d", backList(myList));

	printf("\n\n TEST REMOVEFRONT: (compare to original printed list)");
	removeFrontList(myList);
	printList(myList);

	printf("\n\n TEST REMOVEBACK: (compare to the last list)");
	removeBackList(myList);
	printList(myList);

	printf("\n\n TEST CONTAINS: The value at element 3, %f, should still exist. The function will return 1 if this value is indeed there.", myArr[3]);
	printf("\n %d", containsList(myList, myArr[3]));

	printf("\n\n TEST ADDLIST: Adding the value 20 to the list, treating it like a stack.");
	addList(myList, 20);

	printList(myList);

	printf("\n\n TEST REMOVELIST: Let's remove array element 3 which we mentioned earlier. That value is: %f", myArr[3]);

	removeList(myList, myArr[3]);

	printList(myList);

	printf("\n\nTEST ISEMPTY AND DELETELINKEDLIST: I'm going to delete the list and demonstrate its deletion by testing it using isEmpty. The value returned by this function should be 1.");

	deleteLinkedList(myList);

	printf("\n %d", isEmptyList(myList));

	printf("\n");
	return 0;
}
