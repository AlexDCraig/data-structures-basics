#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define TYPE double
#ifndef EQ
#define EQ(a, b) (a == b)
#endif

/*** SKELETON OF LINKEDLIST STRUCTURE ***/
struct Node
{
	TYPE val;
	struct Node* next;
	struct Node* prev;
};

struct List
{
	struct Node* frontSentinel;
	struct Node* backSentinel;
	int size;
};

struct List* createList();
void initList(struct List*);
void deleteList(struct List*);
void freeList(struct List*);
// Given a Node address, place the data right before that Node.
void _addBefore(struct List*, struct Node*, TYPE);
// Given a Node address, traverse the list and remove the Node.
void _removeLink(struct List*, struct Node*);
// Use _addBefore to add data right after the front sentinel.
void addNode(struct List*, TYPE);
// Will be used in accordance with the other functions to
// determine if the data is found in the list.
int contains(struct List*, TYPE);
// Given data, remove it from the List if it exists.
void removeValue(struct List*, TYPE);
void printList(struct List*);

/*** SKELETON OF LINKEDLIST ITERATOR. ***/
struct ListIterator
{
	struct List* listToIterate;
	struct Node* currentLink;
};

struct ListIterator* createListIterator(struct List*);
// void _removeNode(struct List*, struct Node*); 
int hasNextListIterator(struct ListIterator*);
TYPE nextListIterator(struct ListIterator*);
void removeListIterator(struct ListIterator*);
void deleteListIterator(struct ListIterator*);

int main()
{
	struct List* myList = createList();
	struct ListIterator* myIterator = createListIterator(myList);
	addNode(myList, 1);
	addNode(myList, 2);
	addNode(myList, 3);
	addNode(myList, 4);

	while(hasNextListIterator(myIterator) == 1)
	{
		if (nextListIterator(myIterator) == 3)
			removeListIterator(myIterator);

	} 
	
	printList(myList);		

	deleteListIterator(myIterator);
	deleteList(myList);		
	return 0;
}

/*** IMPLEMENTATION OF THE LINKED LIST BAG***/
struct List* createList()
{
	struct List* newList = malloc(sizeof(struct List));
	initList(newList);
	return newList;
}

void initList(struct List* myList)
{
	myList->frontSentinel = malloc(sizeof(struct Node));
	assert(myList->frontSentinel != 0);

	myList->backSentinel = malloc(sizeof(struct Node));
	assert(myList->backSentinel != 0);

	myList->frontSentinel->next = myList->backSentinel;
	myList->backSentinel->prev = myList->frontSentinel;

	myList->size = 0;
}

void deleteList(struct List* myList)
{
	assert(myList != 0);
	freeList(myList);
	free(myList);
}
// erases all components of the list aside from the list itself
void freeList(struct List* myList)
{
	while (myList->size > 0)
	{
		struct Node* deleteNode = myList->frontSentinel->next;
		_removeLink(myList, deleteNode);
	}

	myList->frontSentinel = myList->backSentinel = 0;
}

void _addBefore(struct List* myList, struct Node* afterNode, TYPE newData)
{
	// Our new structure to plug in.
	struct Node* newNode = malloc(sizeof(struct Node));	
	newNode->val = newData;

	// Our old structures to play around with.	
	struct Node* comesFirst = afterNode->prev;

	// Plug them in properly.
	comesFirst->next = newNode;
	newNode->prev = comesFirst;
	newNode->next = afterNode;
	afterNode->prev = newNode;

	myList->size++;
}

void _removeLink(struct List* myList, struct Node* removalNode)
{
	// Gather the structures that need to be re-linked up after deletion.
	struct Node* beforeNode = removalNode->prev;
	struct Node* afterNode = removalNode->next;

	// Sync them up.
	beforeNode->next = afterNode;
	afterNode->prev = beforeNode;

	// Free the link.
	free(removalNode);

	myList->size--;
}

// Position doesn't matter, but this will add a node right after the 
// front sentinel.
void addNode(struct List* myList, TYPE newData)
{
	_addBefore(myList, myList->frontSentinel->next, newData);	
}

int contains(struct List* myList, TYPE toFind)
{
	struct Node* traversal = myList->frontSentinel;
	int i;

	for (i = 0; i < myList->size; i++)
	{
		traversal = traversal->next;

		if (EQ(traversal->val, toFind))
			return 1;
	}

	return 0;
}	

void removeValue(struct List* myList, TYPE toRemove)
{
	struct Node* traversal = myList->frontSentinel;
	int i;

	for (i = 0; i < myList->size; i++)
	{
		traversal = traversal->next;

		if (EQ(traversal->val, toRemove))
		{
			_removeLink(myList, traversal);
			printf(" \n The value %f has been removed.", toRemove);
		}
	}
}

void printList(struct List* myList)
{
	struct Node* traversal = myList->frontSentinel;
	int i;

	for (i = 0; i < myList->size; i++)
	{
		traversal = traversal->next;

		printf("\n The value at node %d  is %f", i + 1, traversal->val);
	}
}

/*** IMPLEMENTATION OF THE LINKED LIST ITERATOR ***/
struct ListIterator* createListIterator(struct List* myList)
{
	struct ListIterator* myListIterator;
	myListIterator = malloc(sizeof(struct ListIterator));
	assert(myListIterator != 0);

	myListIterator->listToIterate = myList;
	myListIterator->currentLink = myList->frontSentinel;

	return myListIterator;
}

int hasNextListIterator(struct ListIterator* myListIterator)
{
	struct List* myList = myListIterator->listToIterate;
	
	// The list must have a node after the front sentinel and the next link must not be the back sentinel to be valid.

	if (myList->size > 0 && myListIterator->currentLink->next != myList->backSentinel)
		return 1;

	else
		return 0;
}
	
// Must be used in conjunction with hasNext.
TYPE nextListIterator(struct ListIterator* myListIterator)
{
	myListIterator->currentLink = myListIterator->currentLink->next;	
	return myListIterator->currentLink->val;
} 

void removeListIterator(struct ListIterator* myListIterator)
{
	struct Node* tempLink = myListIterator->currentLink->prev;
	_removeLink(myListIterator->listToIterate, myListIterator->currentLink);
	myListIterator->currentLink = tempLink;
}

void deleteListIterator(struct ListIterator* myListIterator)
{
	assert(myListIterator != 0);

	myListIterator->listToIterate = 0;
	myListIterator->currentLink = 0;

	free(myListIterator);
}	

