/*
 * tokenizer.c
 */

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */
 
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 
struct TokenizerT_ {
	/*Pointers to the strings that will be used to return tokens*/
	char *tokens;
	char *delims;
	
	/*integers that hold the lengths of each of the above strings*/
	int lengthofts;
	int lengthofseps;
	
	/*Keeps track of the position in the token stream that still needs to be tokenized*/
	int index;
};
typedef struct TokenizerT_* TokenizerT;


/*
 * TKCreate creates a new TokenizerT object for a given set of separator characters (given as a string)
 * and a token stream (given as a string).
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT TKCreate(char *seperators, char *ts) {
	/*These take in the input from the command prompt
	*And make a copy that can be used for the TokenizerT struct
	*/
	char *seperatorscopy = malloc(strlen(seperators));
	char *tscopy = malloc(strlen(ts));
	strncpy(seperatorscopy, seperators, strlen(seperators));
	strncpy(tscopy, ts, strlen(ts));
	
	/*Our pointer to our TokenizerT_ struct*/
	TokenizerT tokenptr;
	
	/*Allocates the necessary amount of space for the TokenizerT_ struct that will be used
	And assigns it to the TokenizerT pointer tokenptr
	Also checks to make sure that the memory allocation was successful
	*/
	if((tokenptr = (TokenizerT) malloc(sizeof(struct TokenizerT_))) == NULL){
		return NULL;
	}
		
	
	/*Links the strings that was copied earlier to the struct tokenptr is pointing to*/
	tokenptr -> tokens = tscopy;
	tokenptr -> delims = seperatorscopy;
	
	/*Initial position of our tokenstream*/
	tokenptr -> index = 0;
	
	/*Assigns the values of the strings*/
	tokenptr -> lengthofseps = (strlen(seperators));
	tokenptr -> lengthofts = (strlen(ts));
	
	/*Does the rest of the magic*/
	return tokenptr;
    

}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all memory dynamically allocated
 * in TKCreate as part of creating a new TokenizerT object.  (It should not free the token stream
 * given as the argument to TKCreate.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy(TokenizerT tk) {
	/*Frees the space that was allocated in the initializer for the two strings*/
	free(tk-> tokens);
	free(tk-> delims);
	/*Frees the rest of the struct*/
	free(tk);
}

/* This function takes in a character, the string of deliminators and the length of that string as an integer
 * And outputs 1 if the character is in the string of deliminators and a O if the character is not
*/
int compareChartoDelims(char c, TokenizerT tk){
	/*An integer used for counting...hence called counter*/
	int counter;
	
	/* A loop that goes through each item in the deliminators string that was 
	*  Passed by reference to this function and checks to see if any of the elements
	*  In the deliminators string match the character that was passed in.
	*  The reason why I chose to return 0 or 1 is because C does not have booleans.
	*/
	
	for(counter = 0; counter < tk->lengthofseps; counter++){
		if(c == tk->delims[counter]){
			return 1;
		}
	}
	return 0;
}



/*
 * TKGetNextToken returns the next token from the token stream as a character string.
 * Space for the returned token should be dynamically allocated.  Caller is
 * responsible for freeing the space once it is no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken(TokenizerT tk) {
	/*A pointer that will be used to point to the token string that will be returned*/
	char *token;
	
	/*Another integer that counts*/
	int counter = 0;
	
	/* Allocates memory to the string that will be output 
	 * And checks to make sure that the allocation is successful
	 */
	if((token = malloc(tk->lengthofts)) == NULL){
		return NULL;
	}
	
	/* This loop starts from the position of the tokenstream stream that is yet to be tokenized
	 * And for each letter in the index calls the CompareChartoDelims function.
	 * If the current character is not in the deliminator string, then it is copied to the output string.
	 * If it is in the deliminators string, then the index position is incremented for the next 
	 * TKGetNextToken call, the loop is broken, '\0' is assigned to the end of the string, and it is returned.
	*/
	while((tk->index) < (tk->lengthofts)){
		if(compareChartoDelims((*tk).tokens[(*tk).index], tk) != 1){
			token[counter] = tk->tokens[(*tk).index];
			(*tk).index++;
			counter++;
		}
		else{
			(*tk).index++;
			/* The counter checks to see if its greater than 0, because the tokenstream starts with quotes.
			 * This makes sure that the loop doesn't stop at the first element of the tokenstream.
			 */
			if(counter > 0){
				break;
			}
		}
	}
	token[counter] = '\0';
	return token;
}

/*
 * You should use main to write code that will test your tokenizer implementation.
 * You may define a number of test strings in this file as test cases.
 */

 
 /* The program takes in 2 arguments from the command prompt (not including the call to the program itself).
  * The first string serves as the delimiters and the second string is the tokenstream
 *//*
int main(int argc, char **argv) {
	Pointer to the output string
	char *output;
	
	TokenizerT example = TKCreate(argv[1], argv[2]);
	/*checks to make sure that the pointer is valid
	if(example == NULL){
		return -1;
	}
	while(1){
		output = TKGetNextToken(example);
		
		/*Handles the case where the TKGetNextToken fails
		if(output == NULL){
			return -1;
		}
		/*Handles the empty string case
		if(strlen(output) == 0){
			return 0;
		}
		/*Prints out each token
		printf("\"%s\"\n", output);
		free(output);
	}
	/*frees up the space used by the program
	TKDestroy(example);
	return 0;
	
	
}*/

