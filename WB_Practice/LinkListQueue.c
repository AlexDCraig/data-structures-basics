#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define TYPE double

/* Define Link structure. */

struct link
{
	TYPE value;
	struct link* next;
};

/* Define basic queue structure. */

struct Queue
{
	struct link* first;
	struct link* last;
};

/* Define basic operations for the queue structure. */

void initializeQueue(struct Queue* myQueue)
{
	myQueue = (struct Queue*) malloc (1 * sizeof(struct Queue));
	myQueue->first = 0;
	myQueue->last = 0;
}

void addBack(struct Queue* myQueue, TYPE newData)
{
	if (myQueue->last == 0) // if there's nothing in the queue
	{
		myQueue->last = (struct link*) malloc (1 * sizeof(struct link));
		myQueue->last->next = 0;
		myQueue->last->value = newData;
		myQueue->first = myQueue->last;
	}

	else // There is at least one element in this linked list.
	{
		struct link* temp = (struct link*) malloc (1 * sizeof(struct link));
		myQueue->last->next = temp;
		temp->value = newData;
		temp->next = 0;

		myQueue->last = temp;
	}
}

TYPE peekFront(struct Queue* myQueue)
{
	return myQueue->first->value; // recall the sentinel is first, what is the fist value after that
}

void removeFront(struct Queue* myQueue)
{
	struct link* tempFront = myQueue->first;

	if (tempFront == 0)
		printf("Nothing to remove.\n");

	else if (tempFront->next != 0)
	{
		tempFront = tempFront->next;
		printf("\n Dequeued: %f", myQueue->first->value);
		free(myQueue->first);
		myQueue->first = tempFront;
	}

	else if (tempFront->next == 0)
	{
		printf("\n Dequeued: %f", myQueue->first->value);
		free(myQueue->first);
		myQueue->first = 0;
		myQueue->last = 0;
	}					
}

int isEmptyQueue(struct Queue* myQueue)
{
	if (myQueue->first == 0)
		return 1;

	else
		return 0;
}

void deleteQueue(struct Queue* myQueue)
{
	assert(myQueue != 0);
	free(myQueue);
}

int main()
{
	struct Queue* myQ = (struct Queue*) malloc (1 * sizeof(struct Queue));
	initializeQueue(myQ);
	printf("\n Adding 5, 6, 7, and 8 in that order to the queue.\n");
	addBack(myQ, 5);
	addBack(myQ, 6);
	addBack(myQ, 7);
	addBack(myQ, 8);
	removeFront(myQ);
	printf("\n Value at the front: %f", peekFront(myQ));	 
	deleteQueue(myQ);	
	return 0;
}
