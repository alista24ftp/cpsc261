#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include "tree.h"

static void tabTo(int indent) {
    while (indent--) putchar(' ');
}

static void printTree_rec (Tree* t, unsigned long *num, int indent)
{
    if (t == NULL) return;
    tabTo(indent);
    printf("t%lu adr=%p value=%.3ld ", *num, t, t->value);
    printf(" left=%14p ", t->left);
    printf("right=%14p ", t->right);
    ++*num;
    printf("\n");
    if (t->left) 
	printTree_rec(t->left, num, indent + 2);
    if (t->right) 
	printTree_rec(t->right, num, indent + 2);
}

void printTree(Tree *t)
{
    unsigned long num = 0;
    printTree_rec(t, &num, 0);
    printf("  .. number of nodes of Tree t (%p) = %lu \n", t, num);
    return; // end of printTree()
}

static void showTree_rec (Tree* t, int indent)
{
    if (t == NULL) return;
    tabTo(indent);
    printf("%.3ld\n", t->value);
    if (t->left) 
	showTree_rec(t->left, indent + 2);
    if (t->right) 
	showTree_rec(t->right, indent + 2);
}

void showTree(Tree *t)
{
    showTree_rec(t, 0);
}
