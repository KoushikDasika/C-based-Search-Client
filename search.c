#include "search.h"
#include "tokenizer.c"
#include "sorted-list.c"
#include"sorted-list.h"
#include "datastructs.c"
#include "datastructs.h"


/*This method takes care of the case where a logical-and search query has only 2 words*/
SortedListPtr twoWords(fileNode fn, fileNode fn2){
	SortedListPtr curr = SLCreate(compareInts);
	
	if(fn == NULL || fn2 == NULL){
		curr = NULL;
		return curr;
	}
	while(fn != NULL && fn2 != NULL){
		if(fn->fileNum < fn2->fileNum){
			fn2 = fn2->next;
		}
		else if(fn->fileNum > fn2->fileNum){
			fn = fn->next;
		}
		else{
			if(SLInsert(curr, (void*)&(fn->fileNum)) == 0){
				printf("Error inserting into answer list");
			}
			fn = fn->next;
			fn2 = fn2->next;
			
		}
	}
	return curr;
}

/*This method is called when the logical-and query has more than 2 words.
 * The first two words are handled by the twowords method, and the additional
 * words are handled by this method */
void multiplewords(SortedListPtr words, SortedListIteratorPtr slip){
	node tempNode;
	int hash, i, count = 0;
	fileNode fn, fn2;
	node thisword, temp;
	
	while((tempNode = SLNextItem(slip)) != NULL){
		hash = (hashingfunction((char*) tempNode->data))%MAXWORDS;
		fn = table[hash].next;
		if(fn == NULL){
			printf("word is null\n");
			return;
		}
		else if (words->head == NULL){
			printf("the answer chain is null\n");
			return;
		}
		while(fn != NULL){
			thisword = words->head;
			while(thisword != NULL){
				if(fn->fileNum == *((int*)(thisword->data))){
					break;
				}
				else if(thisword->next == NULL){
					SLRemove(words, thisword->data);
				}
				thisword = thisword->next;
			}
			fn = fn->next;
		}
	}
	
}

/* takes tokens from the holder
	hashes them, compares the two lists,
	makes a new list that contains objects in both lists*/

void andProtocol(char *string, hashNode table){
	int count = 0, hash, i;
	char *output;
	int *temp;
	fileNode fn, fn2;
	SortedListPtr slp, answer;
	SortedListIteratorPtr slip, answerslip;
	node tempNode, tempNode2, tempNode3;

	
	
	TokenizerT example = TKCreate(" ", string);
	/*checks to make sure that the pointer is valid*/
	if(example == NULL){
		printf("bad");
	}
	
	output = TKGetNextToken(example);
	free(output);
	slp = SLCreate(compareStrings);
	
	while((output = TKGetNextToken(example)) != NULL){
		/*Handles the case where the TKGetNextToken fails*/
		if(output == NULL){
			break;
		}
		/*Handles the empty string case*/
		else if(strlen(output) == 0){
			break;
		}
		/*Prints out each token*/
		else{
			count++;
			if(SLInsert(slp, output) == 0){
				printf("error");
			}
		}
	}
	slip = SLCreateIterator(slp);

	if(count > 1){
		tempNode = SLNextItem(slip);
		hash = (hashingfunction((char*) tempNode->data))%MAXWORDS;
		fn = table[hash].next;
		free(tempNode->data);
		free(tempNode);
		
		tempNode2 = SLNextItem(slip);
		hash = (hashingfunction((char*) tempNode2->data))%MAXWORDS;
		fn2 = table[hash].next;
		free(tempNode2->data);
		free(tempNode2);
		
		
		
		answer = twoWords(fn, fn2);
		if(count > 2){
			multiplewords(answer, slip);
		}
		
		answerslip = SLCreateIterator(answer);
		while((tempNode3 = SLNextItem(answerslip)) != NULL){
			i = *((int*)(tempNode3->data));
			printf("final answer files %d\n", i);
			free(tempNode3);
		}
	}
	/*frees up the space used by the program*/
	SLDestroy(slp);
	SLDestroy(answer);
	SLDestroyIterator(slip);
	SLDestroyIterator(answerslip);
	TKDestroy(example);
	
	
}

