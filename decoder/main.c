#include <stdio.h>
#include <stdlib.h>
#include "decode.h"

void writeTopology(Node * head, FILE * outptr);
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
    FILE * outptr = fopen(argv[2], "w");
    if (outptr == NULL) {
        fprintf(stderr, "unable to open output file\n");
        fclose(inptr);
        return EXIT_FAILURE;
    }
    /*
    long compressed_bytes;
    long tree_bytes;
    long uncompressed_bytes;
    if (readByteCounts(inptr, &compressed_bytes, &tree_bytes, &uncompressed_bytes)) {
        fclose(inptr);
        return EXIT_FAILURE;
    }
    */

    Node * tree = rebuildTree(inptr);
    writeTopology(tree, outptr);

    fclose(inptr);
    fclose(outptr);
    return EXIT_SUCCESS;
}

// ONLY FOR TESTING PURPOSES
void writeTopology(Node * head, FILE * outptr) {
	if (head->left != NULL) {
		fwrite("0", sizeof(unsigned char), 1, outptr);
		writeTopology(head->left, outptr);
		writeTopology(head->right, outptr);
	} else {
		fwrite("1", sizeof(unsigned char), 1, outptr);
		fwrite(&head->figure, sizeof(unsigned char), 1, outptr);
	}
	return;
}