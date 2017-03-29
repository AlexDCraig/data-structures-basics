#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define TYPE double

struct DynArr
{
	TYPE* data;
	int size;
	int capacity;
};

void initDynArr(struct DynArr* myArr, int initCap)
{
	myArr->data = malloc(initCap * sizeof(TYPE));
	assert(myArr->data != 0);

	myArr->size = 0;
	myArr->capacity = initCap;
}

struct DynArr* createDynArr(int cap)
{
	struct DynArr* r;
	assert(cap > 0);
	
	r = malloc(sizeof(struct DynArr));
	assert(r != 0);

	initDynArr(r, cap);

	return r;
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

int sizeDynArr(struct DynArr* myArr)
{
	return myArr->size;
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

void addDynArr(struct DynArr* myArr, TYPE val)
{
	// Check to see if you need to resize.
	if (myArr->size >= myArr->capacity)
		_setCapacityDynArr(myArr, 2 * myArr->capacity);

	myArr->data[myArr->size] = val;
	myArr->size++;
}

TYPE getDynArr(struct DynArr* myArr, int position)
{
	if (position >= 0 && position < myArr->size) // If position < 0:: no element there. No element at size, either- that's where the next free element is to be placed.
		return myArr->data[position];

	else
	{
		printf("\n ERROR: Invalid element.");
		return 0;
	}
}

void putDynArr(struct DynArr* myArr, int position, TYPE val)
{
	if (position < 0 || position >= myArr->size) 
	{
		printf("\n No such element.");
		return;
	}

	else
	{
		printf("\n Previous occupant of element: %f", myArr->data[position]);		
		myArr->data[position] = val;
		printf("\n New occupant of element: %f", myArr->data[position]);
	}
}
	
void swapDynArr(struct DynArr* myArr, int placeOne, int placeTwo)
{
	if (placeOne < 0 || placeOne >= myArr->size || placeTwo < 0 || placeTwo >= myArr->size)
	{
		printf("\n No such element.");
		return;
	}

	else
	{
		printf("\n BEFORE SWAP: Element at position one = %f, Element at position two = %f", myArr->data[placeOne], myArr->data[placeTwo]);
		TYPE temp = myArr->data[placeOne];
		myArr->data[placeOne] = myArr->data[placeTwo];
		myArr->data[placeTwo] = temp;
		printf("\n AFTER SWAP: Element at position one = %f, Element at position two = %f", myArr->data[placeOne], myArr->data[placeTwo]);
	}
}

void removeAtDynArr(struct DynArr* myArr, int index)
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

void printMyArr(struct DynArr* myArr)
{
	int j;

	printf("\n \n");

	for (j = 0; j < myArr->size; j++)
		printf("\n %f", myArr->data[j]);
}

int main()
{
	struct DynArr* myArray = createDynArr(3);
	addDynArr(myArray, 0);	
        addDynArr(myArray, 1);
	addDynArr(myArray, 2);	
	printMyArr(myArray);
	removeAtDynArr(myArray, 2);
	printMyArr(myArray);
	return 0;
}
