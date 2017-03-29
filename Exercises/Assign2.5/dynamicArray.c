/*	dynamicArray.c: Dynamic Array implementation. */
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "dynamicArray.h"

struct DynArr
{
	TYPE *data;		/* pointer to the data array */
	int size;		/* Number of elements in the array */
	int capacity;	/* capacity ofthe array */
};


/* ************************************************************************
	Dynamic Array Functions
************************************************************************ */

/* Initialize (including allocation of data array) dynamic array.

	param: 	v		pointer to the dynamic array
	param:	cap 	capacity of the dynamic array
	pre:	v is not null
	post:	internal data array can hold cap elements
	post:	v->data is not null
*/
void initDynArr(DynArr *v, int capacity)
{
	assert(capacity > 0);
	assert(v!= 0);
	v->data = (TYPE *) malloc(sizeof(TYPE) * capacity);
	assert(v->data != 0);
	v->size = 0;
	v->capacity = capacity;	
}

/* Allocate and initialize dynamic array.

	param:	cap 	desired capacity for the dyn array
	pre:	none
	post:	none
	ret:	a non-null pointer to a dynArr of cap capacity
			and 0 elements in it.		
*/
DynArr* createDynArr(int cap)
{
	DynArr *r;
	assert(cap > 0);
	r = (DynArr *)malloc(sizeof( DynArr));
	assert(r != 0);
	initDynArr(r,cap);
	return r;
}

/* Deallocate data array in dynamic array. 

	param: 	v		pointer to the dynamic array
	pre:	none
	post:	d.data points to null
	post:	size and capacity are 0
	post:	the memory used by v->data is freed
*/
void freeDynArr(DynArr *v)
{
	if(v->data != 0)
	{
		free(v->data); 	/* free the space on the heap */
		v->data = 0;   	/* make it point to null */
	}
	v->size = 0;
	v->capacity = 0;
}

/* Deallocate data array and the dynamic array ure. 

	param: 	v		pointer to the dynamic array
	pre:	none
	post:	the memory used by v->data is freed
	post:	the memory used by d is freed
*/
void deleteDynArr(DynArr *v)
{
	freeDynArr(v);
	free(v);
}

/* Resizes the underlying array to be the size cap 

	param: 	v		pointer to the dynamic array
	param:	cap		the new desired capacity
	pre:	v is not null
	post:	v has capacity newCap
*/
void _dynArrSetCapacity(DynArr *v, int newCap)
{	
	TYPE* newData = malloc(newCap * sizeof(TYPE));
	int k;
	int size = v->size;

	for (k = 0; k < size; k++)
		newData[k] = v->data[k];

	freeDynArr(v);
	v->data = newData;
	v->capacity = newCap;
	v->size = size;
}

/* Get the size of the dynamic array

	param: 	v		pointer to the dynamic array
	pre:	v is not null
	post:	none
	ret:	the size of the dynamic array
*/
int sizeDynArr(DynArr *v)
{
	return v->size;
}

/* 	Adds an element to the end of the dynamic array

	param: 	v		pointer to the dynamic array
	param:	val		the value to add to the end of the dynamic array
	pre:	the dynArry is not null
	post:	size increases by 1
	post:	if reached capacity, capacity is doubled
	post:	val is in the last utilized position in the array
*/
void addDynArr(DynArr *v, TYPE val)
{
	// Check to see if you need to resize.
	if (v->size >= v->capacity)
		_dynArrSetCapacity(v, 2 * v->capacity);

	v->data[v->size] = val;
	v->size++;

}

/*	Get an element from the dynamic array from a specified position
	
	param: 	v		pointer to the dynamic array
	param:	pos		integer index to get the element from
	pre:	v is not null
	pre:	v is not empty
	pre:	pos < size of the dyn array and >= 0
	post:	no changes to the dyn Array
	ret:	value stored at index pos
*/

TYPE getDynArr(DynArr *v, int pos)
{
	if (pos >= 0 && pos < v->size) // If position < 0:: no element there. No element at size, either- that's where the next free element is to be placed.
		return v->data[pos];

	else
	{
		printf("\n ERROR: Invalid element.");
		return 0;
	}
}

/*	Put an item into the dynamic array at the specified location,
	overwriting the element that was there

	param: 	v		pointer to the dynamic array
	param:	pos		the index to put the value into
	param:	val		the value to insert 
	pre:	v is not null
	pre:	v is not empty
	pre:	pos >= 0 and pos < size of the array
	post:	index pos contains new value, val
*/
void putDynArr(DynArr *v, int pos, TYPE val)
{
	if (pos < 0 || pos >= v->size)
	{
		printf("\n No such element.");
		return;
	}

	else
	{
		printf("\n Previous occupant of element: %f", v->data[pos]);
		v->data[pos] = val;
		printf("\n New occupant of element: %f", v->data[pos]);
	}
}

