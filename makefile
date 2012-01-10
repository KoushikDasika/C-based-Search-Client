######################################
# 
# Author: Koushik Dasika
######################################

COMPILER = gcc
#CCFLAGS  = -ansi

all: search

debug:
	make DEBUG=TRUE

search: search.o
	$(COMPILER) $(CCFLAGS) -o search search.o
search.o: search.c tokenizer.c
	$(COMPILER) $(CCFLAGS) -c search.c search.h tokenizer.c sorted-list.c datastructs.c datastructs.c
	

ifeq ($(DEBUG), TRUE)
 CCFLAGS += -g
endif

clean:
	rm -f search
	rm -f *.o
	make DEBUG=TRUE
