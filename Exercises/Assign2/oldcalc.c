#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "dynamicArray.h"


/* param: s the string
   param: num a pointer to double
   returns: true (1) if s is a number else 0 or false.
   postcondition: if it is a number, num will hold
   the value of the number
*/
int isNumber(char *s, double *num) // check for 0, pi, e, and basic numbers. Return 1 if number and store number in double.
{
	char *end;
	double returnNum;

	if(strcmp(s, "0") == 0)
	{
		*num = 0;
		return 1;
	}

	else if(strcmp(s, "pi") == 0)
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
		if ((strcmp(s, "+") != 0) && (strcmp(s, "^2")) && (strcmp(s, "^3")) && (strcmp(s, "-") != 0) && (strcmp(s, "/") != 0) && (strcmp(s, "x") != 0) && (strcmp(s, "^") != 0) && (strcmp(s, "abs") != 0) && (strcmp(s, "sqrt") != 0) && (strcmp(s, "exp") != 0) && (strcmp(s, "ln") != 0) && (strcmp(s, "log") != 0) && (isdigit(*s) == 0))
		{
			printf("\nERROR: You have entered a string of characters not recognized in this program.");
			exit(1);
		}

		returnNum = strtod(s, &end);
		/* If there's anythin in end, it's bad */
		if((returnNum != 0.0) && (strcmp(end, "") == 0))
		{
			*num = returnNum;
			return 1;
		}

	}
	return 0;  //if got here, it was not a number
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and 
	their sum is pushed back onto the stack.
