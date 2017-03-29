#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define TYPE double

struct DequeLink
{
	TYPE data;
	struct DequeLink* next;
	struct DequeLink* previous;
};

struct DequeList
{
	int size;
	struct DequeLink* frontSentinel;
	struct DequeLink* backSentinel;
};

void initializeList(struct DequeList*);
void freeDequeList(struct DequeList*);
void deleteList(struct DequeList*);
int dequeEmpty(struct DequeList*);
void addFront(struct DequeList*, TYPE);
void addBack(struct DequeList*, TYPE);
void removeFront(struct DequeList*);
void removeBack(struct DequeList*);
void addBefore(struct DequeList*, struct DequeLink*, TYPE);
void removeLink(struct DequeList*, struct DequeLink*);
TYPE getFront(struct DequeList*);
TYPE getBack(struct DequeList*);

int main()
{
	struct DequeList* myList = malloc(sizeof(struct DequeList));
	assert(myList != 0);
	initializeList(myList);
	addFront(myList, 1);
	addFront(myList, 2);
	addFront(myList, 3);
	addBack(myList, 4);
	printf("%f", getFront(myList));
	printf("\n %f", getBack(myList));
	deleteList(myList);	 
	return 0;
}

void initializeList(struct DequeList* myList)
{
	myList->frontSentinel = malloc(sizeof(struct DequeLink));
	assert(myList->frontSentinel != 0);

	myList->backSentinel = malloc(sizeof(struct DequeLink));
	assert(myList->backSentinel != 0);

	myList->frontSentinel->next = myList->backSentinel;
	myList->backSentinel->previous = myList->frontSentinel;

	myList->size = 0;
}

void freeDequeList(struct DequeList* myList)
{
	while (myList->size > 0)
		removeFront(myList);

	free (myList->frontSentinel);
	free (myList->backSentinel);

	myList->frontSentinel = myList->backSentinel = 0;
}

void deleteList(struct DequeList* myList)
{
	assert (myList != 0);
	freeDequeList(myList);
	free(myList);
}

int dequeEmpty(struct DequeList* myList)
{
	if (myList->size == 0)
		return 1; // TRUE. This list is empty.

	else
		return 0;
}

// This function adds the value immediately after the front sentinel.
void addFront(struct DequeList* myList, TYPE addVal)
{
	addBefore(myList, myList->frontSentinel->next, addVal);	
}

void addBack(struct DequeList* myList, TYPE addVal)
{
	addBefore(myList, myList->backSentinel, addVal);
}

void removeFront(struct DequeList* myList)
{
	if (dequeEmpty(myList) == 0) // there's stuff stored besides sentinels
		removeLink(myList, myList->frontSentinel->next);
}

void removeBack(struct DequeList* myList)
{
	if (dequeEmpty(myList) == 0)
		removeLink(myList, myList->backSentinel->previous);
}

void addBefore(struct DequeList* myList, struct DequeLink* afterNode, TYPE data)
{
	// Our new structure to plug in.
	struct DequeLink* newNode = malloc(sizeof(struct DequeLink));	
	newNode->data = data;

	// Our old structures to play around with.	
	struct DequeLink* comesFirst = afterNode->previous;

	// Plug them in properly.
	comesFirst->next = newNode;
	newNode->previous = comesFirst;
	newNode->next = afterNode;
	afterNode->previous = newNode;

	myList->size++;
}

void removeLink(struct DequeList* myList, struct DequeLink* removalNode)
{
	// Gather the structures that need to be re-linked up after deletion.
	struct DequeLink* beforeNode = removalNode->previous;
	struct DequeLink* afterNode = removalNode->next;

	// Sync them up.
	beforeNode->next = afterNode;
	afterNode->previous = beforeNode;

	// Free the link.
	free(removalNode);

	myList->size--;

}

TYPE getFront(struct DequeList* myList)
{
	if (myList->frontSentinel->next != myList->backSentinel)
		return myList->frontSentinel->next->data;
	else
		return 0;
}

TYPE getBack(struct DequeList* myList)
{
	if (myList->backSentinel->previous != myList->frontSentinel)
		return myList->backSentinel->previous->data;

	else
		return 0;
}
