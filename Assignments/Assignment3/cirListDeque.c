#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <float.h>
#include "cirListDeque.h"

/* Double Link Struture */
struct DLink {
	TYPE value;/* value of the link */
	struct DLink * next;/* pointer to the next link */
	struct DLink * prev;/* pointer to the previous link */
};

# define TYPE_SENTINEL_VALUE DBL_MAX 


/* ************************************************************************
 Deque ADT based on Circularly-Doubly-Linked List WITH Sentinel
 ************************************************************************ */

struct cirListDeque {
	int size;/* number of links in the deque */
	struct DLink *sentinel;	/* pointer to the sentinel */
};
/* internal functions prototypes */
struct DLink* _createLink (TYPE val);
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, TYPE v);
void _removeLink(struct cirListDeque *q, struct DLink *lnk);



/* ************************************************************************
	Deque Functions
************************************************************************ */

/* Initialize deque.

	param: 	q		pointer to the deque
	pre:	q is not null
	post:	q->Sentinel is allocated and q->size equals zero
*/
void _initCirListDeque (struct cirListDeque *q) 
{
  	assert (q != 0);
	q->size = 0;
	q->sentinel = malloc(sizeof(struct DLink));
	q->sentinel->next = 0;
	q->sentinel->prev = 0;
	q->sentinel->value = 0;	 
}

/*
 create a new circular list deque
 
 */

struct cirListDeque *createCirListDeque()
{
	struct cirListDeque *newCL = malloc(sizeof(struct cirListDeque));
	_initCirListDeque(newCL);
	return(newCL);
}


/* Create a link for a value.

	param: 	val		the value to create a link for
	pre:	none
	post:	a link to store the value
*/
struct DLink * _createLink (TYPE val)
{
	struct DLink* myLink = malloc(sizeof(struct DLink));
	myLink->value = val;
	myLink->next = 0;
	myLink->prev = 0;	 

	return myLink;
}

/* Adds a link after another link

	param: 	q		pointer to the deque
	param: 	lnk		pointer to the existing link in the deque
	param: 	v		value of the new link to be added after the existing link
	pre:	q is not null
	pre: 	lnk is not null
	pre:	lnk is in the deque 
	post:	the new link is added into the deque after the existing link
*/
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, TYPE v)
{
	assert(q != 0);
	assert(lnk != 0);

	struct DLink* newLink = _createLink(v);	
	
	struct DLink* header = q->sentinel;
	
	struct DLink* temp = header;

	int truth = 0;

	while (temp->next != header) // loop thru the whole list
	{
		if (temp == lnk)
			truth = 1;

		temp = temp->next;
	}

	if (truth == 0 && lnk != header)
	{
		printf("\nThe link does not exist in the list.");
		exit(1);
	}		

	if (lnk == header) // old link is first item in list
	{
		if (q->size == 0)
		{
			header->prev = newLink;
			header->next = newLink;	
			newLink->prev = header;
			newLink->next = header;
			q->size++;
		}

		else
		{
			struct DLink* temp = header->next;
			header->next = newLink;
			newLink->prev = header;
			newLink->next = temp;
			temp->prev = newLink;
		}
	}

	else
	{
		if (lnk->next == header) // old link is last item in list
		{
			lnk->next = newLink;
			
			newLink->prev = lnk;
			newLink->next = header;

			header->prev = newLink;

			q->size++;
		}

		else // old item is between two items
		{
			temp = lnk->prev;	
			struct DLink* after = lnk->next;

			temp->next = newLink;
			after->prev = newLink;

			newLink->prev = temp;
			newLink->next = after;

			q->size++;
		}
	}
}

/* Adds a link to the back of the deque

	param: 	q		pointer to the deque
	param: 	val		value for the link to be added
	pre:	q is not null
	post:	a link storing val is added to the back of the deque
*/
void addBackCirListDeque (struct cirListDeque *q, TYPE val) 
{
	assert(q != 0);

	struct DLink* header = q->sentinel;
	struct DLink* newLink = _createLink(val);


	if (q->size == 0)
	{	
		header->prev = newLink;
		header->next = newLink;
		newLink->next = header;
		newLink->prev = header;

		q->size++;
	}
		
	else
	{
		struct DLink* temp = header->prev;
		temp->next = newLink;
		newLink->prev = temp;
		newLink->next = header;
		header->prev = newLink;

		q->size++;
	}
}

/* Adds a link to the front of the deque

	param: 	q		pointer to the deque
	param: 	val		value for the link to be added
	pre:	q is not null
	post:	a link storing val is added to the front of the deque
*/
void addFrontCirListDeque(struct cirListDeque *q, TYPE val)
{
	assert (q != 0);

	if (q->size == 0)
	{
		struct DLink* newLink = _createLink(val);
		
		q->sentinel->next = newLink;
		q->sentinel->prev = newLink;
		newLink->prev = q->sentinel;
		newLink->next = q->sentinel;

		q->size++;
	}
	
	else
	{	 
		struct DLink* header = q->sentinel;

		_addLinkAfter(q, header, val);
	}

}

