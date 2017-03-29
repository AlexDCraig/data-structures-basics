/* Need to complete removeFront and removeBack. */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define TYPE double

struct Deque
{
	TYPE* data;
	int capacity;
	int size;
	int start;
};

void setCapacityDeque(struct Deque*, int);
void freeDeque(struct Deque*);
void deleteDeque(struct Deque*);
void initializeDeque(struct Deque*, int);
int getSize(struct Deque*);
void doubleCapacityDeque(struct Deque*);
void addFrontDeque(struct Deque*, TYPE);
void addBackDeque(struct Deque*, TYPE);
TYPE frontDeque(struct Deque*);
TYPE backDeque(struct Deque*);
void removeFrontDeque(struct Deque*);
void removeBackDeque(struct Deque*);

int main()
{
	struct Deque* myDeque = malloc(sizeof(myDeque));
	initializeDeque(myDeque, 5);
	addFrontDeque(myDeque, 1);
	addFrontDeque(myDeque, 2);
	addFrontDeque(myDeque, 3);
	//removeFrontDeque(myDeque);
	//removeBackDeque(myDeque);
	printf("%f", frontDeque(myDeque));
	deleteDeque(myDeque);				
	return 0;
}

void setCapacityDeque(struct Deque* myDeque, int newCap)
{
	// Create a new underlying array.
	TYPE* newData = (TYPE*)malloc(newCap * sizeof(TYPE));
	assert(newData != 0);

	// Copy elements to it. Notice how elementTracker helps us "wrap" around the array.
	int elementTracker = myDeque->start;

	int i;
	for (i = 0; i < myDeque->size; i++)
	{
		newData[i] = myDeque->data[i];
	
		elementTracker = elementTracker + 1;
		
		if (elementTracker >= myDeque->capacity)
			elementTracker = 0;
	}

	// Delete the old array.
	free(myDeque->data);
	// Update the array.
	myDeque->data = newData;
	myDeque->capacity = newCap;
	myDeque->start = 0;
}

void freeDeque(struct Deque* myDeque)
{
	free(myDeque->data);
	myDeque->size = 0;
	myDeque->capacity = 0;
}

void deleteDeque(struct Deque* myDeque)
{
	assert (myDeque != 0);
	freeDeque(myDeque);
	free(myDeque);
}
	

void initializeDeque(struct Deque* myDeque, int initialCapacity)
{
	if (initialCapacity <= 1 && initialCapacity >= 0)
		initialCapacity += 2;
	else if (initialCapacity < 0)
		printf("\n Invalid.");

	myDeque->size = 0;
	myDeque->capacity = initialCapacity;
	myDeque->data = (TYPE*) malloc (initialCapacity * sizeof(TYPE));
	assert(myDeque->data != 0);

	int i = 2;	
	myDeque->start = (initialCapacity / i);			
}

int getSize(struct Deque* myDeque)
{
	return myDeque->size;
}

void doubleCapacityDeque(struct Deque* myDeque)
{
	setCapacityDeque(myDeque, 2 * myDeque->capacity);	
}

void addFrontDeque(struct Deque* myDeque, TYPE newValue)
{
	if (myDeque->size >= myDeque->capacity)
		doubleCapacityDeque(myDeque);
	
	if (myDeque->start - 1 < 0)
		doubleCapacityDeque(myDeque);

	myDeque->start--;
	myDeque->data[myDeque->start] = newValue;
	myDeque->size++;	
}
 
void addBackDeque(struct Deque* myDeque, TYPE newValue)
{
	if (myDeque->size >= myDeque->capacity)
		doubleCapacityDeque(myDeque);

	if (myDeque->size + 1 >= myDeque->capacity)
		doubleCapacityDeque(myDeque);

	if (myDeque->size + myDeque->start > myDeque->capacity)
		doubleCapacityDeque(myDeque);  

	myDeque->size++;
	myDeque->data[myDeque->size + myDeque->start] = newValue;

}

TYPE frontDeque(struct Deque* myDeque)
{
	return myDeque->data[myDeque->start];		
}

TYPE backDeque(struct Deque* myDeque)
{
	return myDeque->data[myDeque->size + myDeque->start];
}

void removeFrontDeque(struct Deque* myDeque)
{
	if (myDeque->size > 0)
	{
		myDeque->size--;
		myDeque->start++;
	}

	else
	{
		printf("\n ERROR: Nothing in deque.");
		return;
	}

	TYPE* newData = (TYPE*) malloc (sizeof(TYPE));
	assert (newData != 0);
	
	int elementTracker = myDeque->start;
	int i;

	for (i = myDeque->start; i < (myDeque->size + myDeque->start); i++)
	{
		newData[i] = myDeque->data[i];
		elementTracker = elementTracker + 1;
		
		if (elementTracker >= myDeque->capacity)
			elementTracker = 0;
	}

	free(myDeque->data);
	myDeque->data = newData;	
			
}

void removeBackDeque(struct Deque* myDeque)
{
}



