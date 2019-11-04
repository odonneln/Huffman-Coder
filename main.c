// main.c

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "huffman.h"

int main(int argc, char ** argv)
{
	if (argc < 5) {
		fprintf(stdout, "not enough inputs\n");
		return EXIT_FAILURE;
	}
	// argv[1] = uncompressed input file
	// argv[2] = count file
	// argv[3] = tree info (charactar based)
	// argv[4] = codes
	// argv[5] = compressed output

	if (count(argv[1], argv[2])) {
		return EXIT_FAILURE;
	}
	int depth = 0;
	Node * tree = tree_info(argv[2], argv[3], &depth);
	if (tree == NULL && depth) {
		return EXIT_FAILURE;
	}
	if (codebook(tree, argv[4], depth)) {
		clearTree(tree);
		return EXIT_FAILURE;
	}
	if (compress(argv[1], tree, argv[4], argv[5])) {
		clearTree(tree);
		return EXIT_FAILURE;
	}
	clearTree(tree);
	return EXIT_SUCCESS;
}
