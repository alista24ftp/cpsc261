#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// Size of a cache data block
#define LOG2BLOCKSIZE 2 //2
#define BLOCKSIZE (1 << LOG2BLOCKSIZE)

// N is the number of lines in a set (N-way set associative)
#define LOG2N 3 //3
#define N (1 << LOG2N)

// NSETS is the number of sets in the cache
#define LOG2NSETS 2 //2
#define NSETS (1 << LOG2NSETS)

// ADDRESSWIDTH is the number of bits in an address
#define ADDRESSWIDTH 8 //8

#define VERBOSE 0

// A cache line:  a block plus control information.
// Note that the LRU implementation in this cache in unrealistic
// in that it assumes that we have enough bits to hold the time
// of every access
typedef struct {
    int valid;
    long tag;
    long lastUsedOrder;
    char block[BLOCKSIZE];     // We aren't actually using this since we don't simulate actual reads and writes
} CacheLine;

// A cache set, nothing but an indexed collection (array) of lines
typedef struct {
    CacheLine *lines[N];
} CacheSet;

// A cache, nothing but an indexed collection (array) of sets
typedef struct {
    CacheSet *sets[NSETS];
} Cache;

Cache *cache;

static void die(char *message, int a, int b) {
    	//printf("error\n");
	fprintf(stderr, message, a, b);
	abort();
}

static void showSet(long setindex) {
    int i;
    for (i = 0; i < N; ++i) {
	CacheLine *line = cache->sets[setindex]->lines[i];
	printf("line[%d]: valid = %d, lastUsed = %ld, tag = %ld\n", i, line->valid, line->lastUsedOrder, line->tag);
    }
}

// Check that the lines in the indicated set have reasonable values for
// their lastUsedOrder fields.
void checkValidLastUsedOrder(setindex) {
    int lastUsed[N], i, invalidLines = 0;
    for (i = 0; i < N; ++i) {
	lastUsed[i] = -1;
    }
    for (i = 0; i < N; ++i) {
	CacheLine *line = cache->sets[setindex]->lines[i];
	if (line->valid) {
	    int lu = line->lastUsedOrder;
	    if (lastUsed[lu] != -1) {
		showSet(setindex);
		
		die("Duplicate lastUsed at index %d value %d", i, lu);
	    }
	    lastUsed[lu] = 1;
	} else {
	    invalidLines++;
	}
    }
    for (i = 0; i < N; ++i) {
	if (i < N - invalidLines) {
	    if (lastUsed[i] != 1) {
		showSet(setindex);
		
		die("No line has lastUsed value of %d", i, i);
	    }
	} else {
	    if (lastUsed[i] != -1) {
		showSet(setindex);
		printf("error\n");//
		die("lastUsedOrder too large, expected 0..%d, found %d", N - invalidLines - 1, i);
	    }
	}
    }
}

// Return the tag from the address.  
long tagFromAddress(long address) {
    return address >> (LOG2BLOCKSIZE + LOG2NSETS);
}

// Return the set index from the address.  This function extracts
// the set index bits of the address, and shifts them so that they
// can be used to index into the array of sets in the cache.
long setindexFromAddress(long address) {
    return (address >> LOG2BLOCKSIZE) & ((1 << LOG2NSETS) - 1);
}

// Update the last used ordering for the given set, identified by setIndex.
// The line corresponding to the given tag has just been used so it should
// have a lastUsedOrder of 0.  If this line didn't already have a
// lastUsedOrder of 0, then all of the other valid lines in this set whose
// lastUsedOrder is less than the old value of lastUsedOrder for this line should 
// their lastUsedOrder incremented by 1.
//
// When this function returns, the valid lines in the set should have each
// have a different lastUsedOrder value, and they should all be in the range
// of 0 .. NValidLines - 1.  
void updateLastUsedOrder(long setindex, long tag) {
	long i;
	long linenum;
	
	long oldlru;
	
	for(i=0; i < N; i++){
		
		if(cache->sets[setindex]->lines[i]->tag == tag){
			linenum = i;
			break;
		}		
		
	}
	
	oldlru = cache->sets[setindex]->lines[linenum]->lastUsedOrder;
	cache->sets[setindex]->lines[linenum]->lastUsedOrder = 0;
	cache->sets[setindex]->lines[linenum]->valid = 1;
	for(i=0; i<N; i++){
		
		if(i != linenum){
			if(cache->sets[setindex]->lines[i]->valid && cache->sets[setindex]->lines[i]->lastUsedOrder < oldlru){
				cache->sets[setindex]->lines[i]->lastUsedOrder++;
			}
		}
	}
	
	
	//cache->sets[setindex]->lines[linenum]->lastUsedOrder = 0;//
	
	checkValidLastUsedOrder(setindex);
	
}

