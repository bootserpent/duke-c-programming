#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

unsigned power(unsigned x, unsigned y);
void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  if (power(x, y) != expected_ans) {
    printf("%d ^ %d = %d test failed, isn't equal to %d\n", x, y, power(x, y), expected_ans);
    exit(EXIT_FAILURE);
  }
}

int main() {
  // test case 1
  printf("starting test case 1\n");
  run_check(0, 1, 0);

  // test case 2
  printf("starting test case 2\n");
  run_check(0, 0, 1);

  // test case 3
  printf("starting test case 3\n");
  run_check(2, 3, 8);

  // test case 4
  printf("starting test case 4\n");
  run_check(4, 4, 256);

  // test case 5
  printf("starting test case 5\n");
  run_check(1, 0, 1);

  // test case 6
  printf("starting test case 6\n");
  run_check(-4, -4, 1 / 256);

  // test case 7
  printf("starting test case 7\n");
  run_check(-4, 1, -4);

  // test case 8
  printf("starting test case 8\n");
  run_check(-4, 2, 16);

  return EXIT_SUCCESS;
}
