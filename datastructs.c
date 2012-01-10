#include "datastructs.h"


	/*HASH TABLE METHODS*/
/*This method takes in a string input and returns the string's hash*/
unsigned int hashingfunction(char* pass){
	unsigned int hash = OFFSET;
	char *s = pass;
	while(*s != '\0'){
		hash = hash^*s;
		hash *= PRIME_NUM;
		s++;
	}
	return hash;
}


/*This method creates a fNode with the given parameters
 *and attachs it to the appropriate hash bucket
 */
int addFileNode(hashNode table, char *word, int fNum, int frNum){
	fileNode fl, temp;
	int position;
	char *wordholder;
	
	if((fl = (fileNode)(malloc(sizeof(struct fNode)))) == NULL){
		return -1;
	}
	if((wordholder = (char *)(malloc(sizeof(char)*strlen(word)))) == NULL){
		return -1;
	}

	strncpy(wordholder, word, strlen(word));
	fl->word = wordholder;
	fl->fileNum = fNum;
	fl->numFrequency = frNum;
	
	position = hashingfunction(word)%MAXWORDS;
	
	if(table[position].next == NULL){
		table[position].next = fl;
		return 0;
	}
	else{
		temp = table[position].next;
		while(temp->next != NULL){
			if(temp->next->fileNum < fl->fileNum){
				temp = temp->next;
			}
			else{
				break;
			}
		}
		fl->next = temp->next;
		temp->next = fl;
			
		
		
		return 0;
	}
	return -1; 		
}

/* This method was written to print out the contents of the hash table.
 * It was written purely for testing purposes.
 */
void printtable(hashNode table){
	int i;
	fileNode test;
	for(i = 0; i < MAXWORDS; i++){
		test = table[i].next;
		while(test != NULL){
			printf("the word is %s\n", test->word);
			printf("the hash is %d\n", hashingfunction(test->word)%MAXWORDS);
			
			printf("the file number is %d\n", test->fileNum);
			printf("the frequency is %d\n", test->numFrequency);
			
			test = test->next;
		}
	}
}

/*This method frees all the memory used in the hash table*/
void deallocatetable(hashNode table){
	int i;
	fileNode test, test2;
	hashNode *temp;
	for(i = 0; i < MAXWORDS; i++){
		test = table[i].next;
		while(test!= NULL){
			test2 = test;
			test = test->next;
			free(test2);
		}
		free(test);
		table[i].next = NULL;
		/**/
	}
	/*
	printtable(table);
	for(i = 0; i < MAXWORDS; i++){
		temp = &table[i];
		free(temp);
	}*/
	free(table);
}


/*PRIORITY QUEUE METHODS*/
PriorityQueue PQCreate(int MaximumElements){
	PriorityQueue pq;
	if((pq = (PriorityQueue)(malloc(sizeof(struct Heap)))) == NULL){
		fprintf(stderr, "Error allocating memory for Priority Queue", MAXLINELENGTH);
		return NULL;
	}
	pq->maxSize = MaximumElements;
	pq->currSize = 0;
	if((pq->Elements = (HeapNode*)(MaximumElements)) == NULL){
		fprintf(stderr, "Error allocating memory for Priority Queue elements", MAXLINELENGTH);
		return NULL;
	}
	return pq;
}
void PQInsert(PriorityQueue pq, char *word2){
	HeapNode temp;
	int position;
	
	while(pq->currSize >= pq->maxSize){
		temp = deleteMin(pq);
		free(temp->word);
		free(temp);
	}
		
	position = pq->currSize++;
	while(position > 0 && 1 < (pq->Elements[(position-1)/2]).priority){
		(pq->Elements[position]).priority = (pq->Elements[(position-1)/2]).priority;
		(pq->Elements[position]).word = (pq->Elements[(position-1)/2]).word;
		position = (position-1)/2;
	}
	(pq->Elements[position]).priority = 1;
	(pq->Elements[position]).word = word2;
	return(0);
}
void HeapSort(PriorityQueue pq, int size){
	int i, temp;
	for(i = (size/2); i >= 0; i--){
		siftDown(pq->Elements, i, size-1;
	}
	
}



char* deleteMin(PriorityQueue pq){
	char *minWord;
	int rootWord = 0;
	int pos, newPos, last;
	
	if(pq->currSize == 0){
		return NULL;
	}
	
	minWord = (pq->Elements[0]).word;
	pos = 0;
	
	while(!rootWord){
		if( 2*pos + 2 < pq->currSize ){
			if( (pq->Elements[2*pos+1]).priority < (pq->Elements[2*pos+2]).priority)
				newpos = 2*pos + 1;
			else
				newpos = 2*pos + 2;
			(pq->Elements[pos]).priority = (pq->Elements[newpos]).priority;
			(pq->Elements[pos]).word = (pq->Elements[newpos]).word;
			pos = newpos;
		}
		else if ( 2*pos + 2 == pq->currSize ){
			newpos = 2*pos + 1;
			(pq->Elements[pos]).priority = (pq->Elements[newpos]).priority;
			(pq->Elements[pos]).word = (pq->Elements[newpos]).word;
			pq->currSize -= 1;
			return(minWord);
			/* finished, came out exactly on last element */
		}
		else
			rootWord = 1;
	}
	
	last = --pq->currSize;
	while(pos > 0 && (pq->Elements[last]).priority < (pq->Elements[(pos-1)/2]).priority ){
		(pq->Elements[pos]).priority = (pq->Elements[(pos-1)/2]).priority;
		(pq->Elements[pos]).word = (pq->Elements[(pos-1)/2]).word;
		pos = (pos-1)/2;
	}
	(pq->Elements[pos]).priority = (pq->Elements[last]).priority;
	(pq->Elements[pos]).word = (pq->Elements[last]).word;
	/* filled pos by moving last element in it*/
	return(minWord);
}
		
	
		












