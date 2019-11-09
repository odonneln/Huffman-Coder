#include "huffman.h"

unsigned char ** codebook(Node * head, int depth)
{
    if (head == NULL) {
        return NULL;
    }
    unsigned char ** book = writeCodes(head);
    //test for NULL ?

    return book;
}

unsigned char ** writeCodes(Node * head) {
    //instead of writing to a file
    //write to an ARRAY OF STRINGS/char arrays
        //would an array of another type work? BITS?
        //how long will a 256 ascii code even get?
        //not more than eight 0's,1's
    unsigned char ** book = calloc(256, sizeof(unsigned char*));
    //char ** book = calloc(256 * sizeof(char*)); //only calloc() for printing
    Node * path = head;
    path->next = NULL; //already by NULL by previous ops but to be safe
    Node * temp;
    int depth = 0;
    while (path != NULL) {
        if (path->left != NULL && path->left->next != path) {
            path->left->next = path;
            path = path->left;
            depth++;
        }
        else if (path->right != NULL && path->right->next != path) {
            path->right->next = path;
            path = path->right;
            depth++;
        }
        else {
            if (path->figure || (!path->left && !path->right && !path->figure)) {
            //if (path->figure) {
                book[path->figure] = malloc((depth + 1) * sizeof(unsigned char));
                book[path->figure][0] = depth;
                temp = path;
                int i = 0;
                while (temp->next != NULL && i < depth) {
                    if (temp == temp->next->left) {
                        book[path->figure][depth - i] = '0';
                    } else {
                        book[path->figure][depth - i] = '1';
                    }
                    temp = temp->next;
                    i++;
                }
                /*
                if (temp != NULL || i < depth) {
                   fprintf(stderr, "MISMATCH OCCURANCE\n");
                   printf("i = %d and depth = %d\n", i, depth);
                }
                //printf("i = %d and depth = %d\n", i, depth);
                printf("%c : ", path->figure);
                for (i = 0; i < depth + 1; i++) {
                    printf("%c", book[path->figure][i]);
                }
                printf("\n");
                */

            }
            path = path->next;
            depth--;
        }
    }
    return book;
}

void freeCodebook(unsigned char ** book) {
    for (int i = 0; i < 256; i++) {
        if (book[i]) {
            free(book[i]);
        }
    }
    free(book);
}

void writeCodes_old(Node * head, unsigned char * path, FILE * outptr)
{
    if (head->left != NULL) {
        path[path[0]] = '0';
        path[0]++;
        writeCodes_old(head->left, path, outptr);
        path[0]--;
    }
    if (head->right != NULL) {
        path[path[0]] = '1';
        path[0]++;
        writeCodes_old(head->right, path, outptr);
        path[0]--;
    }
    else {
        fwrite(&head->figure, sizeof(unsigned char), 1, outptr);
        fwrite(":", sizeof(unsigned char), 1, outptr);
        fwrite(&path[1], sizeof(unsigned char), path[0] - 1, outptr);
        fwrite("\n", sizeof(unsigned char), 1, outptr);
    }
}
