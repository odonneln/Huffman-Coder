#include "huffman.h"

int decompress(FILE * inptr, char * outfile, Node * root, long uncompressed_bytes)
{
    FILE * outptr = fopen(outfile, "w");
    if (outptr == NULL) {
        fprintf(stderr, "unable to open output file\n");
        return EXIT_FAILURE;
    }
    long bytes_read = 0;
    long bytes_written = 0;
    unsigned char byte;
    int digit = 8;
    Node * node = root;
    
    bytes_read = ftell(inptr);
    fseek(inptr, 0, SEEK_END);
    long eof = ftell(inptr);
    fseek(inptr, bytes_read, SEEK_SET);
    //fseek(inptr, bytes_read - eof, SEEK_CUR);
    bytes_read = 0;
    
    while (bytes_written < uncompressed_bytes) {
        if (node->figure || !(node->left || node->right)) {
            //printf("writing char --> %c\n", node->figure);

            bytes_written += fwrite(&node->figure, sizeof(unsigned char), 1, outptr);
            node = root;
        }
        else if (getBit(inptr, &byte, &digit, &bytes_read)) {
            node = node->right;
        } else {
            node = node->left;
        }
    }
    if (ftell(inptr) != eof) {
        fprintf(stderr, "unexpected file length\n");
    }
    /*
    printf("after loop in decompress()\n");
    printf("bytes_written = %ld\n", bytes_written);
    printf("bytes_read = %ld\n", bytes_read);
    printf("uncompressed_bytes = %ld\n", uncompressed_bytes);
    printf("ftell() = %ld\n", ftell(inptr));
    */

    //add in catches here for bytes read, bytes written
    fclose(outptr);

    return EXIT_SUCCESS;
}
