#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#pragma warning(disable : 4996)
#include "kv.h"
#include "counts.h"
#include "outname.h"

// compute the counts of values that appear in a particular input file
counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  fprintf(stderr, "%s\n", filename);
    // create pointer counts_t struct
    counts_t* c = createCounts();

    // find filename and open
    FILE* f = fopen(filename, "r");
    if (f == NULL) {
        printf("cannot open file: %s\n", filename);
        perror("Could not open file");
        return NULL;
    }

    // use getline to find name (e.g apple, avocado) until eof
    //loop
    char* name = NULL;
    size_t sz = 5;
    while (getline(&name, &sz, f) >= 0) {
        //remove '\n' from each line
        char* nlChar = strchr(name, '\n');
        *nlChar = '\0';
	fprintf(stderr, "%s\n", name);
        char* value = lookupValue(kvPairs, name);
	// put value to counts_t 
        addCount(c, value);
    }
    free(name);
        
    //close f
    if (fclose(f) != 0) {
        perror("Failed to close the input file!");
        return NULL;
    }

    //return counts_t struct created above
  return c;
}



int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
 //read the key/value pairs from the file named by argv[1] (call the result kv)
    kvarray_t* kv = readKVs(argv[1]);

 //count from 2 to argc (call the number you count i)
    for (int i = 2; i < argc; i++) {
        //count the values that appear in the file named by argv[i], using kv as the key/value pair
        //   (call this result c)
        counts_t* c = countFile(argv[i], kv);
        if (c == NULL) {
            return EXIT_FAILURE;
        }
        //compute the output file name from argv[i] (call this outName)
        char* outName = computeOutputFileName(argv[i]);

        //open the file named by outName (call that f)
        FILE* f = fopen(outName, "w");
        if (f == NULL) {
            perror("Could not open file");
            return EXIT_FAILURE;
        }
        
        //print the counts from c into the FILE f
        printCounts(c, f);

        //close f
        if (fclose(f) != 0) {
            perror("Failed to close the input file!");
            return EXIT_FAILURE;
        }

        //free the memory for outName and c
        free(outName);
        freeCounts(c);

    }

 //free the memory for kv
    freeKVs(kv);

  return EXIT_SUCCESS;
}
