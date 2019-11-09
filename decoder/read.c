#include <stdio.h>
#include <stdlib.h>

//int readBit(FILE * fptr, unsigned char * bit, unsigned char * byte, int digit);
//get to this later ^

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

