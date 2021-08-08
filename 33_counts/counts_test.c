#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "counts.h"

#define NUM_TESTS 16
int main(void) {
    const char* testData[NUM_TESTS] = { "apple", "banana", NULL,"apple",
                                  "frog","sword","bear", NULL,
                                  "frog","apple", "zebra", "knight", "pear",
                                  "duck", "chicken", "cow"};
    counts_t* testCounts = createCounts();
    for (int i = 0; i < NUM_TESTS; i++) {
        addCount(testCounts, testData[i]);
    }
    assert(testCounts->unknownCount == 2);
    assert(testCounts->itemCount == 11);
    assert(testCounts->countArray[5].count == 1);
    assert(strcmp(testCounts->countArray[10].name, "cow") == 0);
    assert(testCounts->countArray[10].count == 1);

    printCounts(testCounts, stdout);
    freeCounts(testCounts);
    return EXIT_SUCCESS;
}
