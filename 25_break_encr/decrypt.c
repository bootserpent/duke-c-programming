#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#pragma warning(disable : 4996)

//void testCountFreq();
//void testGetE();
char getE(int* freq);
int calcKey(char eEncrypted);
int* countFrequency(FILE* f);
int getMaxFreq(int* freqArray);

//after count frequency & getE, implement decrypt
int decrypt(FILE* f) {
  int c;
  int* freqArray = countFrequency(f);
  // checking the max frequency
  int maxFreq = getMaxFreq(freqArray);
  if (maxFreq <= 1) {
    printf("can't discern 'e' because max frequency is less than or equal to 1.\n");
    return EXIT_FAILURE;
  }
  char eEncrypted = getE(freqArray);
  int key = calcKey(eEncrypted);
  /*
    fseek(f, 0, SEEK_SET);
    
    while((c = fgetc(f)) != EOF) {
        if (isalpha(c)) {
            c = tolower(c);
            c -= 'a';
            if (c == key) {
                // 
                c -= key;
            }
            else {
                c = c + (26 - key);
            }
            c %= 26;
            c += 'a';
        }
        // printf("%c", c);
    }
  */
  printf("%d\n", key);
  free(freqArray);
  return EXIT_SUCCESS;
}

int* countFrequency(FILE* f) {
  int* freqArray;
  freqArray = (int*)malloc(26 * sizeof(int));
  for (int i = 0; i < 26; i++) {
    //squiggly line is fine
    freqArray[i] = 0;
  }
  int c;
  int count = 0;
  while ((c = fgetc(f)) != EOF) {
    count++;
    if (isalpha(c)) {
      c = tolower(c);
      c -= 'a';
      freqArray[c]++;
    }
    /*
        if (count > 529000) {
            break;
	    }*/
  }
  return freqArray;
}

char getE(int* freq) {
  int idx;
  int maxFreq = 0;
  // loop to find greatest char freq and index
  for (int i = 0; i < 26; i++) {
    if (freq[i] > maxFreq) {
      maxFreq = freq[i];
      idx = i;
    }
  }

  return idx + 'a';
}


int calcKey(char eEncrypted) {
  int key;
  if (eEncrypted >= 'e') {
    /*
        ex: if 'e' is encrypted as 'i', then all letters
        are shifted down by result of 'i' - 'e'
    */
    key = eEncrypted - 'e';
  }
  else {
    /*
        ex: if 'e' is encrypted as 'c', then you have to loop 
        around (+26) and stop short by result of 'c' - 'e'
    */
    key = 26 + (eEncrypted - 'e');
  }
  return key;
}

int getMaxFreq(int* freqArray) {
  int maxFreq = 0;
  for (int i = 0; i < 26; i++) {
    if (freqArray[i] > maxFreq) {
      maxFreq = freqArray[i];
    }
  }
  return maxFreq;
}

int main(int argc, char** argv) {
  //testCountFreq();
  //testGetE();
  if (argc != 2) {
    fprintf(stderr, "Usage: breaker inputFileName\n");
    return EXIT_FAILURE;
  }

  FILE* f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  decrypt(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}


void testCountFreq() {
  FILE* f = fopen("test.txt", "r");
  int* cf = countFrequency(f);
  assert(cf[0] == 5);
  for (int i = 1; i < 26; i++) {
    assert(cf[i] == 1);
  }
}

void testGetE() {
  FILE* f = fopen("test.txt", "r");
  int* cf = countFrequency(f);
  char ge = getE(cf);
  assert(ge == 'a');
}
