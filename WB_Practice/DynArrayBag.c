#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define TYPE double
#ifndef EQ
#define EQ(a, b) (a == b)
#endif

// MY DYNAMIC ARRAY STRUCTURE AND ITS CORRESPONDING FUNCTIONS
struct DynArr
{
	TYPE* data;
	int size;
	int capacity;
};

void initDynArr(struct DynArr*, int);
void addDynArr(struct DynArr*, TYPE);
void _setCapacityDynArr(struct DynArr*, int);
void removeDynArr(struct DynArr*, TYPE);
void _removeAtDynArr(struct DynArr*, int);
int containsDynArr(struct DynArr*, TYPE);
void freeDynArr(struct DynArr*);
void deleteDynArr(struct DynArr*);
void printMyBag(struct DynArr*);

// MY DYNAMIC ARRAY'S ITERATOR AND ITS CORRESPONDING FUNCTIONS
struct DynArrIterator
{
	struct DynArr* referenceArr;
	int currentIndex;
};

void initDynArrIterator(struct DynArr*, struct DynArrIterator*);
int hasNextDynArrIterator(struct DynArrIterator*);
TYPE nextDynArrIterator(struct DynArrIterator*);
void removeDynArrIterator(struct DynArrIterator*);
void deleteMyIterator(struct DynArrIterator*);

int main()
{
	// Make and initialize my dynamic array.
	struct DynArr* myArr = malloc(sizeof(struct DynArr)); 
	initDynArr(myArr, 1);
	
	// Make and initialize my iterator. Give it the address of my array.
	struct DynArrIterator* myIt = malloc(sizeof(struct DynArrIterator));
	initDynArrIterator(myArr, myIt);

	// Add some stuff to make sure the iterator works.
	addDynArr(myArr, 1);
	addDynArr(myArr, 2);
	addDynArr(myArr, 3);
	addDynArr(myArr, 4);
	
	// Iterate, loop.
	TYPE current;
	int i = 0;

	printMyBag(myArr);

	while (hasNextDynArrIterator(myIt) == 1)
	{
		current = nextDynArrIterator(myIt);
		
		if (i == 3)
		removeDynArrIterator(myIt);

		i++;						
	}
	
	printMyBag(myArr);
	
	deleteDynArr(myArr);
	deleteMyIterator(myIt);

	return 0;
}

/******** IMPLEMENTATION OF DYNAMIC ARRAY STRUCTURE FUNCTIONS *********/
void initDynArr(struct DynArr* myArr, int initCap)
{
	myArr->data = malloc(initCap * sizeof(TYPE));
	assert(myArr->data != 0);

	myArr->size = 0;
	myArr->capacity = initCap;
}

void addDynArr(struct DynArr* myArr, TYPE val)
{
	// Check to see if you need to resize.
	if (myArr->size >= myArr->capacity)
		_setCapacityDynArr(myArr, 2 * myArr->capacity);

	myArr->data[myArr->size] = val;
	myArr->size++;
}

void _setCapacityDynArr(struct DynArr* myArr, int newCap)
{
	TYPE* newData = malloc(newCap * sizeof(TYPE));
	int k;
	int size = myArr->size;

	for (k = 0; k < size; k++)
		newData[k] = myArr->data[k];

	freeDynArr(myArr);
	myArr->data = newData;
	myArr->capacity = newCap;
	myArr->size = size;
}

// EXAMINES THE ARRAY TO FIND WHERE THE VALUE IS, THEN
// SENDS THE ELEMENT WHERE IT IS TO THE REMOVEAT
// FUNCTION FOR REMOVAL.
void removeDynArr(struct DynArr* myBag, TYPE test)
{
	int i;
	for (i = 0; i < myBag->size; i++)
	{
		if (EQ(test, myBag->data[i])) // if data found
		{
			_removeAtDynArr(myBag, i);
			return;
		}
	}
}						

void _removeAtDynArr(struct DynArr* myArr, int index)
{
	if (index < 0 || index >= myArr->size)
	{
		printf("\n No such element.");
		return;
	}

	else if (index == myArr->size - 1) // delete final element, no other elements must be changed
	{
		int cap = myArr->capacity;
		TYPE* newData = malloc(cap * sizeof(TYPE));
		int k;
		int size = myArr->size - 1; // we want to copy all elements but the final occupied one

		for (k = 0; k < size; k++)
		{
			newData[k] = myArr->data[k];
		}

		freeDynArr(myArr);
		myArr->data = newData;
		myArr->capacity = cap;
		myArr->size = size;
	}

	else // each element before the position is to remain the same. the element itself is to be removed. each element following the position is to be moved backward one.
	{
		int cap = myArr->capacity;
		TYPE* newData = malloc(cap * sizeof(TYPE));
		int k;
		int size = myArr->size;

		for (k = 0; k < size; k++)
		{
			if (k < index)
				newData[k] = myArr->data[k];

			else if (k >= index)
				newData[k] = myArr->data[k+1];
		}

		freeDynArr(myArr);
		myArr->data = newData;
		myArr->capacity = cap;
		myArr->size = size - 1;
	}	

}

// Searches thru the array: if the search value is in
// the array then it returns 1, or true, otherwise returns 0.
// There can be multiple versions of the value in the array
// and it will only return once.
int containsDynArr(struct DynArr* myBag, TYPE searchVal)
{
	int i;

	for (i = 0; i < myBag->size; i++)
	{
		if (EQ(searchVal, myBag->data[i])) // if data found
		{
			return 1;
		}
	}

	return 0;
}

void freeDynArr(struct DynArr* myArr) // For the purpose of erasing the
// dynamic array's data. This doesn't erase the array itself.
{
	if (myArr->data != 0)
	{
		free(myArr->data);
		myArr->data = 0; // myArr's data is now NULL
	}	

	myArr->size = 0;
	myArr->capacity = 0;
}

void deleteDynArr(struct DynArr* myArr)
{
	assert (myArr != 0);
	freeDynArr(myArr);
	free(myArr);
}

void printMyBag(struct DynArr* myArr)
{
	int j;

	printf("\n \n");

	for (j = 0; j < myArr->size; j++)
		printf("\n %f", myArr->data[j]);
}

/******* IMPLEMENTATION OF ITERATOR FUNCTIONS **********/
void initDynArrIterator(struct DynArr* myArr, struct DynArrIterator* myIt)
{
	myIt->referenceArr = myArr;
	myIt->currentIndex = 0;	
}

int hasNextDynArrIterator(struct DynArrIterator* myIt)
{
	struct DynArr* reference = myIt->referenceArr;
	
	// If the current index is less than the size of the array,
	// then it can seize another element, i.e. return 1, for true.
	// Otherwise, it cannot iterate further, it must return 0.

	if (myIt->currentIndex < reference->size)
		return 1;

	else
		return 0;		
}

// Must be used with hasNext.
TYPE nextDynArrIterator(struct DynArrIterator* myIt)
{
	TYPE tempVal = myIt->referenceArr->data[myIt->currentIndex];
	myIt->currentIndex++; // move up to the next element

	return tempVal;
}	

void removeDynArrIterator(struct DynArrIterator* myIt)
{
	myIt->currentIndex--; // before decrementing, we are one above the last value entered
	_removeAtDynArr(myIt->referenceArr, myIt->currentIndex);
}

void deleteMyIterator(struct DynArrIterator* myIt)
{
	assert(myIt != 0);

	myIt->referenceArr = 0;
	myIt->currentIndex = 0;

	free(myIt);
}
