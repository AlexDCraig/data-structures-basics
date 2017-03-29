#include <stdio.h>
#include <stdlib.h>
#define TYPE double

/* DYNAMIC ARRAY IMPLEMENTATIONS */

struct DynArr // basic dynamic array structure
{
    TYPE* data;
    int size;
    int capacity;
};

void initDynArr(struct DynArr* da, int initialCapacity) // initialize dynamic array
{
    da->capacity = initialCapacity;
    da->size = 0;
    da->data = (TYPE*)malloc(initialCapacity*sizeof(TYPE));
}

void pushDynArray(struct DynArr*, TYPE);

void setCapacityDynArr(struct DynArr* da) // double capacity of dynamic array
{
    int newCap = da->capacity * 2;
    int CURRENT_SIZE = da->size;
    
    TYPE dataHolder[CURRENT_SIZE];

    int k;
    
    for (k = 0; k < CURRENT_SIZE; k++)
        dataHolder[k] = da->data[k];
        
    free(da);
    
    da = (struct DynArr*)malloc(newCap*sizeof(struct DynArr));
    initDynArr(da, newCap);
 
    int r;
   
    for (r = 0; r < CURRENT_SIZE; r++)
        pushDynArray(da, dataHolder[r]);
      
}

void freeDynArr(struct DynArr* da) // delete, free up memory
{
    free(da);
}
    
int sizeDynArr(struct DynArr* da) // return how many elements are currently in the dynamic array
{
    return da->size;
}

double getDynArr(struct DynArr* da, int element) // retrieve value stored at specified element
{
    if (element > da->size || element < 0)
    {
        printf("No such element.\n");
        return 0;
    }
    
    else
        return da->data[element];
}

/* STACK IMPLEMENTATIONS */

void pushDynArray(struct DynArr* da, TYPE val)
{
    int CURRENT_SIZE = da->size;
    
    if (CURRENT_SIZE == da->capacity)
        setCapacityDynArr(da);
    
    da->data[CURRENT_SIZE] = val;
    da->size++;
}

double topDynArray(struct DynArr* da)
{
    int CURRENT_SIZE = da->size;
    
    return da->data[CURRENT_SIZE - 1];
}

int isEmptyDynArray(struct DynArr* da)
{
    if (da->size == 0)
        return 1; // return true
        
    else
        return 0; // return false
}


void popDynArray(struct DynArr* da)
{
    if (isEmptyDynArray(da) == 0)
    {
        int CURRENT_SIZE = da->size;
        int CAP = da->capacity;
        
        TYPE dataHolder[CURRENT_SIZE - 1];
 
	int k;
       
        for (k = 0; k < CURRENT_SIZE - 1; k++)
            dataHolder[k] = da->data[k];
        
        free(da);
        
        da = (struct DynArr*)malloc(CAP*sizeof(struct DynArr));
        initDynArr(da, CAP);
     
	int r;
   
        for (r = 0; r < CURRENT_SIZE - 1; r++)
            {
                pushDynArray(da, dataHolder[r]);
            }
    }
    
    else
        printf("Nothing to pop.\n");
}


int main()
{
  struct DynArr* da = (struct DynArr*)malloc(20*sizeof(*da));
  initDynArr(da, 3);

  pushDynArray(da, 1);
  pushDynArray(da, 2);
  pushDynArray(da, 3);
  pushDynArray(da, 4);
  popDynArray(da);
  popDynArray(da);
  pushDynArray(da, 420);
  pushDynArray(da, 500);
  pushDynArray(da, 550);
  pushDynArray(da, 200);
  printf("%f", topDynArray(da));
  freeDynArr(da);
  return 0;
}

