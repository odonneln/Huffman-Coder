#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

Node * rebuildTree(FILE * fptr, long tree_bytes)
{
    unsigned char byte;
    int digit = 8; //gets modded to 0 in getBit(), has to be 8 so next byte is read
    long bytes_read = 0;

    if (getBit(fptr, &byte, &digit, &bytes_read)) {
        fprintf(stderr, "unrecognized format-- first bit of .hbt should be 0\n");
        return NULL;
    }
    unsigned char figure;
    Node * root = createNode('\0');
    Node * stack = root;
    Node * temp;
    while (stack) {
        if (getBit(fptr, &byte, &digit, &bytes_read)) {

            figure = getChar(fptr, &byte, &digit, &bytes_read);

            temp = createNode(figure);
            if (stack->left == NULL) {
                stack->left = temp;
            } else {
                stack->right = temp;
                stack = stack->next;
            }
        } else {
            temp = createNode('\0');
            if (stack->left == NULL) {
                stack->left = temp;
                temp->next = stack;
            } else {
                stack->right = temp;
                temp->next = stack->next;
            }
            stack = temp;
        }
    }
    /*
    if (stack) {
        printf("\tstack = %p\n", (void*)stack);
    } else {
        printf("stack is NULL\n");
    }
    */
    // make catches better than this
    /*
    if (stack != NULL) {
        //printf("stack is not null after loop creating tree\n");
        printf("stack %p -> %u\n", stack, stack->figure);
        stack = stack->next;
    }

    printf("bytes read recorded as : %ld\n", bytes_read);
    printf("ftell() at end = %ld\n", ftell(fptr));
    */
    return root;
}

Node * createNode(unsigned char figure)
{
    Node * node = malloc(sizeof(Node));
    node->figure = figure;
    node->right = node->left = node->next = NULL;
    return node;
}

void clearTree(Node * n)
{
	if (n == NULL) { return; }
	clearTree(n->left);
	clearTree(n->right);
	free(n);
}
