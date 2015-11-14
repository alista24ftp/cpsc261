#include "tree.h"
#include "endian.h"
#include <stdlib.h>

void writeTreeNode(FILE *file, Tree *t){
	writeLong(file, t->value);
	writeLong(file, (long)t->left); // save the pointer to the left-node as an id
	writeLong(file, (long)t->right); // save the pointer to the right-node as an id
}

void writeTree(FILE *file, Tree *t){
	if(t == NULL) return;
	
	writeLong(file, (long)t); // first write the id of this node
	writeTreeNode(file, t); // write the node 
	writeTree(file, t->left); // recursively write the left subtree
	writeTree(file, t->right); // recursively write the right subtree
}