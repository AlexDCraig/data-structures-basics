#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "dynArr.h"

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
		/*if ((strcmp(s, "+") != 0) && (strcmp(s, "^2")) && (strcmp(s, "^3")) && (strcmp(s, "-") != 0) && (strcmp(s, "/") != 0) && (strcmp(s, "x") != 0) && (strcmp(s, "^") != 0) && (strcmp(s, "abs") != 0) && (strcmp(s, "sqrt") != 0) && (strcmp(s, "exp") != 0) && (strcmp(s, "ln") != 0) && (strcmp(s, "log") != 0) && (isdigit(*s) != 0))
		{
			printf("\nERROR: You have entered a string of characters not recognized in this program.");
			exit(1);
		}*/

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

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and 
	their sum is pushed back onto the stack.
*/
void add (struct DynArr *stack)
{
	// Error condition #1: Nothing in stack.
	if (isEmptyDynArr(stack) == 1) // stack is empty
	{
		printf("\nERROR: You need two numbers to perform a sum operation.");
		exit(1);
	}

	double firstNum = topDynArr(stack);
	popDynArr(stack);

	// Error condition #2: only one number is provided.
	if (isEmptyDynArr(stack)== 1)
	{
		printf("\nERROR: Sum operation requires two numbers.");
		exit(1);
	}

	double secondNum = topDynArr(stack);
	popDynArr(stack);

	pushDynArr(stack, firstNum + secondNum); // Top of the stack is now the sum. 	
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and 
	their difference is pushed back onto the stack.
*/
void subtract(struct DynArr *stack)
{
	if (isEmptyDynArr(stack) == 1)
	{
		printf("\nERROR: Subtraction requires two operands.");
		exit(1);
	}

	double secondNum = topDynArr(stack);
	popDynArr(stack);

	if (isEmptyDynArr(stack) == 1)
	{
		printf("\nERROR: Subtraction requires two operands.");
		exit(1);
	}

	double firstNum = topDynArr(stack);
	popDynArr(stack);

	pushDynArr(stack, firstNum - secondNum);
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and 
	their quotient is pushed back onto the stack.
*/
void divide(struct DynArr *stack)
{
	if (isEmptyDynArr(stack) == 1)
	{
		printf("\nERROR: Division requires two operands.");
		exit(1);
	}

	double denominator = topDynArr(stack);
	popDynArr(stack);

	if (isEmptyDynArr(stack) == 1)
	{
		printf("\nERROR: Division requires another operand.");
		exit(1);
	}

	double numerator = topDynArr(stack);
	popDynArr(stack);

	pushDynArr(stack, numerator / denominator);
}

void multiply(struct DynArr *stack)
{
	if (isEmptyDynArr(stack) == 1)
	{
		printf("\nERROR: Multiplication requires two operands.");
		exit(1);
	}

	double secondNum = topDynArr(stack);
	popDynArr(stack);

	if (isEmptyDynArr(stack) == 1)
	{
		printf("\nERROR: Multiplication requires another operand.");
		exit(1);
	}

	double firstNum = topDynArr(stack);
	popDynArr(stack);

	pushDynArr(stack, (firstNum * secondNum));
}

void square(struct DynArr* stack)
{
	if (isEmptyDynArr(stack) == 1)
	{
		printf("\nERROR: No number to square provided.");
		exit(1);
	}

	double numToSquare = topDynArr(stack);
	popDynArr(stack);

	pushDynArr(stack, (pow(numToSquare, 2)));
}
	 

void power(struct DynArr *stack)
{
	if (isEmptyDynArr(stack) == 1)
	{
		printf("\nERROR: A power operation requires syntax like so: 5 4 ^");
		exit(1);
	}

	double exponent = topDynArr(stack);
	popDynArr(stack);

	if (isEmptyDynArr(stack) == 1)
	{
		printf("\nERROR: Bad syntax.");
		exit(1);
	}

	double numToExp = topDynArr(stack);
	popDynArr(stack);	

	pushDynArr(stack, (pow(numToExp, exponent)));
}

void cube(struct DynArr *stack)
{
	if (isEmptyDynArr(stack) == 1)
	{
		printf("\nERROR: No number to cube provided.");
		exit(1);
	}

	double numToCube = topDynArr(stack);
	popDynArr(stack);

	pushDynArr(stack, (pow(numToCube, 3))); 
}

void absol(struct DynArr* stack)
{
	if (isEmptyDynArr(stack) == 1)
	{
		printf("\nERROR: No number to absolute value.");
		exit(1);
	}
	
	double numToAbs = topDynArr(stack);
	popDynArr(stack);

	double result = 0;

	if (numToAbs < 0)
		result = numToAbs * -1;

	else
		result = numToAbs;

	pushDynArr(stack, result);
}

void squrt(struct DynArr* stack)
{
	if (isEmptyDynArr(stack) == 1)
	{
		printf("\nERROR: No number to square root.");
		exit(1);
	}

	double numToSqrt = topDynArr(stack);
	popDynArr(stack);

	double result = sqrt(numToSqrt);

	pushDynArr(stack, result);

}

void expon(struct DynArr* stack)
{
	if (isEmptyDynArr(stack) == 1)
	{
		printf("\nERROR: No number.");
		exit(1);
	}

	double numToExp = topDynArr(stack);
	popDynArr(stack);	

	double result = exp(numToExp);

	pushDynArr(stack, result);
}

void ln(struct DynArr* stack)
{
	if (isEmptyDynArr(stack) == 1)
	{
		printf("\nERROR: No number.");
		exit(1);
	}

	double numToLn = topDynArr(stack);
	popDynArr(stack);

	double result = log(numToLn); // natural log
	
	pushDynArr(stack, result);
}

void logbs(struct DynArr* stack)
{
	if (isEmptyDynArr(stack) == 1)
	{
		printf("\nERROR: No number.");
		exit(1);
	}
	
	double numToLog = topDynArr(stack);
	popDynArr(stack);

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

		else if (strcmp(s, "^") == 0)
		{
			power(stack);
		}

		else if(strcmp(s, "^2") == 0)
		{
			square(stack);
		}

		else if (strcmp(s, "^3") == 0)
		{
			cube(stack);
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

		else 
		{
			printf("\nERROR: Invalid figures in command.");
			printf("\nThe offending character(s): %s \n", s);
			exit(1);
		}

	}	//end for 

	/* FIXME: You will write this part of the function (2 steps below) 
	 * (1) Check if everything looks OK and produce an error if needed.
	 * (2) Store the final value in result and print it out.
	 */

	result = topDynArr(stack); 
	popDynArr(stack);

	if (isEmptyDynArr(stack) == 0)
	{
		printf("\nERROR: Too many figures provided to perform the calculations properly.\n");
		exit(1);
	}

	return result;
}

int main(int argc , char** argv)
{
	// assume each argument is contained in the argv array
	// argc-1 determines the number of operands + operators
	if (argc == 1)
		return 0;

	printf("\nThe result is: %f", calculate(argc,argv));
	return 0;
}
