#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

size_t arrayMax(size_t* array, int n);

size_t maxSeq(int* array, size_t n) {
  size_t maxSeqLen = 0;
  if (n == 0) {
    return maxSeqLen;
  }
  size_t *seqArray;
  seqArray = (size_t*)malloc(n * sizeof(size_t));
  for (int i = 0; i < n; i++) {
    seqArray[i] = 0;
  }

  // minimum sequence length is 1
  int seqLen = 1;
  int lV = array[0];
  int arraySlot = 0;
  for (int i = 1; i < n; i++) {
    if (array[i] > lV) {
      lV = array[i];
      // printf("%d\n", seqLen);
      seqLen++;

    }
    else {
      // write seqLen to seqArray, incrementing arraySlot
      seqArray[arraySlot] = seqLen;
      arraySlot++;
      // reset seqLen to 1
      seqLen = 1;
      // reset LV
      lV = array[i];
    }
    if (i == n - 1) {
      seqArray[arraySlot] = seqLen;
    }
  }
  maxSeqLen = arrayMax(seqArray, n);
  return maxSeqLen;
}

size_t arrayMax(size_t* array, int n) {
  if (n == 0) {
    return 0;
  }
  size_t largestValue = array[0];
  size_t indexLargest = 0;
  for (int i = 0; i < n; i++) {
    if (largestValue < array[i]) {
      largestValue = array[i];
      indexLargest = i;
    }
  }
  return array[indexLargest];
}
