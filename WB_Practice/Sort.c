#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define TYPE double

/* Best Case: already sorted and the algorithm keeps track of whether there are swaps, O(n) 
 * Worst Case: O(n^2), sorted backwards
 * Average Case: O(n^2), random order
 */

void BubbleSort(TYPE* data, int size)
{
	int n;
	int j;

	for (n = size - 1; n > 0; n--)
	{
		for (j = 0; j < n; j++)	
		{
			if (data[j] > data[j + 1])
			{
				TYPE temp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = temp;
			}
		}
	}
}

/* Requires an ordered list.
 * Best Case: Item the first thing found. O(1).
 * Worst Case: Item not found. O(log n).
 * Average Case: Item in list. O(log n).
 */

int BinarySearch(TYPE* data, int size, TYPE lookFor)
{
	int low = 0;
	int high = size;
	int mid;

	while (low < high)
	{
		mid = (low + high) / 2;
		
		if (data[mid] == lookFor)
			return mid;

		else if (data[mid] < lookFor)
			low = mid + 1;

		else
			high = mid;
	}

	return 0;
}

/* Requires no order.
 * Best Case: Item the first thing found. O(1).
 * Worst Case: Item not found. O(n).
 * Average Case: Item found in the middle. O(n/2) or O(n).
 */

int LinearSearch(TYPE* data, int size, TYPE lookFor)
{
	int j;

	for (j = 0; j < size; j++)
	{
		if (data[j] == lookFor)
			return j;
	}

	return 0;
}

/* Best Case: Sorted forwards, O(n)
 * Worst Case: Sorted backwards, O(n^2)
 * Average Case: Sorted randomly, O(n^2)
 */

void insertionSort(TYPE* data, int size)
{
	int k;
	int j;
	TYPE temp;

	for (k = 1; k < size; k++)
	{
		temp = data[k];	
		j = k - 1;

		while ((temp < data[j]) && (j >= 0))
		{
			data[j + 1] = data[j];
			j -= 1;
		}

		data[j + 1] = temp;
	} 
	
}

/* Best Case, Worst Case, Average Case: O(n^2)
 */

void SelectionSort(TYPE* data, int size)
{
	int z;
	int m;
	int spot;

	for (z = 0; z < (size - 1); z++)
	{
		spot = z;

		for (m = z + 1; m < size; m++)
		{
			if (data[spot] > data[m])
				spot = m;
		}

		if (spot != z)
		{
			TYPE temp = data[z];
			data[z] = data[spot];
			data[spot] = temp;
		}
	}
}

/* Shell Sort algorithm's complexity depends on the gap size it uses.
 * Worst case: O(n^2)
 * Best case: O(n log n)
 * Average case: depends
 */

void ShellSort(TYPE* data, int size)
{
	int gap, secondaryCounter, tertiaryCounter, placeHolder;

	for (gap = size; gap /= 2; gap = gap )
	{
		for (secondaryCounter = gap; secondaryCounter < size; secondaryCounter++)
		{
			placeHolder = data[secondaryCounter];
			
			for (tertiaryCounter = secondaryCounter; tertiaryCounter >= gap && placeHolder < data[tertiaryCounter - gap]; tertiaryCounter -= gap)
			{
				data[tertiaryCounter] = data[tertiaryCounter - gap];
			}

			data[tertiaryCounter] = placeHolder;
		}
	}
}

/* Recursive sort algorithm #1: MergeSort.
 * Best case, Worst case, Average case: O(n log n)
 */

void mergeSortInternal(TYPE*, int, int, TYPE*);
void merge(TYPE*, int, int, int, TYPE*);

void mergeSort(TYPE* data, int size)
{
	TYPE* temp = (TYPE*)malloc (size * sizeof(TYPE));
	assert (temp != 0);
	mergeSortInternal(data, 0, size - 1, temp);
	free (temp);
}

