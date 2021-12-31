#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "input.h"
#include "future.h"
#include "deck.h"
#pragma warning(disable : 4996)
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

//comment out this during PPE
#include <errno.h>
#include <stdint.h>

// if typedef doesn't exist (msvc, blah)
typedef intptr_t ssize_t;

ssize_t getline(char** lineptr, size_t* n, FILE* stream) {
	size_t pos;
	int c;

	if (lineptr == NULL || stream == NULL || n == NULL) {
		errno = EINVAL;
		return -1;
	}

	c = getc(stream);
	if (c == EOF) {
		return -1;
	}

	if (*lineptr == NULL) {
		*lineptr = (char*)malloc(128);
		if (*lineptr == NULL) {
			return -1;
		}
		*n = 128;
	}

	pos = 0;
	while (c != EOF) {
		if (pos + 1 >= *n) {
			size_t new_size = *n + (*n >> 2);
			if (new_size < 128) {
				new_size = 128;
			}
			char* new_ptr = (char*)realloc(*lineptr, new_size);
			if (new_ptr == NULL) {
				return -1;
			}
			*n = new_size;
			*lineptr = new_ptr;
		}

		((unsigned char*)(*lineptr))[pos++] = c;
		if (c == '\n') {
			break;
		}
		c = getc(stream);
	}

	(*lineptr)[pos] = '\0';
	return pos;
}

void freeLines(char** lines, int lineCount) {
	if (lines == NULL) {
		perror("lines array is already null. You are double-freeing lines");
		return;
	}
	for (int i = 0; i < lineCount; i++) {
		free(lines[i]);
	}
	free(lines);
}

char** getFileLines(FILE* f, int* lineCountPtr) {
	int bufferSize = 10;
	int lineCount = 0;
	//read contents from file handle f and write into a matrix called lines
	char** lines;
	//allocating space for each of the lines in the file, counted in function countLines
	lines = (char**)malloc(sizeof(char*) * bufferSize);

	//getline dynamically allocates space for each line (not all lines same length), ends line with '\0'
	//using getline with NULL to malloc appropriately, writing the lines into the buffer from file handle f
	size_t sz = 5;
	char* line = NULL;
	ssize_t charReturn;
	while ((charReturn = getline(&line, &sz, f)) >= 0) {
		//realloc-ing more memory if there are more lines than previously alloted
		if (lineCount == bufferSize) {
			//+= 20 to bufferSize to be able to handle 20 more lines
			bufferSize += 20;

			char** newLinesPtr = (char**)realloc(lines, bufferSize * sizeof(char*));
			if (newLinesPtr == NULL) {
				freeLines(lines, lineCount);
			}
			//printf("realloc succeeded with buffer size: %d, at lineCount %d\n", bufferSize, lineCount);
			lines = newLinesPtr;
		}
		//printf("%s\n", line);
		// 1 + charReturn for '\0' space
		lines[lineCount] = (char*)malloc((1 + charReturn) * sizeof(char));
		for (int j = 0; j < charReturn + 1; j++) {
			lines[lineCount][j] = '\0';
		}
		//remove '\n' from each line
		char* nlChar = strchr(line, '\n');
		if (nlChar != NULL) {
			*nlChar = '\0';
		}
		strcpy(lines[lineCount], line);
		//as long as we're in the while loop, we were able to fetch '\n', incrementing lineCount
		lineCount++;
	}
	free(line);
	//set lineCountPtr to lineCount
	*lineCountPtr = lineCount;
	//returns fully populated array
	return lines;
}

deck_t* hand_from_string(const char* str, future_cards_t* fc) {
	//"3c 4c ?0 ?1 ?2\0"

	int stringLen = strlen(str) + 1;
	int spaceCount = 0;
	int cardCount = 0;
	

	for (int i = 0; i < stringLen; i++) {
		//detect where spaces are
		if (str[i] == ' ' && i != 0) {
			//count spaces
			spaceCount++;
		}
	}

	if (str[stringLen - 1] == ' ') {
		cardCount = spaceCount;
	}
	else cardCount = spaceCount + 1;

	//allocate hand
	deck_t* hand = (deck_t*)malloc(sizeof(deck_t));
	hand->cards = (card_t**)malloc(sizeof(card_t*) * cardCount);
	for (int i = 0; i < cardCount; i++) {
		hand->cards[i] = (card_t*)malloc(sizeof(card_t));
	}
	hand->n_cards = 0;

	char value = NULL;
	char suit = NULL;
	int lastGapIndex = 0;

	//iterate through string
	for (int i = 0; i < stringLen; i++) {
		//stop at the space or null terminator
		if (str[i] == ' ' || str[i] == '\0') {
			//if the first character is whitespace, do nothing
			if (i == 0) {
				continue;
			}

			if (i - lastGapIndex < 2) {
				printf("no value or character, not enough characters to make a card\n");
				return NULL;
			}

			//if future card (?x) add_empty_card to the deck and update fc
			if (str[i - 2] == '?') {
				char indexChar[2] = { str[i - 1], '\0' };
				int index = atoi(indexChar);
				card_t* emptyCard = add_empty_card(hand);
				add_future_card(fc, index, emptyCard);
			}	

			//if is regular card, add to hand
			else {
				card_t c = card_from_letters(str[i - 2], str[i - 1]);
				add_card_to(hand, c);
			}

		lastGapIndex = i;
		}
	}

	//return deck
	return hand;
}

bool is_line_empty(char* line) {
	bool isEmpty = true;
	//detect empty space like spaces or '\n'
	for (int i = 0; i < strlen(line); i++) {
		if (line[i] != '\0' && line[i] != ' ') {
			isEmpty = false;
			break;
		}
	}
	return isEmpty;
}

deck_t** read_input(FILE* f, size_t* n_hands, future_cards_t* fc) {
	//error handling
	if (f == NULL) {
		fprintf(stderr, "File provided is NULL. Check the inputted filename or use a file that exists.\n");
		return EXIT_FAILURE;
	}

	if (fc == NULL) {
		fprintf(stderr, "future_cards_t pointer cannot be NULL.\n");
		return EXIT_FAILURE;
	}

	if (n_hands == NULL) {
		fprintf(stderr, "Provided n_hands pointer cannot be NULL.\n");
		return EXIT_FAILURE;
	}

	//count and report hands read
	int numLines = 0;
	int numHands = 0;
	char** lines = getFileLines(f, &numLines);

	//counting actual number of hands
	for (int i = 0; i < numLines; i++) {
		//"!" operator switches true result to false, or false to true. 
		//if the line is not empty, it will go into this block
		if (!is_line_empty(lines[i])) {
			numHands++;
		}
	}
	
	*n_hands = numHands;
	//currentHand keeps track of the index that needs to be written to in case of empty lines
	int currentHand = 0;

	deck_t** hands = (deck_t**)malloc(sizeof(deck_t*) * numHands);
	for (int i = 0; i < numLines; i++) {
		//printf("%s\n", lines[i]);
		if (is_line_empty(lines[i])) {
			continue;
		}

		hands[currentHand] = hand_from_string(lines[i], fc);
		if (hands[currentHand]->n_cards < 5) {
			fprintf(stderr, "On line %d: %s\nThere cannot be less than five cards.\n", i + 1, lines[i]);
			return EXIT_FAILURE;
		}
		//we don't increment before line 247 because it would check the next hand (doesn't exist yet)
		currentHand++;
	}

	//free what we malloc'ed
	freeLines(lines, numLines);

	//add_empty_card for future card, add_future_card
	return hands;
}
