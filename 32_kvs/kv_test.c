#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "kv.h"

#define NUM_LOOKUPS 6
int main(void) {
  kvarray_t* array = readKVs("test.txt");
  printf("Printing all keys\n\n");
  printKVs(array);
  const char* tests[NUM_LOOKUPS] = { "banana", "grapes", "cantaloupe", "lettuce", "orange", "apple" };
  const char* values[NUM_LOOKUPS] = { "yellow", "purple", "<unknown>", "<unkown>", "orange", "red" };
  for (int i = 0; i < NUM_LOOKUPS; i++) {

    //printf("index = %d, lookupValue('%s')=%s\n", i, tests[i], lookupValue(array, tests[i]));
    // uncomment when lookupValue is done
    if (lookupValue(array, tests[i]) != NULL) {
      assert(strcmp(lookupValue(array, tests[i]), values[i]) == 0);
    }
    else {
      assert(i == 2 || i == 3);
    }
  }
  freeKVs(array);

  return EXIT_SUCCESS;
}
