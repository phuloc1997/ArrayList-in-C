#include <stdio.h>
#include "Arraylist.h"



/**[Check 26/1/2017]Making list

	*ArrayList arrayListInitialize(const unsigned int capacity)

**/

ArrayList arrayListInitialize(int capacity)
{
	ArrayList temp; 
	temp.usedSize = 0;
	temp.capacity = capacity;
	temp.pointer = (valueType*)calloc(capacity, capacity * sizeof(valueType));
	return temp;
}


/***[Check 27/1/2017] Adding

*void arrayListAdd(ArrayList *arr,valueType val) to index || out of bound or less than bound
*void arrayListAddIndex(ArrayList *arr,const unsigned int index,valueType val) to index of list
*void arrayListAddAll(ArrayList *arr, valueType *arrIn, int arrInSize) add all to end of list
*void arrayListAddAllIndex(ArrayList *arr, valueType *arrIn, unsigned const int index, int arrInSize) 
	add all to index of list
***/

void arrayListAdd(ArrayList *arr,valueType val)
{
	if (isFull(arr) == FALSE)
		arr->pointer[arr->usedSize++] = val;
	else if (isFull(arr) == TRUE)
	{
		Bool successAdd=arrayListEnsureCapacity(arr, 1);
		arr->pointer[arr->usedSize++] = val;
		if (successAdd == FALSE)
			puts("Error!");
	}
}

void arrayListAddIndex(ArrayList *arr,const int index,valueType val)
{
	if (index < 0 || index > (arr->usedSize))
		puts("Out of bound index!");
	else
	{
		if (isFull(arr) == TRUE)
			arrayListEnsureCapacity(arr, 1);

			int i = arr->usedSize;
			for (i = arr->usedSize; i >= index; i--)
				arr->pointer[i+1] = arr->pointer[i];

			arr->usedSize++;
			arr->pointer[index] = val;
	}
}

void arrayListAddAll(ArrayList *arr, ArrayList *arrIn)
{
	int i = 0;
	if ((arr->capacity - arr->usedSize) < arrIn->usedSize)
	arrayListEnsureCapacity(arr, arrIn->usedSize);

	for (i = 0; i < arrIn->usedSize; i++)
	{
		arr->pointer[arr->usedSize++] = arrIn->pointer[i];
	}
}

void arrayListAddAllIndex(ArrayList *arr, ArrayList *arrIn,
	int index)
{
	if (index < 0 || index >(arr->usedSize))
		puts("Out of bound index!");
	else
	{
		if ((arr->capacity - arr->usedSize) < arrIn->usedSize)
			arrayListEnsureCapacity(arr, arrIn->usedSize);

		int i = arr->usedSize, j = 0;

		for (i = arr->usedSize; i >= index; i--)
		{
			arr->pointer[i + arrIn->usedSize] = arr->pointer[i];
		}
		

		for (i = index, j = 0; j < arrIn->usedSize; j++)
			arr->pointer[i++] = arrIn->pointer[j];

		arr->usedSize += arrIn->usedSize;
	}
}

/**** [Check on 26/1/2017] Utilities

*Bool isFull(ArrayList *arr) is list full
*void arrayListPrint(ArrayList *arr) print arrayList
*void arrayListClear(ArrayList *arr) clear the entire array to NULL
*ArrayList arrayListClone(ArrayList *arr) clone the input arrayList return a copy
*Bool arrayListContains(ArrayList *arr,valueType val) if the arrayList contains val ? TRUE:FALSE
*Bool arrayListEnsureCapacity(ArrayList *arr, const unsigned int size) ensure the capacity of the input array to size
*valueType arrayListGet(ArrayList *arr, const unsigned int index) return arr[index] 
*int arrayListIndexOf(ArrayList *arr,valueType val) return the index of the first occurence of val if not return -1
*int lastIndexOf(Type val) return the last occurence of the val,if not -1

****/

Bool isEmpty(ArrayList *arr)
{
	return ((arr->usedSize == 0) ? TRUE : FALSE);
}

Bool isFull(ArrayList *arr)
{
	return (arr->usedSize) >= (arr->capacity) ? TRUE : FALSE;
}

void arrayListPrint(ArrayList *arr)
{
	int i = 0;
	printf("%i/%i space%s used\n", arr->usedSize, 
		arr->capacity, (arr->usedSize) > 1 ? "s" : "");
	printf("[");
	for (i = 0; i <  arr->usedSize; i++)
	{
		printf(" %i%s",arr->pointer[i],i<arr->usedSize-1 ? ",":" ");
	}
	printf("]\n");
}

void arrayListClear(ArrayList *arr)
{
	if (isFull(arr) == TRUE)
		return;

	int i = 0;
	for (i = 0; i < arr->usedSize; i++)
		arr->pointer[i] = 0;
	arr->usedSize = 0;
}

