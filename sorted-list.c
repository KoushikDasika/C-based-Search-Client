
#include "sorted-list.h"

SortedListPtr SLCreate(CompareFuncT cf){
	SortedListPtr slp;
	
	if((slp = (SortedListPtr)(malloc(sizeof(struct SortedList)))) == NULL){
		return NULL;
	}
	slp->head = NULL;
	slp->compare = cf;
	slp->size = 0;
	return slp;
}

void SLDestroy(SortedListPtr list){
	free(list);
}

int SLInsert(SortedListPtr list, void *newObj){
	node tempNode, currNode;
	
	/*Create and allocate memory for new node*/
	if((tempNode = (node)(malloc(sizeof(struct ListNode_)))) == NULL){
		printf("Failed allocating memory for tempnode\n");
		return 0;
	}
	tempNode->data = newObj;
	tempNode->next = NULL;
	
	/*Case where list is null*/
	if(list == NULL){
		printf("List is NULL\n");
		return 0;
	}
	
	/*insert new node into appropriate spot using compare function*/
	if(list->head == NULL){
		list->head = tempNode;
		list->size++;
		/*printf("Added node to front of list\n");*/
		return 1;
	}
	else{
		/*case where new item is greater than the head of the list*/
		if(list->compare(tempNode->data, list->head->data) < 0){
			tempNode->next = list->head;
			list->head = tempNode;
			list->size++;
			/*printf("node added to head of existing list\n");*/
			return 1;
		}
		/*case where its somewhere in the list thats not the head*/
		else{
			currNode = list->head;
			while(currNode->next != NULL){
				if(list->compare(tempNode->data, currNode->data) > 0){
					currNode = currNode->next;
				}
				else{
					break;
				}
			}
			if(list->compare(tempNode->data, currNode->data) != 0){
				tempNode->next = currNode->next;
				currNode->next = tempNode;
				list->size++;
			}
			/*printf("node added somewhere in list\n");*/
			return 1;
		}
	}
	return 0;
}

int SLRemove(SortedListPtr list, void *newObj){
	node ptr; /*pointer for traversing purpose*/

	/*If the list is empty then there's nothing to remove*/
	if(list == NULL){
		return 0;
	}
	/*If the data in the head matches the argument then make the next node the new head and then remove the
	original head*/
	if(list->head->data == newObj)
	{
		ptr = list->head;
		if(list->head->next == NULL){
			list->head = NULL;
		}
		else{
			list->head = list->head->next;
		}
		free(ptr);
		list->size--;
	}
	/*For all other cases, traverse through the list to find the matching component to remove*/
	ptr = list->head;
	while(ptr != NULL)
	{
		if(ptr->next != NULL && *((int*)(ptr->next->data)) == newObj)
		{
			node tmp = ptr->next;
			ptr->next = ptr->next->next;
			free(tmp);
			list->size--;
			return 1;
		}
		ptr = ptr->next;
	}
	return 0;
}
SortedListIteratorPtr SLCreateIterator(SortedListPtr list){
	SortedListIteratorPtr slip;
	
	/*Case where list is null*/
	if(list == NULL){
		printf("List is NULL\n");
		return NULL;
	}
	
	if((slip = (SortedListIteratorPtr)(malloc(sizeof(struct SortedListIterator)))) == NULL){
		printf("Error allocating memory for SortedListIteratorPointer\n");
		return NULL;
	}
	slip->list = list;
	slip->currNode = list->head;
	return slip;
}
		
void SLDestroyIterator(SortedListIteratorPtr iter){
	free(iter);
}

void *SLNextItem(SortedListIteratorPtr iter){
	/*check for memory allocation and management*/
	node tempNode;
	if(iter == NULL){
		return NULL;
	}
	else if(iter->list == NULL){
		printf("iterators list is null\n");
		return NULL;
	}
	else if(iter->currNode == NULL){
		/*printf("currNode is null\n");*/
		return NULL;
	}
	else{
		tempNode = iter->currNode;
		iter->currNode = iter->currNode->next;
		return tempNode;
	}
}
/*
int main(int argc, char **argv)
{
	
	int i, holder;
	SortedListPtr slp;
	SortedListIteratorPtr slip;
	node tempNode;
	
	int num[] = {5,4,3,2,1};
	
	slp = SLCreate(compareInts);
	for(i = 0; i < 5; i++){
		if(SLInsert(slp,  (void*)&num[i]) == 1){
			printf("successful insertion of %d\n", i);
		}
	}
	printf("blah\n");
	SLRemove(slp, (void*)&num[2]);
	printf("num nodes is %d\n", slp->size);
	
	
	slip = SLCreateIterator(slp);
	while((tempNode = SLNextItem(slip)) != NULL){
		holder = *((int*)(tempNode->data));
		printf("node is %d\n", holder);
	}
	
	
	
	return 0;
	
}
*/