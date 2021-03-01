#ifndef __COUNTS_H__
#define __COUNTS_H__
struct _one_count_t {
	const char* name;
	int count;
};
typedef struct _one_count_t one_count_t;

struct _counts_t {
	one_count_t* countArray;
	// itemCount tracks number of unique items in countArray
	int itemCount;
	//size tracks total allocated slots for one_count_t
	int size;
	int unknownCount;
};
typedef struct _counts_t counts_t;

counts_t* createCounts(void);
void addCount(counts_t* c, const char* name);
void printCounts(counts_t* c, FILE* outFile);

void freeCounts(counts_t* c);

#endif