ArrayList arrayListClone(ArrayList *arr)
{
	ArrayList arrCopy;
	arrCopy.pointer = (valueType*)calloc(arr->capacity, arr->capacity * sizeof(valueType));
	arrCopy.capacity = arr->capacity;
	arrCopy.usedSize = arr->usedSize;

	int i = 0;
	for (i = 0; i < arr->usedSize; i++)
		arrCopy.pointer[i] = arr->pointer[i];
	return arrCopy;
}

Bool arrayListContains(ArrayList *arr,valueType val)
{
	int i = 0;
	for (i = 0; i < arr->usedSize; i++)
		if (arr->pointer[i] == val)
			return TRUE;
	return FALSE;
}

Bool arrayListEnsureCapacity(ArrayList *arr, int size)
{
	if (size <= 0)
	{
		puts("Invalid list size!");
		return FALSE;
	}

	if ((arr->capacity - arr->usedSize) >= size)
		return TRUE;
	else if ((arr->capacity - arr->usedSize) < size)
	{
		int capcityNeed = size - (arr->capacity - arr->usedSize);

		arr->pointer = (valueType*)realloc
		(arr->pointer, (arr->capacity + capcityNeed) * sizeof(valueType));
		arr->capacity += capcityNeed;
		
		return TRUE;
	}

	return FALSE;
}

valueType arrayListGet(ArrayList *arr, const int index)
{
	if (index<0 || index>arr->usedSize)
	{
		puts("Invalid index!");
		return -1;
	}
	else
	return arr->pointer[index];
}

int arrayListIndexOf(ArrayList *arr,valueType val)
{
	int i = 0;
	for (i = 0; i < arr->usedSize; i++)
		if (arr->pointer[i] == val)
			return i;
	return -1;
}

int arrayListLastIndexOf(ArrayList *arr, valueType val)
{
	int i = 0,lastIndex=-1;
	for (i = 0; i < arr->usedSize; i++)
		if (arr->pointer[i] == val)
			lastIndex = i;
	return lastIndex;
}


/*****[Check 26/1/2017 ] Modifying

*valueType arrayListRemove(ArrayList *arr,const unsigned int index) remove the element in index if invalid index -1
*valueType removeRange(int fromIndex, int toIndex) remove the range,if invalid -1
*valueType set(int index, Object element) Replaces the element at the specified position in this list
*int size(ArrayList arr) return the size
*void trimtoSize(ArrayList arr) trim the excess memory space

******/

valueType arrayListRemove(ArrayList *arr,const  int index)
{
	if (isEmpty(arr) == TRUE)
	{
		puts("List is already empty!");
		return -1;
	}

	if (index < 0 || index > arr->capacity)
	{
		puts("Invalid index!");
		return -1;
	}
	else
	{
		int i = index,valRemoved=arr->pointer[index];
		for (i = index; i < arr->usedSize; i++)
			arr->pointer[i] = arr->pointer[i + 1];

		arr->usedSize -= 1;
		return valRemoved;
	}
}

valueType arrayListRemoveRange(ArrayList *arr, const unsigned int start, const unsigned int end)
{	
	if (isEmpty(arr) == TRUE)
	{
		puts("List is already empty!");
		return -1;
	}

	if (start<0 || end<0 || start>arr->usedSize-1 || end>arr->usedSize-1 || start > end)
	{
		puts("Invalid bounds!");
		return -1;
	}
	else
	{
		
		if (start == end)
			arrayListRemove(arr, start);
		else if (end == arr->usedSize&& start==0)
		{
				arrayListClear(arr);
		}
		else
		{
			if (end == arr->usedSize)
			{
				int i = start;
				for (i = start; i < end; i++)
					arr->pointer[i] = 0;
				arr->usedSize = start ;
			}
			else if(end < arr->usedSize)
			{
				int i = end+1;
				int elementToRemove = (end - start) + 1;//+1 Because of this varible is an index
				for (i = end + 1; i < arr->usedSize; i++)
				{
					arr->pointer[i - elementToRemove] = arr->pointer[i];
				}
				arr->usedSize -= elementToRemove;
			}
		}
	}
}

void arrayListTrimToSize(ArrayList *arr)
{
	if (arr->capacity == arr->usedSize)
		return;
	else
	{
		arr->pointer = (valueType*)realloc(arr->pointer, arr->usedSize * sizeof(valueType));
		arr->capacity = arr->usedSize;
	}
}

valueType arrayListSet(ArrayList *arr, valueType val, int index)
{
	if (index<0 || index>arr->capacity)
	{
		puts("Out of bound index!");
		return -1;
	}

	valueType previousVal = arr->pointer[index];
	arr->pointer[index] = val;
	return previousVal;
}

int arrayListSize(ArrayList *arr)
{
	return arr->capacity;
}