#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
#pragma warning(disable : 4996)
#define MAX_BUFFER_SIZE 10
#define NOT_FOUND 0

//allocate memory to initialize a pointer to a counts_t struct
counts_t* createCounts(void) {
	counts_t* counts = (counts_t*)malloc(sizeof(counts_t));

	counts->size = MAX_BUFFER_SIZE;
	counts->itemCount = 0;
	counts->countArray = (one_count_t*)malloc(sizeof(one_count_t) * MAX_BUFFER_SIZE);
	counts->unknownCount = 0;

	return counts;
}

//put "name" to counts_t
//uses the name to count the total amount of times it has been seen
void addCount(counts_t* c, const char* name) {
	if (name == NULL) {
		c->unknownCount++;
		return;
	}

	for (int i = 0; i < c->itemCount; i++) {
		// loops through the countArray, checks if names are equal
		//if equal you found the item in countArray
		//if not equal, keep looping
		if (strcmp(c->countArray[i].name, name) == 0) {
			c->countArray[i].count++;
			return;
		}
		
	}

	if (c->itemCount == c->size) {
		//increment size FIRST, must do this or will realloc as same size and overrun buffer
		c->size += MAX_BUFFER_SIZE;
		c->countArray = (one_count_t*)realloc(c->countArray, c->size * sizeof(one_count_t));
		
	}

	// if we haven't returned already, the name is a new item
	c->countArray[c->itemCount].count = 1;
	//allocate space for name string
	//allocate +1 for '\0' so that strcpy will have space to write it into the name field
	c->countArray[c->itemCount].name = (const char*)malloc(sizeof(const char) * strlen(name) + 1);
	//write string to the slot
	c->countArray[c->itemCount].name = (const char*)strcpy((char*)c->countArray[c->itemCount].name, name);

	//only increment after writing newItem to countArray
	//makes sure index is correct
	c->itemCount++;
}

//store counts_t content to a file
//produce formatted output file with all values and keys
void printCounts(counts_t* c, FILE* outFile) {

	for (int i = 0; i < c->itemCount; i++) {
		fprintf(outFile, "%s: %d\n", c->countArray[i].name, c->countArray[i].count);
	}

	if (c->unknownCount > 0) {
		fprintf(outFile, "<unkown> : %d\n", c->unknownCount);
	}
}

//free memory
void freeCounts(counts_t* c) {
	//free name in each slot of c->countArray
	for (int i = 0; i < c->itemCount; i++) {
		free((void*)c->countArray[i].name);
	}
	//free slots in c->countArray
	free(c->countArray);
	//free c
	free(c);

}