void mergeSortInternal(TYPE* data, int low, int high, TYPE* temp)
{
	int i, mid;
	
	if (low >= high) // base case
		return;	

	mid = (low + high) / 2;
	
	mergeSortInternal(data, low, mid, temp); // first recursive call
	mergeSortInternal(data, mid + 1, high, temp); // second recursive call
	
	merge(data, low, mid, high, temp);

	for (i = low; i <= high; i++)
		data[i] = temp[i];

}

void merge(TYPE* data, int low, int mid, int high, TYPE* temp)
{
	int i;
	int sizeFirst = mid - low;
	int sizeSecond = high - (mid + 1);
	// low marks beginning of first half, mid marks end of first half, mid + 1 marks begin of first half,  high marks end of second half.	
	// Initialize first array.
	TYPE* firstArray = malloc(sizeFirst * sizeof(TYPE));
	TYPE* secondArray = malloc(sizeSecond * sizeof(TYPE));	

	for (i = low; i <= mid; i++)
	{	
		firstArray[i] = data[i];
	}	

	for (i = mid + 1; i <= high; i++)
	{
		secondArray[i] = data[i];
	}

	int trackerOne = low;
	int trackerTwo = mid + 1;
	int BoolFirst = 0;
	int BoolSecond = 0;
	int tempNext = low;

	while (BoolFirst == 0 || BoolSecond == 0)
	{
		TYPE tempArr1 = firstArray[trackerOne];
		TYPE tempArr2 = secondArray[trackerTwo];

		if (tempArr1 <= tempArr2)
		{
			temp[tempNext] = tempArr1;
			tempNext++;
			trackerOne++;

			if (trackerOne > mid)
			{
				BoolFirst = 1;

				if (BoolSecond != 1)
				{
					BoolSecond = 1;
				
					for (i = trackerTwo; i <= high; i++)
					{
						temp[tempNext] = secondArray[i];
						tempNext++;
					}
				}		
				
			}
		}

		else 
		{
			temp[tempNext] = tempArr2;
			tempNext++;
			trackerTwo++;

			if (trackerTwo > high)
			{
				BoolSecond = 1;

				if (BoolFirst != 1)
				{
					BoolFirst = 1;
					
					for (i = trackerOne; i <= mid; i++)
					{
						temp[tempNext] = firstArray[i];
						tempNext++;
					}
				}
			}
		}
				
	}

}

/* Recursive sort algorithm #2: QuickSort.
 * Best case: O(n^2)
 * Worst case: O(n log n) with a simple partition or O(n) with three-way partition and equal keys
 * Average case: O(n log n)
 */
	
void quickSortInternal(TYPE*, int, int);
int partition(TYPE*, int, int);

void QuickSort(TYPE* data, int size)
{
	quickSortInternal(data, 0, size - 1);
}

void quickSortInternal(TYPE* data, int low, int high)
{
	if (low >= high)
		return;

	int pivot = partition(data, low, high);
	quickSortInternal(data, low, pivot - 1); // sort data below the pivot
	quickSortInternal(data, pivot + 1, high); // sort data above pivot
}

int partition(TYPE* data, int low, int high)
{
	int pivot = data[high];
	int partitionIndex = low;
	int i;

	for (i = low; i < high; i++)
	{
		if (data[i] <= pivot)
		{
			TYPE temp = data[i];
			data[i] = data[partitionIndex];
			data[partitionIndex] = temp;
			partitionIndex++;
		}
	}
		TYPE temp = data[partitionIndex];
		data[partitionIndex] = data[high];
		data[high] = temp;

		return partitionIndex;
}

void print(TYPE* data, int size)
{
	int p;

	for (p = 0; p < size; p++)
		printf(" %f  ", data[p]);

	printf("\n");
}

int main()
{
	TYPE sortMe[5] = { 5, 4, 3, 2, 1 };
	QuickSort(sortMe, 5);	
	print(sortMe, 5);	 
	return 0;
}



