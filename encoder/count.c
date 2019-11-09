#include "huffman.h"

long * count(char * infile)
{
	FILE * fptr = fopen(infile, "r");
	if (!fptr) {
		fprintf(stderr, "unable to open input file to count()\n");
		return NULL;
	}
    /*
	FILE * outptr = fopen(outfile, "w");
	if (!outptr) {	
		fprintf(stderr, "unable to open output file to count()\n");
		fclose(fptr);
		return NULL;
	}
    */
	//allocate array to store char counts
	long * arr = calloc(256, sizeof(long));
	if (arr == NULL) {
		fprintf(stderr, "calloc() fail\n");
		fclose(fptr);
		//fclose(outptr);
		return NULL;
	}

	int i = 0; // ensure whole file is read
	unsigned char figure;
	while (fread(&figure, sizeof(unsigned char), 1, fptr)) {
		i++;
		arr[figure]++;
	}

    fseek(fptr, 0, SEEK_END);
    if (i != ftell(fptr) / sizeof(char)) {
        fprintf(stderr, "fread() failure in count()\n");
        fclose(fptr);
        free(arr);
        return NULL;
    }
    
    /*
	//write char counts to output file
	fwrite(arr, sizeof(long), 256, outptr);
	fclose(outptr);
    */
	fclose(fptr);
	//free(arr);

	return arr;
}
