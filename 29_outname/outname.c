#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "outname.h"

char* computeOutputFileName(const char* inputName) {
  const char* extension = ".count";
  // +1 to make space for '\0'
  size_t sz = strlen(inputName) + strlen(extension) + 1;
  char* outFileName = (char*)malloc (sz * sizeof(char));
  for (int i = 0; i < sz; i++) {
    outFileName[i] = '\0';
  }
  strcpy(outFileName, inputName);
  strcat(outFileName, ".count");
  
  return outFileName;
}

/*
int main(int argc, char** argv) {

  FILE* f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  char* outName = (char*)computeOutputFileName(argv[1]);
  FILE* outFile = fopen(outName, "w+");
  //read from f, write to outFile
  //todo: read contents from f and write all to outFile
  char* line = NULL;
  size_t sz = 5;
  while (getline(&line, &sz, f) >= 0) {
    fprintf(outFile, "%s", line);
  }
  free(line);
  //frees the malloc'd space from computeOutFileName
  free(outName);
  //next two if blocks used to close file handles, also handles errors
  if (fclose(outFile) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
*/
