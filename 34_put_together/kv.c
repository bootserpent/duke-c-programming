#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
//#pragma warning(disable : 4996)

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
    *nlChar = '\0';
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


kvpair_t* findKV(char* lineToRead) {
  kvpair_t* pair = (kvpair_t*)malloc(sizeof(kvpair_t));
  char* charPtr = strchr(lineToRead, '=');

  //if no '=' exists in line, return NULL
  if (charPtr == NULL) {
    printf("Cannot discern key from value.");
    return NULL;
  }

  //calculating number of chars after '='
  size_t vLen = strlen(charPtr + 1); // +1 to exclude '=' from value string

  //replacing '=' with '\0' to get key string
  *charPtr = '\0';

  //calculate number of chars before '\0' to get key length
  size_t lineLen = strlen(lineToRead);

  pair->key = (char*)malloc(sizeof(char) * (lineLen + 1)); // +1 for null terminator
  pair->key[lineLen] = '\0';

  pair->value = (char*)malloc(sizeof(char) * (vLen + 1)); // +1 for null terminator
  pair->value[vLen] = '\0';

  strcpy(pair->key, lineToRead);
  strcpy(pair->value, charPtr + 1);

  //printf("key = %s, value = %s\n", pair->key, pair->value);
  return pair;
}



kvarray_t* readKVs(const char* fname) {
  /*
    look for loop @ ./30_sort_lines/sortLines.c:  while ((charReturn = getline(&line,&sz, f)) >= 0)

    In readKVs, you will want to open the file, read the lines of text, split them into
    key/value pairs, add the resulting pairs to an array (hint: realloc it to make it larger
    each time), close the file, and return the kvarray_t * that has your array.

    Remember that you will want to abstract out complex steps into functions (you should
    see at least 2 pieces to naturally pull out into their own functions).
  */

  int lineCount = 0;
  kvarray_t* array = (kvarray_t*)malloc(sizeof(kvarray_t));

  FILE* f;
  if ((f = fopen(fname, "r")) == NULL) {
    perror("Failed to open file");
    return NULL;
  }

  char** lines = getFileLines(f, &lineCount);
  array->kvPairs = (kvpair_t**)malloc(sizeof(kvpair_t*) * lineCount);
  array->length = lineCount;

  fprintf(stderr, "filename: %s\n", fname);
  for (int i = 0; i < lineCount; i++) {
    fprintf(stderr, "%s\n", lines[i]);
    kvpair_t* pair = findKV(lines[i]);
    array->kvPairs[i] = pair;
  }

  freeLines(lines, lineCount);
  if (fclose(f) == EOF) {
    perror("Failed to close file");
    return NULL;
  }
  return array;
}

void freeKVs(kvarray_t* pairs) {
  //free key/values
  for (int i = 0; i < pairs->length; i++) {
    kvpair_t* pair = pairs->kvPairs[i];
    if (pair == NULL) {
      continue;
    }
    free(pair->key);
    free(pair->value);
    free(pairs->kvPairs[i]);
  }
  //free pairs
  free(pairs->kvPairs);
  //free kvPairs array and length
  free(pairs);
}

void printKVs(kvarray_t* pairs) {
  for (int i = 0; i < pairs->length; i++) {
    //checking if current pair is NULL; if it is, the code skips the pair
    if (pairs->kvPairs[i] == NULL) {
      continue;
    }
    printf("key = '%s' value = '%s'\n", pairs->kvPairs[i]->key, pairs->kvPairs[i]->value);
  }
}

char* lookupValue(kvarray_t* pairs, const char* key) {
  /*
    Finally, write the lookupValue function, which takes a kvarray_t * and a char * (string).
    The char * that is passed in represents a key.  This function searches the kvarray_t 
    for a matching key, and if found, returns the corresponding value.  If no match is found,
    this function returns NULL
    */
  for (int i = 0; i < pairs->length; i++) {
    //checking if current pair is NULL; if it is, the code skips the pair
    if (pairs->kvPairs[i] == NULL) {
      continue;
    }

    //cannot use == to compare the strings, this instead compares addresses
    //call strcmp instead to compare actual values
    if (strcmp(pairs->kvPairs[i]->key, key) == 0) {
      return pairs->kvPairs[i]->value;
    }
  }
  return NULL;
}
