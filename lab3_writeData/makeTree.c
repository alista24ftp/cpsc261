#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include "tree.h"

Tree *makeTree(int argc, char **argv) {
    Tree *t;
    char *style;
    unsigned long size = 0;
    int i;
    for (i = 0; i < argc; ++i) {
	if ('a' <= argv[i][0] && argv[i][0] <= 'z')
	    style = argv[i];
	else if ('0' <= argv[i][0] && argv[i][0] <= '9')
	    size = strtol(argv[i], 0, 0);
    }

    if (!strcmp("random", style)) {
	t = makeRandomTree(size == 0 ? 20 : size);
    } else if (!strcmp("little", style)) {
	t = makeLittleTree();
    } else if (!strcmp("complete", style)) {
	t = makeCompleteTree(size == 0 ? 6 : size);
    } else {
	fprintf(stderr, "Unrecognized tree style \"%s\"\n", style);
	return NULL;
    }
    return t;
}

Tree *makeCompleteTree(const unsigned long levels)
{
    if (levels <= 0) {
	return NULL;
    }

    Tree *t = malloc (sizeof *t);
    t->value = random() % 1000;
    t->right = makeCompleteTree(levels - 1);
    t->left  = makeCompleteTree(levels - 1);
    return t;
}

Tree *makeRandomTree(unsigned long nNodes)
{  
    if (nNodes == 0)
	return NULL;

    Tree *t = malloc (sizeof *t);
    t->value = random() % 1000;
    nNodes --;
    if (nNodes == 0) {
	t->left = NULL;
	t->right = NULL;
    } else if (random() % 10 == 0) {
	// With one chance in 10, put all the children in the left child
	t->left  = makeRandomTree(nNodes);
	t->right = NULL;
    } else if (random() % 10 == 0) {
	// With one chance in 10, put all the children in the right child
	t->left  = NULL;
	t->right = makeRandomTree(nNodes);
    } else {
	// Randomly choose how many children should be in the left child
	// [ 1 .. nNodes - 1]
	unsigned long inLeft = random() % nNodes;
	unsigned long inRight = nNodes - inLeft;
	t->right = makeRandomTree(inRight);
	t->left  = makeRandomTree(inLeft);
    }
    return t;
}

Tree *makeLittleTree(void) {
   
    Tree *t;

    t = (Tree *) calloc(9, sizeof(Tree));

    t[0].value = 100;
    t[0].left = t+1;  
    t[0].right = t+5;//t+1;  
   
    t[1].value = 101;
    t[1].left = t+2;//t+3;
    t[1].right = t+3;//t+4;

    t[2].value = 102;
    t[2].left = NULL;
    t[2].right = NULL;//t+3;

    t[3].value = 103;
    t[3].left = NULL;//t+1;
    t[3].right = t+4;

    t[4].value = 104;
    t[4].left = NULL;//t+3;
    t[4].right = NULL;//t+5;

    t[5].value = 105;
    t[5].left = t+6;
    t[5].right = NULL;//t+1;

    t[6].value = 106;
    t[6].left = NULL;
    t[6].right = t+7;

    t[7].value = 107;
    t[7].left = t+8;
    t[7].right = NULL;//t+2;

    t[8].value = 108;
    t[8].left = NULL;//t+6;
    t[8].right = NULL;

    return t;
}
