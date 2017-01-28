#ifndef arrayList
#define arrayList

typedef int valueType;

typedef enum boolean { FALSE, TRUE } Bool;

typedef struct ArrayList
{
	valueType *pointer;
	int usedSize;
	int capacity;
}ArrayList;

ArrayList arrayListInitialize(int capacity);

void arrayListAdd(ArrayList *l, valueType val);
void arrayListAddIndex(ArrayList *arr, const int index, valueType val);
void arrayListAddAll(ArrayList *arr, ArrayList *arrIn);
void arrayListAddAllIndex(ArrayList *arr, ArrayList *arrIn,
	int index);

Bool isEmpty(ArrayList *arr);
Bool isFull(ArrayList *arr);
void arrayListPrint(ArrayList *arr);
void arrayListClear(ArrayList *arr);
ArrayList arrayListClone(ArrayList *arr);
Bool arrayListContains(ArrayList *arr, valueType val);
Bool arrayListEnsureCapacity(ArrayList *arr, int size);
valueType arrayListGet(ArrayList *arr, const int index);
int arrayListLastIndexOf(ArrayList *arr, valueType val);

valueType arrayListRemove(ArrayList *arr, const  int index);
valueType arrayListRemoveRange(ArrayList *arr, const unsigned int start, const unsigned int end);
void arrayListTrimToSize(ArrayList *arr);
valueType arrayListSet(ArrayList *arr, valueType val, int index);
int arrayListSize(ArrayList *arr);

#endif

