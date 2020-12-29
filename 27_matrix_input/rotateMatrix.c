#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#pragma warning(disable : 4996)
#define EXIT_SUCCESS 0

int** getMatrix(FILE* f) {
  //asserting that file is not fake
  assert(f != NULL);
  //declaring array for 10 columns, malloc for each spot in array:
  int** matrix;
  matrix = (int**)malloc(sizeof(int*) * 10);
  for (int i = 0; i < 10; i++) {
    matrix[i] = (int*)malloc(sizeof(int) * 10);
  }
  int c;
  // i is rows, j is columns
  int i = 0;
  int j = 0;
  while ((c = fgetc(f)) != EOF) {
    matrix[i][j] = c;
    j++;

    if (c == '\n') {
      //newline counted as a character, j = 11 instead of 10
      if (j != 11) {
	fprintf(stderr, "Line is not the expected size: %d. Should be 10 + newline.\n", j);
	return NULL;
      }
      i++;
      j = 0;
    }
  }
  //checking row count, making sure == 10.
  if (i != 10) {
    fprintf(stderr, "Incorrect amount of rows provided: %d. Should be 10 rows.\n", i);
    return NULL;
  }
  //return an array full of values
  return matrix;
}


bool meetRequirements(int** matrix) {
  int c;
  c = matrix[0][0];
  //check dimensions (line length, line amount) to make sure not in invalid place
  //if the file is too short then it will start printing on the next line to make 10x10 and produce strange output
  //notenoughlines.txt somehow increments i over 9



  //make sure the file isn't empty if not null
  if (c == 10) {
    fprintf(stderr, "File is empty or first line is empty. Start matrix at first line. ");
    return false;
  }
  return true;
}



void rotate(int** matrix) {
  char rotatedMatrix[10][10];
  for (int row = 0; row < 10; row++) {
    for (int col = 0; col < 10; col++) {
      rotatedMatrix[col][9 - row] = matrix[row][col];
    }
  }
  for (int row = 0; row < 10; row++) {
    for (int col = 0; col < 10; col++) {
      matrix[row][col] = rotatedMatrix[row][col];
    }
  }
}

int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: rotateMatrix fileName\n");
    return EXIT_FAILURE;
  }
  FILE* f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Can't open specified file");
    return EXIT_FAILURE;
  }
  int** matrix;
  matrix = getMatrix(f);
  if (matrix == NULL) {
    fprintf(stderr, "Failed to retrieve matrix or returned NULL.\n");
    return EXIT_FAILURE;
  }
  bool ret = meetRequirements(matrix);
  if (ret == false) {
    perror("File does not meet requirements");
    return EXIT_FAILURE;
  }
  rotate(matrix);

  for (int row = 0; row < 10; row++) {
    for (int col = 0; col < 10; col++) {
      printf("%c", matrix[row][col]);
    }
    printf("\n");
  }
  //frees contents of each line
  //for (int i = 0; i < 10; i++) {
  //    free(matrix[i]);
  //}
  //frees the line slots
  free(matrix);
  if (fclose(f) != 0) {
    perror("Could not close file\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