// Return the index of the line in the set identified by the given setindex
// that has been least recently used (LRU).  If any line in the set is invalid,
// then return the index of that line.  If all lines are valid, then return the 
// index of the line with the largest lastUsedOrder field (which should always
// be 7 if your implementation of updateTimeOfUse function is correct.
long lruLineInSet(long setindex) {
	long lineindex = 0;
	long i;
	long largest = 0;
	CacheLine *testline;
	for(i=0; i<N; i++){
		testline = cache->sets[setindex]->lines[i];
		if(!testline->valid){
			return i;
		}
		if(testline->lastUsedOrder > largest){
			largest = testline->lastUsedOrder;
			lineindex = i;
		}
		
	}
	
	return lineindex;
}

// If the indicated tag is in one of the cache lines in the set identified
// by setindex, then return the index of that line.  Return -1 otherwise.
long inSet(long setindex, long tag) {
	//CacheLine *line; 
	long i;
	for(i=0; i < N; i++){
		if(cache->sets[setindex]->lines[i]->tag == tag){
			return i;
		}		
	}	
	return -1;
}

// Add the given tag to the given set.  This function must first identify which
// line in the set is least recently used (the lruLineInSet() function determines
// this).  Then it updates that cache line to record that it is valid, that is 
// contains this tag, and that the line has been accessed most recently.
// This function must return the index of the line in the set that has been updated.
long addToSet(long setindex, long tag) {
    long lineindex = lruLineInSet(setindex);
	cache->sets[setindex]->lines[lineindex]->valid = 1;
	cache->sets[setindex]->lines[lineindex]->tag = tag;
	updateLastUsedOrder(setindex, tag);
	
    return lineindex;
}

// Allocate and initialize the cache structures.  This function is complete.
void initCache() {
    long setindex, lineindex;
    cache = malloc(sizeof(Cache));
    
    for (setindex = 0; setindex < NSETS; ++setindex) {
		CacheSet *set = malloc(sizeof(CacheSet));
		cache->sets[setindex] = set;
		for (lineindex = 0; lineindex < N; ++lineindex) {
			CacheLine *line = malloc(sizeof(CacheLine));
			line->valid = 0;
			line->lastUsedOrder = N;
			set->lines[lineindex] = line;
		}
    }
    printf("The cache has %d sets, each with %d lines, total size = %d bytes\n",
	   NSETS, N, NSETS * N * BLOCKSIZE);
}

// Read the sequence of addresses and simulate the cache.  This function is complete
// except that it calls a number of functions that are not.
int main(int argc, char **argv) {
    int i = 0;
    long addr, setindex, tag, now = 0, line;
    long accesses = 0, hits = 0;
    long lineindex;
	
    srandom(time(0));
    initCache();
    while (!feof(stdin)) {
	if (1 != scanf("%lx", &addr))
	    break;
	accesses ++;
	setindex = setindexFromAddress(addr);
	tag = tagFromAddress(addr);
	if ((line = inSet(setindex, tag)) >= 0) {
	    hits ++;
	    if (VERBOSE) printf("0x%06lx:  Hit in line %ld in set %ld\n", addr, line, setindex);
	    updateLastUsedOrder(setindex, tag);
	} else {
	    line = addToSet(setindex, tag);
	    if (VERBOSE) printf("0x%06lx:  Replaced line %ld in set %ld\n", addr, line, setindex);
	}
	++i;
	++now;
    }

    /*
    printf("%ld\n", tagFromAddress(202));
    printf("%ld\n", setindexFromAddress(202));
    updateLastUsedOrder(setindexFromAddress(202), tagFromAddress(202));
    printf("%ld\n", lruLineInSet(setindexFromAddress(202)));
    printf("%ld\n", inSet(setindexFromAddress(202), tagFromAddress(202)));
    */
    printf("%ld hits in %ld accesses; hit rate = %5.2f%%\n",
	   hits, accesses, (double) hits / accesses * 100.0);
	
	// free malloc'd pointers
	for(setindex = 0; setindex < NSETS; ++setindex){
		for(lineindex = 0; lineindex < N; ++lineindex){
			free(cache->sets[setindex]->lines[lineindex]);
		}
		free(cache->sets[setindex]);
	}
	free(cache);
}
