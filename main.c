// main.c

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "huffman.h"

int main(int argc, char ** argv)
{
	if (argc < 4) {
		fprintf(stdout, "not enough inputs\n");
		return EXIT_FAILURE;
	}
	// argv[1] = uncompressed input file
	// argv[2] = tree info (charactar based)
	// argv[3] = codes
	// argv[4] = compressed output
    
    long * counts = count(argv[1]);
	if (counts == NULL) {
		return EXIT_FAILURE;
	}
	int depth = 0;
	Node * tree = getTree(counts, &depth);
	if (tree == NULL && depth) {
		return EXIT_FAILURE;
	}
	if (codebook(tree, argv[2], depth)) {
		clearTree(tree);
		return EXIT_FAILURE;
	}
    if (compress(argv[1], tree, argv[2], argv[3])) {
		clearTree(tree);
		return EXIT_FAILURE;
	}
    free(counts);
	clearTree(tree);
	return EXIT_SUCCESS;
}
