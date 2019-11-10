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

unsigned char getBit(FILE * fptr, unsigned char * byte, int * digit, long * bytes_read);
unsigned char getChar(FILE * fptr, unsigned char * byte, int * digit, long * bytes_read);
int readByteCounts(FILE * fptr, long * compressed, long * tree, long * uncompressed);
Node * rebuildTree(FILE * fptr, long tree_bytes);
Node * createNode(unsigned char figure);
void clearTree(Node * tree);

// utility
void printBinary(unsigned char);
void preOrder(Node * tree);
void writeTopology(Node * head, FILE * fptr);
