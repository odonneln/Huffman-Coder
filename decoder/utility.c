#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

void printBinary(unsigned char byte) {
    unsigned char figure = 128;
    for (int i = 0; i < 8; i++) {
        printf("%d", (figure & byte) > 0);
        figure >>= 1;
    }
    printf("\n");
}

void preOrder(Node * tree) {
    if (!tree) {
        return;
    }
    if (tree->left) {
        preOrder(tree->left);
    }
}

void writeTopology(Node * head, FILE * outptr) {
	if (head->left != NULL || head->left != NULL) {
	//if (head->left != NULL || head->right != NULL) {      //
		fwrite("0", sizeof(unsigned char), 1, outptr);
		writeTopology(head->left, outptr);
		writeTopology(head->right, outptr);
	} else {
		fwrite("1", sizeof(unsigned char), 1, outptr);
		fwrite(&head->figure, sizeof(unsigned char), 1, outptr);
	}
	return;
}
