#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAXWORDS 10240
#define PRIME_NUM 16777619
#define OFFSET 2166136261u

/*FUNCTIONS FOR SORTED-LISTS*/

int compareInts(void *p1, void *p2)
{
	int i1 = *(int*)p1;
	int i2 = *(int*)p2;

	return i1 - i2;
}

int compareDoubles(void *p1, void *p2)
{
	double d1 = *(double*)p1;
	double d2 = *(double*)p2;

	return (d1 < d2) ? -1 : ((d1 > d2) ? 1 : 0);
}

int compareStrings(void *p1, void *p2)
{
	char *s1 = p1;
	char *s2 = p2;

	return strcmp(s1, s2);
}
typedef int (*CompareFuncT)(void *, void *);



	/*STRUCTS FOR SORTED-LISTS*/

/*This struct is used for sorted-lists*/
struct ListNode_{
 	 void *data;
 	 struct ListNode_* next;
};
typedef struct ListNode_* node; 
 
/*
 * Sorted list type.
 */

struct SortedList
{
	node head;
	CompareFuncT compare;
	int size;
};
typedef struct SortedList* SortedListPtr;


/*
 * Iterator type for user to "walk" through the list item by item, from
 * beginning to end.  You need to fill in the type as part of your implementation.
 */
struct SortedListIterator
{
	SortedListPtr list;
	node currNode;
	
};
typedef struct SortedListIterator* SortedListIteratorPtr;



	/*STRUCTS FOR HASH TABLE*/

/*This struct is used to keep track of the file name
 * and frequency a given word appears in that file
 */
struct fNode {
	char *word;
	int fileNum;
	int numFrequency;
	struct fNode *next;
};
typedef struct fNode* fileNode;


/*This struct is used to build a hashtable in order
 * to keep track of the words in the indexed file
 */
 
struct hashNode_{
	fileNode next;
}table[MAXWORDS];
typedef struct hashNode_* hashNode;


/*STRUCTS FOR HEAP BASED PRIORITY QUEUE*/
/*Struct used to hold the data of the heap nodes*/
struct HeapNode_{
	char *word;
	unsigned int priority;
};
typedef struct HeapNode_* HeapNode;

struct Heap{
	unsigned int maxSize;
	unsigned int currSize;
	HeapNode *Elements;
	
};
typedef struct Heap* PriorityQueue;




#endif
