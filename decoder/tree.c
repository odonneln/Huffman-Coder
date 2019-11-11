#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

Node * rebuildTree(FILE * fptr, long tree_bytes)
{
    long bytes_read = 0;
    unsigned char byte;
    int digit = 8; //gets modded to 0 in getBit(), has to be 8 so next byte is read

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
            if (temp == NULL) {
                //make malloc fail on leaf node
                // clear tree or clear stack??
            }
            if (stack->left == NULL) {
                stack->left = temp;
            } else {
                stack->right = temp;
                stack = stack->next;
            }
        } else {
            temp = createNode('\0');
            if (temp == NULL) {
                //make malloc fail on non leaf node
                // clear tree or clear stack??
            }
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
        add in catches here -- remaining stack?
    */
    if (bytes_read != tree_bytes) {
        fprintf(stderr, "unexpected input format\n");
        clearTree(root);
        return NULL;
    }
    
    return root;
}

Node * createNode(unsigned char figure)
{
    Node * node = malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
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
