//
// decode.h
//
#include <stdio.h>
#include <stdlib.h>

typedef struct node 
{
    struct node * left;
    struct node * right;
    struct node * next;
    unsigned char figure;
} Node;

int readByteCounts(FILE * fptr, long * compressed, long * tree, long * uncompressed);
Node * rebuildTree(FILE * fptr);
Node * createNode(unsigned char figure);
