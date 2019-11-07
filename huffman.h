//
// huffman.h
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
	struct node * next; //for when the forest needs to be a sorted list
	struct node * left; //tree children
	struct node * right;
	unsigned char figure;
	long count;
} Node;

long * count(char * infile);
int codebook(Node * head, char * outfile, int depth);
int compress(char * infile, Node * tree, char * codebook, char * outfile);
void findCode(unsigned char figure, FILE * codebook);
void compressTree(Node * tree, FILE * outptr, unsigned char * byte, int * bit);
void writeBit(unsigned char figure, unsigned char * byte, int * bit, FILE * outptr);
void straddleByte(unsigned char figure, unsigned char currentByte, 
										int * bit, FILE * outptr);
Node * getTree(long * count, int* depth);
Node * createNode(unsigned char figure, long count);
Node * ListInsert(Node * head, Node * newn);
Node * constructTree(Node * listHead);
Node * mergeNodes(Node * left, Node * right);
void printList(Node * head);
//void writeTopology(Node * head, FILE * outptr);
void writeCodes(Node * head, unsigned char * path, FILE * outptr);
//
char ** myWriteCodes(Node * head);
//
void writeLongs(FILE * outptr, long compressed_bytes, long tree_bytes, long uncompressed_bytes);
void tell(FILE * fptr);
void clearTree(Node * node);