/* Get the value of the front of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	none
	ret: 	value of the front of the deque
*/
TYPE frontCirListDeque(struct cirListDeque *q) 
{
	assert (q != 0);
	
	if (q->size == 0)
	{
		printf("\nNothing in the list.");
		exit(1);
	}

	struct DLink* temp = q->sentinel->next;

	return temp->value;
}

/* Get the value of the back of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	none
	ret: 	value of the back of the deque
*/
TYPE backCirListDeque(struct cirListDeque *q)
{
	assert (q != 0);

	if (q->size == 0)
	{
		printf("\nNothing in the list.");
		exit(1);
	}

	struct DLink* temp = q->sentinel->prev;

	return temp->value;
}

/* Remove a link from the deque

	param: 	q		pointer to the deque
	param: 	lnk		pointer to the link to be removed
	pre:	q is not null and q is not empty
	post:	the link is removed from the deque
*/
void _removeLink(struct cirListDeque *q, struct DLink *lnk)
{
	assert (q != 0);

	if (q->size == 0)
	{	 
		printf("\nNothing in the list.");
		exit(1);
	}

	if (lnk == q->sentinel)
	{
		printf("\nAttempt to delete the sentinel.");
		exit(1);
	}

	if (q->size == 1 && q->sentinel->next == lnk) // link is only element
	{
		q->sentinel->next = 0;
		q->sentinel->prev = 0;
		lnk->next = 0;
		lnk->prev = 0;
		free(lnk);
		q->size--;
	}

	else if (q->sentinel->prev == lnk) // link is at the end
	{
		struct DLink* before = lnk->prev;

		before->next = q->sentinel;
		q->sentinel->prev = before;

		lnk->next = 0;
		lnk->prev = 0;

		free(lnk);

		q->size--;
	}

	else
	{
		struct DLink* before = lnk->prev;
		struct DLink* after = lnk->next;

		before->next = after;
		after->prev = before;

		lnk->next = 0;
		lnk->prev = 0;

		free(lnk);

		q->size--;
	}		

	
}

/* Remove the front of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	the front is removed from the deque
*/
void removeFrontCirListDeque (struct cirListDeque *q) 
{
	assert (q != 0);

	if (q->size == 0)
	{
		printf("\nNothing in the list.");
		exit(1);
	}

	_removeLink(q, q->sentinel->next);		 

}


/* Remove the back of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	the back is removed from the deque
*/
void removeBackCirListDeque(struct cirListDeque *q)
{
  	assert (q != 0);

	if (q->size == 0)
	{
		printf("\nNothing in the list.");
		exit(1);
	}

	_removeLink(q, q->sentinel->prev);	 
}

/* De-allocate all links of the deque

	param: 	q		pointer to the deque
	pre:	none
	post:	All links (including Sentinel) are de-allocated
*/
void freeCirListDeque(struct cirListDeque *q)
{
	if (q->size == 0)
	{
		q->sentinel->next = 0;
		q->sentinel->prev = 0;
		free(q->sentinel);
		free(q);
		return;
	}

	struct DLink* temp = q->sentinel;
	struct DLink* before = q->sentinel;

	while (temp->next != q->sentinel)
	{
		temp = temp->next;
		before->next = 0;
		before->prev = 0;
		free(before);
		before = temp;
	}							 
	
	free(q->sentinel);		
}

/* 	Deallocate all the links and the deque itself. 

	param: 	v		pointer to the dynamic array
	pre:	v is not null
	post:	the memory used by v->data is freed
*/
void deleteCirListDeque(struct cirListDeque *q) {
	assert(q != 0);
	freeCirListDeque(q);
	free(q);
}

/* Check whether the deque is empty

	param: 	q		pointer to the deque
	pre:	q is not null
	ret: 	1 if the deque is empty. Otherwise, 0.
*/
int isEmptyCirListDeque(struct cirListDeque *q)
{
	assert(q != 0);

	if (q->sentinel->next == 0)
		return 1;

	else
		return 0;
}

/* Print the links in the deque from front to back

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post: 	the links in the deque are printed from front to back
*/
void printCirListDeque(struct cirListDeque *q)
{
	assert (q != 0);

	if (isEmptyCirListDeque(q) == 1)
	{
		printf("\nERROR: Nothing in the list to print.");
		exit(1);
	}

	struct DLink* temp = q->sentinel->next;
	int counter = 1;

	while (temp != q->sentinel)
	{
		printf("\nPosition %d: %f", counter, temp->value);
		temp = temp->next;
		counter++;
	}
}

/* Reverse the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post: 	the deque is reversed
*/
void reverseCirListDeque(struct cirListDeque *q)
{
	assert (q != 0);

	if (isEmptyCirListDeque(q) == 1)
	{
		printf("\nNothing in the list.");
		exit(1);
	}

	struct DLink* header = q->sentinel;
	struct DLink* next;

	while (next != q->sentinel)
	{
		next = header->next;

		header->next = header->prev;
		header->prev = next;

		header = next;
	}
}
