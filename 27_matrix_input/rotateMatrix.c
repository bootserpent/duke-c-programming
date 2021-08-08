#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
//#pragma warning(disable : 4996)
#define EXIT_SUCCESS 0

void freeMatrix(int** matrix);

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
    if (c != '\n') {
      if (j > 9 || i > 9) {
	fprintf(stderr, "Line is not the expected size: %d. Should be 10 (no newline)\n", j + 1);
	fprintf(stderr, "Alternatively, your file may be writing outside of the 10 allocated rows because it has too many lines\n");
	freeMatrix(matrix);
	return NULL;
      }
      matrix[i][j] = c;
      j++;
    }
    if (c == '\n') {
      //newline not counted as character, columns = 10 instead of 11
      if (j != 10) {
	fprintf(stderr, "Line is not the expected size: %d. Should be 10 (no newline)\n", j);
	freeMatrix(matrix);
	return NULL;
      }
      i++;
      j = 0;
    }
  }
  //checking row count, making sure == 10.
  if (i != 10) {
    fprintf(stderr, "Incorrect amount of rows provided: %d. Should be 10 rows.\n", i);
    freeMatrix(matrix);
    return NULL;
  }
  //return an array full of values
  return matrix;
}


int meetRequirements(int** matrix) {
  int c;
  c = matrix[0][0];
  //check dimensions (line length, line amount) to make sure not in invalid place
  //if the file is too short then it will start printing on the next line to make 10x10 and produce strange output
  //notenoughlines.txt somehow increments i over 9



  //make sure the file isn't empty if not null
  if (c == 10) {
    fprintf(stderr, "File is empty or first line is empty. Start matrix at first line. ");
    freeMatrix(matrix);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
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

void freeMatrix(int** matrix) {
  if (matrix == NULL) {
    return;
  }
  //frees contents of each line
  for (int i = 0; i < 10; i++) {
    free(matrix[i]);
  }
  //frees the line slots
  free(matrix);
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
    if (fclose(f) != 0) {
      perror("Could not close file\n");
      return EXIT_FAILURE;
    }
    return EXIT_FAILURE;
  }
  int ret = meetRequirements(matrix);
  if (ret == EXIT_FAILURE) {
    perror("File does not meet requirements");
    if (fclose(f) != 0) {
      perror("Could not close file\n");
      return EXIT_FAILURE;
    }
    return EXIT_FAILURE;
  }
  rotate(matrix);

  for (int row = 0; row < 10; row++) {
    for (int col = 0; col < 10; col++) {
      printf("%c", matrix[row][col]);
    }
    printf("\n");
  }
  freeMatrix(matrix);
  if (fclose(f) != 0) {
    perror("Could not close file\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
