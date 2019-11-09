// main.c

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "huffman.h"

int main(int argc, char ** argv)
{
	if (argc < 3) {
		fprintf(stdout, "not enough inputs\n");
		return EXIT_FAILURE;
	}
	// argv[1] = uncompressed input handle
	// argv[2] = compressed output destination
    
    long * counts = count(argv[1]);
	if (counts == NULL) {
		return EXIT_FAILURE;
	}
	int depth = 0;
	Node * tree = getTree(counts, &depth);
	if (tree == NULL && depth) {
		return EXIT_FAILURE;
	}
    unsigned char ** book = codebook(tree, depth);
    if (book == NULL && depth) {
        clearTree(tree);
		return EXIT_FAILURE;
	}
    if (compress(argv[1], tree, book, argv[2])) {
		clearTree(tree);
		return EXIT_FAILURE;
	}
    free(counts);
	clearTree(tree);
	return EXIT_SUCCESS;
}
