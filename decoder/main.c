#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

int main(int argc, char ** argv)
{
    if (argc < 3) {
        fprintf(stderr, "not enough inputs\n");
        return EXIT_FAILURE;
    }
    FILE * inptr = fopen(argv[1], "r");
    if (inptr == NULL) {
        fprintf(stderr, "unable to open input file\n");
        return EXIT_FAILURE;
    }
    long tree_bytes;
    long uncompressed_bytes;
    if (readByteCounts(inptr, &tree_bytes, &uncompressed_bytes)) {
        fclose(inptr);
        return EXIT_FAILURE;
    }
    Node * tree = rebuildTree(inptr, tree_bytes);
    if (tree == NULL && tree_bytes) {
        fclose(inptr);
        return EXIT_FAILURE;
    }
    if (decompress(inptr, argv[2], tree, uncompressed_bytes)) {
        clearTree(tree);
        fclose(inptr);
        return EXIT_FAILURE;
    }
    //catches for 3 bytes at the beginning of .hbt
    //especially uncompressed_bytes

    clearTree(tree);
    fclose(inptr);
    return EXIT_SUCCESS;
}
