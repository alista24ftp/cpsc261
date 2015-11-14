#include "tree.h"
#include <stdlib.h>
#include "endian.h"

#define TABLESIZE 1000000


struct{
	long id;
	Tree *tree;
} lookupTable[TABLESIZE];

int nEntries = 0;

void rememberId(long id, Tree *tree){
	lookupTable[nEntries].id = id;
	lookupTable[nEntries].tree = tree;
	nEntries++;
}

Tree *findNodeWithId(long id){
	int i;
	for(i=0; i<nEntries; i++){
		if(lookupTable[i].id == id){
			return lookupTable[i].tree;
		}
	}
	return NULL;
}

Tree *readTreeNode(FILE *file, int swap){
	Tree *t;
	t = (Tree *) calloc(1, sizeof(Tree));
	t->value = 0;
	t->left = NULL;
	t->right = NULL;
	
	
	readLong(file, swap, &(t->value));
	readPtr(file, swap, &(t->left));
	readPtr(file, swap, &(t->right));

	return t;
}

Tree *readTree(FILE *file, int swap){
	int i=0;
	long id=0;
	long rootid;
	
	if(!feof(file)){
		readLong(file, swap, &id);
		Tree *t = readTreeNode(file, swap);
		rememberId(id, t);
		rootid = id;
	}else{
		return NULL;
	}
	
	// read all nodes from file
	while (!feof(file)) {
		
		readLong(file, swap, &id); // reads id of node 
		Tree *t = readTreeNode(file, swap); // reads node associated with id read
		
		rememberId(id, t); // save id-node into lookupTable
	}
	
	// unswizzling
	while(i<nEntries){
		long thisid = (long)lookupTable[i].tree->left;
		lookupTable[i].tree->left = findNodeWithId(thisid);
		thisid = (long)lookupTable[i].tree->right;
		lookupTable[i].tree->right = findNodeWithId(thisid);
		i++;
	}
	
	return findNodeWithId(rootid);
}
