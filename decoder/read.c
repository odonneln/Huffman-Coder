#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

unsigned char getBit(FILE * fptr, unsigned char * byte, int * digit, long * bytes_read)
{
    if (*digit == 8) {
        *bytes_read += fread(byte, sizeof(unsigned char), 1, fptr); //
        *digit = 0;
    }
    unsigned char mask = 1 << (*digit)++;
    return mask & *byte;
}

unsigned char getChar(FILE * fptr, unsigned char * byte, int * digit, long * bytes_read)
{
    if (*digit == 8) {
        *bytes_read += fread(byte, sizeof(unsigned char), 1, fptr);
        return *byte;
    }

    unsigned char figure = 0;
    int offset = *digit;
    while (*digit < 8) {
        figure |= getBit(fptr, byte, digit, bytes_read) >> offset;
    }
    while (*digit != offset) {
        figure |= getBit(fptr, byte, digit, bytes_read) << (8 - offset);
    }
    return figure;
}

int readByteCounts(FILE * fptr, long * tree_ct, long * uncompressed_ct)
{
    long compressed_ct;
    if (!fread(&compressed_ct, sizeof(long), 1, fptr)) {
        return EXIT_FAILURE;
    }
    fseek(fptr, 0, SEEK_END);
    if (ftell(fptr) != compressed_ct) {
        fprintf(stderr, "ERROR: input file length does not match file header\n");
        return EXIT_FAILURE;
    }
    fseek(fptr, sizeof(long), SEEK_SET);
    if (
            !fread(tree_ct, sizeof(long), 1, fptr) || 
            !fread(uncompressed_ct, sizeof(long), 1, fptr) ||
            ftell(fptr) != 3 * sizeof(long)
       ) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
