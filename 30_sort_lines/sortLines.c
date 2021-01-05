#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void* vp1, const void* vp2) {
  const char* const* p1 = (const char* const*)vp1;
  const char* const* p2 = (const char* const*)vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char** data, size_t count) {
  qsort(data, count, sizeof(char*), stringOrder);
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
  while ((charReturn = getline(&line,&sz, f)) >= 0) {
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
    for(int j = 0; j < charReturn + 1; j++) {
      lines[lineCount][j] = '\0';
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

void sortFileLines(FILE* f) {
  int lineCount = 0;
  char** lines = getFileLines(f, &lineCount);
  //printf("lineCount = %d\n", lineCount);
  sortData(lines, lineCount);
  for (int i = 0; i < lineCount; i++) {
    printf("%s", lines[i]); 
  }
  freeLines(lines, lineCount);
}
  
int main(int argc, char** argv) {
  if (argc == 1) { // no input file: ./sortLines
    /*your program should read from standard input, sort the lines of input,
      print the results, free memory, and exit successfully. */
    sortFileLines(stdin);
  }
  else { // 1+ input files: ./sortLines t1.txt (or) ./sortLines t1.txt t2.txt
    /*your program should
      treat each argument as an input file name.*/
    for (int i = 1; i < argc; i++) {
      FILE* f = fopen(argv[i], "r");
      if (f == NULL) {
	perror("Can't open specified file");
	return EXIT_FAILURE;
      }
      sortFileLines(f);
      if (fclose(f) != 0) {
	fprintf(stderr, "Can't close specified file: %s\n", argv[i]);
	return EXIT_FAILURE;
      }
    }
    
  }
  return EXIT_SUCCESS;
}