void orProtocol(char *string, hashNode table){
	int count = 0, hash, i;
	char *output, *holder;
	int *temp;
	fileNode fn, fn2;
	SortedListPtr slp, answer;
	SortedListIteratorPtr slip, answerslip;
	node tempNode, tempNode2, tempNode3;
	node thisword;
	
	
	TokenizerT example = TKCreate(" ", string);
	/*checks to make sure that the pointer is valid*/
	if(example == NULL){
		printf("bad");
	}
	
	output = TKGetNextToken(example);
	free(output);
	slp = SLCreate(compareStrings);
	
	
	while((output = TKGetNextToken(example)) != NULL){
		/*Handles the case where the TKGetNextToken fails*/
		if(output == NULL){
			break;
		}
		/*Handles the empty string case*/
		else if(strlen(output) == 0){
			break;
		}
		/*Prints out each token*/
		else{
			count++;
			if(SLInsert(slp, output) == 0){
				printf("error");
			}
		}
	}
	slip = SLCreateIterator(slp);
	
	/* prints out the nodes in the sorted-lis
	while((tempNode = SLNextItem(slip)) != NULL){
		holder = (char*)(tempNode->data);
		printf("%s\n", holder);
		free(holder);
	}t*/
	
	
	
	printf("count is %d\n", count);
	
	if(count == 1){
		tempNode = SLNextItem(slip);
		hash = (hashingfunction((char*) tempNode->data))%MAXWORDS;
		printf("hash of 0 is %d\n", hash);
		fn = table[hash].next;
		while(fn != NULL){
			printf("The Files with %s are %d\n", fn->word, fn->fileNum);
			fn = fn-> next;
		}
	}
	else if(count > 1){
		answer = SLCreate(compareInts);
		while((tempNode = SLNextItem(slip)) != NULL){
			hash = (hashingfunction((char*) tempNode->data))%MAXWORDS;
			fn = table[hash].next;
			while(fn != NULL){
				if(SLInsert(answer, (void*)&(fn->fileNum)) == 0){
					printf("Error inserting into answer list");
				}
				fn = fn-> next;
			}
		}
		
		answerslip = SLCreateIterator(answer);
		while((tempNode3 = SLNextItem(answerslip)) != NULL){
			i = *((int*)(tempNode3->data));
			printf("final answer files %d\n", i);
			free(tempNode3->data);
			free(tempNode3);
			
		}
	}
	/*frees up the space used by the program*/
	TKDestroy(example);
	
}



int main(int argc, char **argv){
	FILE *fp;
	char holder[MAXLINELENGTH], word[MAXLINELENGTH], holder2[MAXLINELENGTH];
	int fileNum, freqNum;
	unsigned int hash;
	TokenizerT token;
	char *test;
	
	/* In the event that the input arguments is incorrect */
	if(argc != 2){
		printf("Improper number of inputs\n");
		return -1;
	}
	/*In the event that the input file name is incorrect */
	if ((fp = fopen(argv[1], "r")) == NULL) {
		printf("Can't open file\n");
		return -1;
	}
	
	while(fgets(holder, MAXLINELENGTH, fp) > 0){
		/*The case of adding a new word to the hash table*/
		if(sscanf(holder, "<list> %s", (char *)&word) == 1){
			/*fprintf(stderr, "Failed to parse word from index\n", MAXLINELENGTH);*/ 
		}
		
		/*Adding a file Node to the hash entry*/
		if(sscanf(holder, "%d: %d", &fileNum, &freqNum) == 2){
			if(addFileNode(table, word, fileNum, freqNum) == -1){
				fprintf(stderr, "Failed to parse word from index\n", MAXLINELENGTH);
			}
		}
		
	}


	
	while(1){
		printf("\nsearch> ");
		gets(holder2);
		if(strlen(holder2)> MAXLINELENGTH){
			fprintf(stderr, "Any individual line in a file must be less than %i characters.\n", MAXLINELENGTH);
			return -1;
		}
		
		if(strcmp(holder2, "q") == 0){
			printf("exiting\n");
			break;
		}
		else{
			if(strncmp(holder2, "so", 2) == 0){
				printf("so\n");
				orProtocol(holder2, table);
			}
			else if(strncmp(holder2, "sa", 2) == 0){
				andProtocol(holder2, table);
			}
			else{
				printf("Improper input. Proper input is of the form\n"
					"so <terms>, sa <terms>, or q to quit\n");
			}
		}
	}
	
	
	
	
	/*
	TKDestroy(token);
	deallocatetable(table);
	free(holder);
	free(word);printtable(table);
	free(holder2);
	fclose(fp);*/
	return 0;
}


