#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

size_t maxSeq(int* array, size_t n);

int main() {

  int array1[] = { 1, 2, 1, 3, 5, 7, 2, 4, 6, 9 };

  size_t max_n = maxSeq(array1, 10);
  if (max_n != 4) {
    printf("(test 1) returned %ld, test failed\n", max_n);
    return EXIT_FAILURE;
  }
  // test case 2

  int array2[] = {10};
  max_n = maxSeq(array2, 0);
  if (max_n != 0) {
    printf("returned %ld, test failed\n", max_n);
    return EXIT_FAILURE;
  }

  //test 3
  int array3[] = { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 };
  max_n = maxSeq(array3, 10);
  if (max_n != 1) {
    printf("(test 3) returned %ld, test failed\n", max_n);
    return EXIT_FAILURE;
  }

  //test 4
  int array4[] = { 4, 3, 2, 1, 0, -1, -2, -3, -4, -5};
  printf("starting test 4\n");
  max_n = maxSeq(array4, 10);
  if (max_n != 1) {
    printf("(test 4) returned %ld, test failed\n", max_n);
    return EXIT_FAILURE;
  }

  //test 5
  int array5[] = { 2, 4, 67, 93, 94, 102 };
  printf("starting test 5\n");
  max_n = maxSeq(array5, 6);
  if (max_n != 6) {
    printf("(test 5) returned %ld, test failed\n", max_n);
    return EXIT_FAILURE;
  }
  printf("test passed\n");
  return EXIT_SUCCESS;
}
