#include <stdlib.h>
#include <stdio.h>

unsigned power(unsigned x, unsigned y) {
  if (x == 0 && y == 1) {
    return 0;
  }
  // base case
  if (y == 0) {
    return 1;
  }
  // x ^ y = (x ^ y - 1) * x, recursively called
  return power(x, y - 1) * x;
}
