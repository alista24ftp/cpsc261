#include <stdio.h>

typedef long treevaluetype;

typedef struct Tree
{		
    treevaluetype value; 
    struct Tree *left;
    struct Tree *right;
} Tree; 

// functions to make a Tree
Tree *makeRandomTree (unsigned long nNodes);
Tree *makeCompleteTree (unsigned long levels);
Tree *makeLittleTree (void);
Tree *makeTree(int argc, char **argv);

void printTree (Tree* t); 
void showTree (Tree* t); 
long treeHeight(Tree *t);
long treeNodes(Tree *t);
Tree *readTree(FILE *file, int swap);
Tree *readTreeX(FILE *file, int swap);
Tree *readTreeNode(FILE *file, int swap);

// function to write a tree to a file
void writeTree (FILE *file, Tree* t);
