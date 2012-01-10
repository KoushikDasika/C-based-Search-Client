#include <stdio.h>
#include <string.h>
#include "tokenizer.c"

int main(){
	TokenizerT token;
	char string[] = "bubble.trouble";
	char delims[] = ".";
	char *test;
	
	token = TKCreate(delims, string);
	test = TKGetNextToken(token);
	while(test != NULL){
		printf("token is %s", test);
		test = TKGetNextToken(token);
	}
	return 0;
	
}
