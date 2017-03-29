#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define TYPE double

/* LINKED LIST NODE STRUCTURE */

struct node
{
	TYPE value;
	struct node* next;
};

/* LINKED LIST STACK IMPLEMENTATIONS */

struct linkStack
{
	struct node* top;
};

void initializeStack(struct linkStack* stack)
{
	stack->top = 0; // set the top node to a null value
}

int isEmpty(struct linkStack* stack)
{
	if (stack->top == 0) // if there remains nothing in the stack
		return 1;
	else
		return 0;
} 

void push(struct linkStack* stack, TYPE entry)
{
	if (stack->top == 0) // if the stack is empty
	{
		stack->top  = (struct node*) malloc (1 * sizeof(struct node));
		assert(stack->top != 0); // make sure the memory allocation worked
		stack->top->next = 0; // null the next link
		stack->top->value = entry;
	}

	else // there is stuff in the stack
	// Make a new node- this node will become the top, the node that will
	// be popped off next. Set new node's next node to the top, which will
	// become the old top. Perform the switch.
	{
		struct node* newTop = (struct node*) malloc (1 * sizeof(struct node));
		newTop->next = stack->top;
		newTop->value = entry;
		stack->top = newTop;
	}
}

TYPE top(struct linkStack* stack)
{
	TYPE topNum = stack->top->value;
	return topNum;
}

void pop(struct linkStack* stack) // remember to set top to 0 if last element
{
	// tempStack will be used to traverse the stack and make freeing memory
	// possible

	struct node* tempNode = (struct node*) malloc (1 * sizeof(struct node));
	tempNode = stack->top;

	if (tempNode == 0)
	{
		printf("Nothing in the stack.\n");
			return;
	}

	else
	{
		tempNode = tempNode->next; // move the top node to the next most recent node					
		free(stack->top); // erase the old top-- "pop it off"
		stack->top = tempNode; // make the next top the next most recent pushed on value
	}
}
	
void freeStack(struct linkStack* stack)
{
	while(isEmpty(stack) == 0) // while there remains elements in the stack, pop out each value
	{
		pop(stack); // the pop function deletes the top node
	}
}

void deleteStack(struct linkStack* myStack)
{
	assert(myStack != 0);
	freeStack(myStack);
	free(myStack);
}
	
int main()
{
	struct linkStack* myStack = (struct linkStack*) malloc (1 * sizeof(struct linkStack));
	initializeStack(myStack);
	push(myStack, 1);
	push(myStack, 2);
	push(myStack, 3);
	push(myStack, 4);
	pop(myStack);
	printf("%f", top(myStack));
	deleteStack(myStack);		
	return 0;
}
