#include <stdio.h>
#include <stdlib.h>
#include "decode.h"

Node * rebuildTree(FILE * fptr)
{
    /*
    unsigned char byte;
    unsigned char bit;
    int digit; //matters for later when actually reading .hbt
    */
    unsigned char figure;
    Node * root;
    fread(&figure, sizeof(unsigned char), 1, fptr);
    if (figure == '0') {
        root = createNode('\0');
    } else {
        fprintf(stderr, "unexpected first bit value in tree builder\n");
        return NULL;
    }
    Node * stack = root;
    Node * temp;
    while (fread(&figure, sizeof(unsigned char), 1, fptr) && stack) {
        if (figure == '0') {
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
        else if (figure == '1') {
            if (!fread(&figure, sizeof(unsigned char), 1, fptr)) {
                fprintf(stderr, "unexpected--no char after cmd bit == 1\n");
            }
            temp = createNode(figure);
            if (stack->left == NULL) {
                stack->left = temp;
            } else {
                stack->right = temp;
                stack = stack->next;
            }
        }
        else {
            fprintf(stderr, "unexpected charactar\n");
        }
    }
    if (stack != NULL) {
        printf("stack is not null after loop creating tree\n");
    }
    return root;
}

Node * createNode(unsigned char figure)
{
    Node * node = malloc(sizeof(Node));
    node->figure = figure;
    node->right = node->left = node->next = NULL;
    return node;
}
