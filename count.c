#include "huffman.h"

int count(char * infile, char * outfile)
{
	FILE * fptr = fopen(infile, "r");
	if (!fptr) {
		fprintf(stderr, "unable to open input file to count()\n");
		return EXIT_FAILURE;
	}
	FILE * outptr = fopen(outfile, "w");
	if (!outptr) {	
		fprintf(stderr, "unable to open output file to count()\n");
		fclose(fptr);
		return EXIT_FAILURE;
	}
	//allocate temp array to store char counts
	long * arr = calloc(256, sizeof(long));
	if (arr == NULL) {
		fprintf(stderr, "calloc() fail\n");
		fclose(fptr);
		fclose(outptr);
		return EXIT_FAILURE;
	}

	int i = 0; // may not need this counter
		//could use it to check the whole file was read
	unsigned char figure;
	while (fread(&figure, sizeof(unsigned char), 1, fptr)) {
		i++;
		arr[figure]++;
	}
	
	//write char counts to output file
	fwrite(arr, sizeof(long), 256, outptr);

	fclose(fptr);
	fclose(outptr);
	free(arr);

	return EXIT_SUCCESS;
}
