#include "huffman.h"

int codebook(Node * head, char * outfile, int depth)
{
	FILE * fptr = fopen(outfile, "w");
	if (fptr == NULL) {
		fprintf(stderr, "unable to open output file in writeCodes()\n");
		return EXIT_FAILURE;
	}
	if (head == NULL) {
		fclose(fptr);
		return EXIT_SUCCESS;
	}
	unsigned char * path = malloc(depth * sizeof(unsigned char));
	if (path == NULL) {
		fprintf(stderr, "malloc fail in codebook()\n");
		fclose(fptr);
		return EXIT_FAILURE;
	}
	path[0] = 1;
	writeCodes(head, path, fptr);

	free(path);
	fclose(fptr);

	return EXIT_SUCCESS;
}

void writeCodes(Node * head, unsigned char * path, FILE * outptr)
{
	if (head->left != NULL) {
		path[path[0]] = '0';
		path[0]++;
		writeCodes(head->left, path, outptr);
		path[0]--;
	}
	if (head->right != NULL) {
		path[path[0]] = '1';
		path[0]++;
		writeCodes(head->right, path, outptr);
		path[0]--;
	}
	else {
		fwrite(&head->figure, sizeof(unsigned char), 1, outptr);
		fwrite(":", sizeof(unsigned char), 1, outptr);
		fwrite(&path[1], sizeof(unsigned char), path[0] - 1, outptr);
		fwrite("\n", sizeof(unsigned char), 1, outptr);
	}
}