*/
void add (struct DynArr *stack)
{
	double firstNum = topDynArr(stack);
	popDynArr(stack);

	double secondNum = topDynArr(stack);
	popDynArr(stack);

	if (isEmptyDynArr(stack) == 0) // the stack is not empty
	{
		printf("ERROR: Too many operands."); 
		exit(1);
	}

	pushDynArr(stack, firstNum + secondNum); // Top of the stack is now the sum. 	
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and 
	their difference is pushed back onto the stack.
*/
void subtract(struct DynArr *stack)
{
	double secondNum = topDynArr(stack);
	popDynArr(stack);

	double firstNum = topDynArr(stack);
	popDynArr(stack);

	if (isEmptyDynArr(stack) == 0)
	{
		printf("ERROR: Too many operands.");
		exit(1);
	}

	pushDynArr(stack, firstNum - secondNum);
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and 
	their quotient is pushed back onto the stack.
*/
void divide(struct DynArr *stack)
{
	double denominator = topDynArr(stack);
	popDynArr(stack);

	double numerator = topDynArr(stack);
	popDynArr(stack);

	if (isEmptyDynArr(stack) == 0)
	{
		printf("\nERROR: Too many operands.");
		exit(1);
	}

	pushDynArr(stack, numerator / denominator);
}

void multiply(struct DynArr *stack)
{
	double secondNum = topDynArr(stack);
	popDynArr(stack);

	double firstNum = topDynArr(stack);
	popDynArr(stack);

	if (isEmptyDynArr(stack) == 0)
	{
		printf("\nERROR: Too many operands.");
		exit(1);
	}

	pushDynArr(stack, (firstNum * secondNum));
}

void square(struct DynArr* stack)
{
	double squared = topDynArr(stack);
	popDynArr(stack);

	double numToSquare = topDynArr(stack);
	popDynArr(stack);

	if (isEmptyDynArr(stack) == 0)
	{
		printf("\nERROR: Too many operands.");
		exit(1);
	}

	pushDynArr(stack, (pow(numToSquare, squared)));
}
	 

void power(struct DynArr *stack)
{
	double exponent = topDynArr(stack);
	popDynArr(stack);

	double numToExp = topDynArr(stack);
	popDynArr(stack);	

	if (isEmptyDynArr(stack) == 0)
	{
		printf("\nERROR: Too many operands.");
		exit(1);
	}

	pushDynArr(stack, (pow(numToExp, exponent)));
}

void cube(struct DynArr *stack)
{
	double cubed = topDynArr(stack);
	popDynArr(stack);

	double numToCube = topDynArr(stack);
	popDynArr(stack);

	if (isEmptyDynArr(stack) == 0)
	{
		printf("\nERROR: Too many operands.");
		exit(1);
	}

	pushDynArr(stack, (pow(numToCube, cubed))); 
}

void absol(struct DynArr* stack)
{
	
	double numToAbs = topDynArr(stack);
	popDynArr(stack);

	if (isEmptyDynArr(stack) == 0)
	{
		printf("\nERROR: Too many operands");
		exit(1);
	}	

	double result = 0;

	if (numToAbs < 0)
		result = numToAbs * -1;

	else
		result = numToAbs;

	pushDynArr(stack, result);
}

void squrt(struct DynArr* stack)
{
	double numToSqrt = topDynArr(stack);
	popDynArr(stack);

	if (isEmptyDynArr(stack) == 0)
	{
		printf("\nERROR: Too many numbers.");
		exit(1);
	}	

	double result = sqrt(numToSqrt);

	pushDynArr(stack, result);

}

void expon(struct DynArr* stack)
{
	double numToExp = topDynArr(stack);
	popDynArr(stack);

	if (isEmptyDynArr(stack) == 0)
	{
		printf("\nERROR: Too many numbers.");
		exit(1);
	}	

	double result = exp(numToExp);

	pushDynArr(stack, result);
}

void ln(struct DynArr* stack)
{
	double numToLn = topDynArr(stack);
	popDynArr(stack);

	if (isEmptyDynArr(stack) == 0)
	{
		printf("\nERROR: Too many numbers.");
		exit(1);
	}	

	double result = log(numToLn); // natural log
	
	pushDynArr(stack, result);
}

void logbs(struct DynArr* stack)
{
	double numToLog = topDynArr(stack);
	popDynArr(stack);

	if (isEmptyDynArr(stack) == 0)
	{
		printf("\nERROR: Too many numbers.");
		exit(1);
	}	

	double result = log10(numToLog);

	pushDynArr(stack, result);
}

double calculate(int numInputTokens, char **inputString) // note that this is an array of c strings. The function only enters a computational state if the last item
// is an operator
{
	int i;
	double result = 0.0;
	char* s;
	struct DynArr *stack;

	//set up the stack
	stack = createDynArr(20); 

	// start at 5 to skip the name of the calculator calc
	for(i=1; i < numInputTokens;i++) // PUSH EACH THING ON THE STACK
	{
		s = inputString[i];
		double* temp = malloc(sizeof(double));

		// Hint: General algorithm:
		// (1) Check if the string s is in the list of operators.
		//   (1a) If it is, perform corresponding operations.
		//   (1b) Otherwise, check if s is a number.
		//     (1b - I) If s is not a number, produce an error.
		//     (1b - II) If s is a number, push it onto the stack

		if(strcmp(s, "+") == 0) // if the input is the operator plus
		{
			add(stack);
		}

		else if(strcmp(s,"-") == 0) // if input is operator -
		{
			subtract(stack);
		}		
	
		else if(strcmp(s, "/") == 0) // if input is operator /
		{
			divide(stack);
		}

		else if(strcmp(s, "x") == 0) // if input is operator x
		{
			multiply(stack);

		}

		else if(strcmp(s, "^") == 0)
		{
			if ((i + 1) < numInputTokens)
			{
				if (isNumber(inputString[i + 1], temp) == 1)
				{
					if (*temp == 2)
					{
						pushDynArr(stack, *temp);
						square(stack);
						i += 1;
					}

					else if (*temp == 3)
					{
						pushDynArr(stack, *temp);
						cube(stack);
						i += 1;
					}

					else
					{
						//power(stack);
						printf("\nERROR: That syntax is reserved for cubing or squaring exclusively. To perform your operation you must use the following syntax: 'x y ^'.\n");
						exit(1);
					}
						
				}

				else
				{
					power(stack);
				}
			}
			
			else
			{
				power(stack);	
			}
				
		}

		else if(strcmp(s, "abs") == 0)
		{
			absol(stack);
		}

		else if(strcmp(s, "sqrt") == 0)
		{
			squrt(stack);
		}

		else if(strcmp(s, "exp") == 0)
		{
			expon(stack);
		}

		else if(strcmp(s, "ln") == 0)
		{
			ln(stack);
		}

		else if(strcmp(s, "log") == 0)
		{
			logbs(stack);
		}

		else if (isNumber(s,temp) == 1) // if it's a number, push the number on the stack
		{
			pushDynArr(stack, *temp);
		} 



	}	//end for 

	/* FIXME: You will write this part of the function (2 steps below) 
	 * (1) Check if everything looks OK and produce an error if needed.
	 * (2) Store the final value in result and print it out.
	 */

	result = topDynArr(stack); 
	popDynArr(stack);
	return result;
}

int transfer(int argc, char** argv, char* commands)
{
	// transfer to array of chars
	int i;
	int totalSize = argc + 4; // no empty last element
	int j;

	int numElements = 1; // maybe 2?
	int r = i = 5;
	/* FIND LOOP COUNTER */

	for (i = 5; i <= totalSize; i++)
	{
		if (isalpha(commands[r]))
		{
			while (isalpha(commands[r]))
			{
				r++;
			}

			numElements++;

			if (r == totalSize)
				break;
		}

		else if (isdigit(commands[r]))
		{
			while (isdigit(commands[r]))
			{
				r++;
			}

			numElements++;

			if (r == totalSize)
				break;
		}

		else if (commands[r] == '.')
		{	
			while (commands[r] == '.')
			{
				r++;
				numElements++;
			}

			if (commands[r] == '.' && r == totalSize - 1)
			{
				printf("\nImproper usage of decimal.");
				exit(1);
			}
			
			if (r == totalSize)
				break;
		}

		else if (commands[r] == '+')
		{
			while (commands[r] == '+')
			{
				r++;
				numElements++;
			}
	
			if (r == totalSize)
				break;
		}

		else if (commands[r] == '/')
		{
			while (commands[r] == '/')
			{
				r++;
				numElements++;
			}

			if (r == totalSize)
				break;
		}

		else if (commands[r] == '^')
		{
			while (commands[r] == '^')
			{
				r++;
				numElements++;
			}

			if (r == totalSize)
				break;
		}

		else if (commands[r] == '-')
		{
			while (commands[r] == '-')
			{
				r++;
				numElements++;
			}

			if (r == totalSize)
				break;
		}

		else if (commands[r] == ' ')
		{
			while (commands[r] == ' ')
			r++;

			if (r == totalSize)
				break;
		}

		else
		{
				printf("\nERROR: Invalid operator.");
				exit(1);
		
		}

	}	

	argv[0] = malloc(5 * sizeof(char)); 

	for (j = 0; j < 5; j++)
		argv[0][j] = commands[j];

	if (strcmp(argv[0], "calc ") != 0)
	{
		printf("\nYou failed to write calc before the operations.");
		exit(1);
	}

	j = 5;
	int m = j; // J will traverse but must move backward
	int counter = 0;
	int l = 0;

	for (i = 1; i < numElements; i = i)
	{
		if (isalpha(commands[j]))
		{
			while (isalpha(commands[j]))
			{
				counter++;
				j++;
			}

			argv[i] = malloc(counter * sizeof(char*));

			while (m < j)
			{
				argv[i][l] = commands[m];
				m++;
				l++;
			}

			l = 0;
			m = j + 1;
			i++;
		}	

		else if (isdigit(commands[j]) || commands[j] == '.' || commands[j] == '-' || commands[j] == '^')
		{
			while (isdigit(commands[j]) || commands[j] == '.' || commands[j] == '-' || commands[j] == '^')
			{
				counter++;
				j++;
			}
			
			argv[i] = malloc(counter * sizeof(char*));

			while (m < j)
			{
				argv[i][l] = commands[m];
				m++;
				l++;
			}

			l = 0;
			m = j + 1;
			i++;
		}
	
		else if (commands[j] == '+')
		{
			while (commands[j] == '+')
			{
				counter++;
				j++;
			}

			argv[i] = malloc(counter * sizeof(char*));

			while (m < j)
			{
				argv[i][l] = commands[m];
				m++;
				l++;
			}

			l = 0;
			m = j + 1;
			i++;			

		}

		else if (commands[j] == '/')
		{
			while (commands[j] == '/')
			{
				counter++;
				j++;
			}

			argv[i] = malloc(counter * sizeof(char*));

			while (m < j)
			{
				argv[i][l] = commands[m];
				m++;
				l++;
			}

			l = 0;
			m = j + 1;
			i++;			

		}

		else if (commands[j] == ' ')
		{
			while (commands[j] == ' ')
				j++;

			m = j;

		}

		else
			i++;


		counter = 0;

}

	int q;
	
	for (q = 0; q < numElements; q++)
	{
		if (argv[q] == '\0')
			break;

	}	

	numElements = q;
	argc = q;	
	
	return argc; 	 		
}
				
int main(int argc , char** argv)
{
	// Get initial string data.
	char* commands = malloc(100 * sizeof(char));
	assert(commands != 0);
	printf("\nPlease enter a valid reverse polish notation to the command line. Make sure to type calc first.\n");
	fgets(commands, 100, stdin);
	
	int size = strlen(commands);
	size--;
	argc = size - 4; // no calc

	// transfer to array of chars
	argv = malloc(argc * sizeof(char*));
	size = transfer(argc, argv, commands);	
	argc = size;

	double RESULT = 0;

	// assume each argument is contained in the argv array
	// argc-1 determines the number of operands + operators
	if (argc == 1)
		return 0;
	else
		RESULT = calculate(argc, argv);

	printf("\nThe result is: %f", RESULT);	

	return 0;
}

	
