#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define EXIT_SUCCESS 0

void rotate(char matrix[10][10]) {
  char rotatedMatrix[10][10];
  for (int row = 0; row < 10; row++) {
    for (int col = 0; col < 10; col++) {
      rotatedMatrix[col][9 - row] = matrix[row][col];
    }
  }
  for (int row = 0; row < 10; row++) {
    for (int col = 0; col < 10; col++) {
      printf("%c", rotatedMatrix[row][col]);
    }
    printf("\n");
  }
}
