/* CS261- Assignment 1 - Q.5*/
/* Name: Alex Hoffer
 * Date: 1/7/2016
 * Solution description: Calculates the size of the c string, then proceeds to upper case
 * each 0 or even number and lowercase all else, provided the numbers aren't already in that format
 */
 
#include <stdio.h>
#include <stdlib.h>

/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch){
     return ch-'a'+'A';
}

/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch){
     return ch-'A'+'a';
}

void studly(char* word)
{
	int size = 1; // Size includes null terminator.
	int i;

	for (i = 0; i < 100 && word[i] != '\0'; ++i)
		size++;

	for (i = 0; i < size; i++)
	{
		char temp = word[i];

		// If this number is at element 0 or an even element and it isn't already uppercase
		if (i == 0 || i % 2 == 0)
		{
			if (temp < 65 || temp > 90) // checks the ASCII interval that corresponds to
			// the upper case set of letters
			word[i] = toUpperCase(temp);
		}

		// If this is number is at an odd element and it isn't already lowercase
		else
		{
			if (temp >= 65 && temp <= 90) // consult ASCII
			word[i] = toLowerCase(temp); 
		}
	}

	printf("Converted to studly caps, here's what it looks like:\n");
	for (i = 0; i < size - 1; i++)
	{
		printf("%c", word[i]);
	}

}

int main(){
	
	char myString[100];	

	printf("Please enter the word to be converted to studly caps.\n");
	
   	scanf("%s", myString);

	studly(myString);	

	printf("\n");	

	return 0;
}
