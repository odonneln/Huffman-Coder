#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

Node * rebuildTree(FILE * fptr, long tree_bytes)
{
    unsigned char byte;
    //unsigned char bit = 0;
    int digit = 0;
    long bytes_read = 0;

    if (getBit(fptr, &byte, &digit, &bytes_read)) {
        fprintf(stderr, "unrecognized format-- first bit of .hbt should be 0\n");
        return NULL;
    }

    unsigned char figure;
    Node * root = createNode('\0');
    Node * stack = root;
    Node * temp;
    int i = 0;
    while (stack) {

        if (getBit(fptr, &byte, &digit, &bytes_read)) {
            figure = getChar(fptr, &byte, &digit, &bytes_read);
            
            //
            printf("got figure : %c\n", figure);
            i++; 
            if (i > 10) { stack = NULL; }
            //

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
        if (figure == 'r') {
            break;
        }
    }

    // make catches better than this
    if (stack != NULL) {
        printf("stack is not null after loop creating tree\n");
    }

    printf("bytes read recorded as : %ld\n", bytes_read);
    printf("ftell() at end = %ld", ftell(fptr));

    return root;
}

Node * createNode(unsigned char figure)
{
    Node * node = malloc(sizeof(Node));
    node->figure = figure;
    node->right = node->left = node->next = NULL;
    return node;
}
