#include <stdio.h>
#include <stdlib.h>

void printBinary(unsigned char);

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

int readByteCounts(FILE * fptr, long * compressed_ct, long * tree_ct, long * uncompressed_ct)
{
    if (!fread(compressed_ct, sizeof(long), 1, fptr)) {
        return EXIT_FAILURE;
    }
    if (!fread(tree_ct, sizeof(long), 1, fptr)) {
        return EXIT_FAILURE;
    }
    if (!fread(uncompressed_ct, sizeof(long), 1, fptr)) {
        return EXIT_FAILURE;
    }
    if (ftell(fptr) != 3 * sizeof(long)) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void printBinary(unsigned char byte) {
    unsigned char figure = 128;
    for (int i = 0; i < 8; i++) {
        printf("%d", (figure & byte) > 0);
        figure >>= 1;
    }
    printf("\n");
}