/*	Swap two specified elements in the dynamic array

	param: 	v		pointer to the dynamic array
	param:	i,j		the elements to be swapped
	pre:	v is not null
	pre:	v is not empty
	pre:	i, j >= 0 and i,j < size of the dynamic array
	post:	index i now holds the value at j and index j now holds the value at i
*/
void swapDynArr(DynArr *v, int i, int  j)
{
	if (i < 0 || i >= v->size || j < 0 || j >= v->size)
	{
		printf("\n No such element.");
		return;
	}

	else
	{
		printf("\n BEFORE SWAP: Element at position one = %f, Element at position two = %f", v->data[i], v->data[j]);
		TYPE temp = v->data[i];
		v->data[i] = v->data[j];
		v->data[j] = temp;
		printf("\n AFTER SWAP: Element at position one = %f, Element at position two = %f", v->data[i], v->data[j]);
	}
}

/*	Remove the element at the specified location from the array,
	shifts other elements back one to fill the gap

	param: 	v		pointer to the dynamic array
	param:	idx		location of element to remove
	pre:	v is not null
	pre:	v is not empty
	pre:	idx < size and idx >= 0
	post:	the element at idx is removed
	post:	the elements past idx are moved back one
*/
void removeAtDynArr(DynArr *v, int idx)
{
	if (idx < 0 || idx >= v->size)
	{
		printf("\n No such element.");
		return;
	}

	else if (idx == v->size - 1) // delete final element, no other elements must be changed
	{
		int cap = v->capacity;
		TYPE* newData = malloc(cap * sizeof(TYPE));
		int k;
		int size = v->size - 1; // we want to copy all elements but the final occupied one

		for (k = 0; k < size; k++)
		{
			newData[k] = v->data[k];
		}

		freeDynArr(v);
		v->data = newData;
		v->capacity = cap;
		v->size = size;
	}

	else // each element before the position is to remain the same. the element itself is to be removed. each element following the position is to be moved backward one.
	{
		int cap = v->capacity;
		TYPE* newData = malloc(cap * sizeof(TYPE));
		int k;
		int size = v->size;

		for (k = 0; k < size; k++)
		{
			if (k < idx)
				newData[k] = v->data[k];

			else if (k >= idx)
				newData[k] = v->data[k + 1];
		}

		freeDynArr(v);
		v->data = newData;
		v->capacity = cap;
		v->size = size - 1;
	}

}

/* ************************************************************************
	Stack Interface Functions
************************************************************************ */

/*	Returns boolean (encoded in an int) demonstrating whether or not the 
	dynamic array stack has an item on it.

	param:	v		pointer to the dynamic array
	pre:	the dynArr is not null
	post:	none
	ret:	1 if empty, otherwise 0
*/
int isEmptyDynArr(DynArr *v)
{
	if (v->size == 0)
		return 1; // return true

	else
		return 0; // return false
}

/* 	Push an element onto the top of the stack

	param:	v		pointer to the dynamic array
	param:	val		the value to push onto the stack
	pre:	v is not null
	post:	size increases by 1
			if reached capacity, capacity is doubled
			val is on the top of the stack
*/
void pushDynArr(DynArr *v, TYPE val)
{
	addDynArr(v, val);
}

/*	Returns the element at the top of the stack 

	param:	v		pointer to the dynamic array
	pre:	v is not null
	pre:	v is not empty
	post:	no changes to the stack
*/
TYPE topDynArr(DynArr *v)
{
	assert (v != 0);

	int CURRENT_SIZE = v->size;

	if (CURRENT_SIZE > 0)
	return v->data[CURRENT_SIZE - 1];

	else
		return 0;
}

/* Removes the element on top of the stack 

	param:	v		pointer to the dynamic array
	pre:	v is not null
	pre:	v is not empty
	post:	size is decremented by 1
			the top has been removed
*/
void popDynArr(DynArr *v)
{
	assert (v != 0);
	removeAtDynArr(v, (v->size - 1));
}

/* ************************************************************************
	Bag Interface Functions
************************************************************************ */

/*	Returns boolean (encoded as an int) demonstrating whether or not
	the specified value is in the collection
	true = 1
	false = 0

	param:	v		pointer to the dynamic array
	param:	val		the value to look for in the bag
	pre:	v is not null
	pre:	v is not empty
	post:	no changes to the bag
*/
int containsDynArr(DynArr *v, TYPE val)
{
	int i;

	for (i = 0; i < v->size; i++)
	{
		if (EQ(val, v->data[i])) // if data found
		{
			return 1;
		}
	}

	return 0;
}

/*	Removes the first occurrence of the specified value from the collection
	if it occurs

	param:	v		pointer to the dynamic array
	param:	val		the value to remove from the array
	pre:	v is not null
	pre:	v is not empty
	post:	val has been removed
	post:	size of the bag is reduced by 1
*/
void removeDynArr(DynArr *v, TYPE val)
{
	int i;
	for (i = 0; i < v->size; i++)
	{
		if (EQ(val, v->data[i])) // if data found
		{
			removeAtDynArr(v, i);
			return;
		
		}
	}
}
