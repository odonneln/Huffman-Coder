#include "huffman.h"

int compress(char * infile, Node * tree, char * codefile, char * outfile)
{
	FILE * fptr = fopen(infile, "r");
	if (fptr == NULL) {
		fprintf(stderr, "unable to open uncompressed input in compress()\n");
		return EXIT_FAILURE;
	}
	FILE * codebook = fopen(codefile, "r");
	if (codebook == NULL) {
		fprintf(stderr, "unable to open character codes file in compress()\n");
		fclose(fptr);
		return EXIT_FAILURE;
	}
	FILE * outptr = fopen(outfile, "w+");
	if (outptr == NULL) {
		fprintf(stderr, "unable to open output file in compress()\n");
		fclose(codebook);
		fclose(fptr);
		return EXIT_SUCCESS;
	}

	fseek(outptr, 3 * sizeof(long), SEEK_SET); //for the following long ints
	long compressed_bytes = 0;
	long tree_bytes = 0;
	long uncompressed_bytes = 0;
	unsigned char byte = 0;
	int bit = 0;
    //long bytes_read = 0;
    //long bytes_written = 0;
	
	if (tree != NULL) {
		compressTree(tree, outptr, &byte, &bit);
		fseek(outptr, 1, SEEK_CUR);
	}
	tree_bytes = ftell(outptr) - 3 * sizeof(long);

	// begin writing compressed data
	byte = 0;
	bit = 0;
	unsigned char figure; //buffer for chars and their code bits
	while (fread(&figure, sizeof(unsigned char), 1, fptr))
	{
		uncompressed_bytes++;
		findCode(figure, codebook);
		do {
			if (!fread(&figure, sizeof(unsigned char), 1, codebook)) {
                fprintf(stderr, "fread() failure\n");
            }
			writeBit(figure, &byte, &bit, outptr);
		} while (figure == '1' || figure == '0');
		fseek(codebook, 0, SEEK_SET);
	}
    // test that none of hte fread in the outer while loop failed!
    // ^^

	if (tree != NULL && bit != 8) {
		//demo this with a tree of size 1 etc.// this last byte is an assumption
		fwrite(&byte, sizeof(unsigned char), 1, outptr);
	}
	compressed_bytes = ftell(outptr);
	writeLongs(outptr, compressed_bytes, tree_bytes, uncompressed_bytes);

	fclose(fptr);
	fclose(codebook);
	fclose(outptr);

	return EXIT_SUCCESS;
}

void writeBit(unsigned char figure, unsigned char * byte, int * bit, FILE * outptr)
{
	unsigned char mask;
	if (*bit == 8) {
		fwrite(byte, sizeof(unsigned char), 1, outptr);
		*bit = 0;
		*byte = 0;
	}
	if (figure == '1') {
		mask = 1;
		mask <<= *bit;
		*byte = *byte | mask;
	}
	else if (figure != '0') {
		*bit -= 1; //bit not written to byte
	}
	*bit += 1; //increment bit
}

void compressTree(Node * head, FILE * outptr, unsigned char * byte, int * bit) 
{
	unsigned char mask;
	if (*bit == 8) {
		*bit = 0;
		fwrite(byte, sizeof(*byte), 1, outptr);
		*byte = 0;
	}
	//if (head->left != NULL || head->left != NULL) { //may need to be || head->right
	if (head->left != NULL) { //any parent has both children
		//fwrite("0", sizeof(unsigned char), 1, outptr);
		*bit += 1;
		compressTree(head->left, outptr, byte, bit);
		compressTree(head->right, outptr, byte, bit);
	} else {
		//fwrite("1", sizeof(unsigned char), 1, outptr);
		mask = 1;
		mask <<= *bit;
		*byte = *byte | mask;
		*bit += 1;
		//fwrite(&head->figure, sizeof(unsigned char), 1, outptr);
		*bit += 1; //since straddle byte starts at bit = 1
		straddleByte(head->figure, *byte, bit, outptr);
		//just wrote the straddle bytes, get the later one
		fseek(outptr, -1, SEEK_CUR);
		if (!fread(byte, sizeof(*byte), 1, outptr)) {
            fprintf(stderr, "fread() failure\n");
        }
		fseek(outptr, -1, SEEK_CUR);
	}
	return;
}

void straddleByte(unsigned char figure, unsigned char currentByte, int * bit, FILE * outptr)
{
	if (*bit == 1) {
		fwrite(&figure, sizeof(unsigned char), 1, outptr);
		fseek(outptr, 1, SEEK_CUR);
		*bit -= 1;
		return;
	}
	int B = *bit - 1;

	unsigned char byte1 = figure << (B);
	byte1 = byte1 | currentByte;
	fwrite(&byte1, sizeof(unsigned char), 1, outptr);

	unsigned char byte2 = figure >> (8-B);
	fwrite(&byte2, sizeof(unsigned char), 1, outptr);
	*bit -= 1;
}

void findCode(unsigned char figure, FILE * fptr)
{
	unsigned char buffer;
	do {
		if (!fread(&buffer, sizeof(unsigned char), 1, fptr)) {
			fprintf(stderr, "unable to find charactar in codebook\n");
			return;
		}
	} while (buffer != figure);

	if (!fread(&buffer, sizeof(unsigned char), 1, fptr)) {
        fprintf(stderr, "fread() failure\n");
    }
	if (buffer != ':') {
		if (figure == '\n') {
			fseek(fptr, -1, SEEK_CUR);
			findCode(figure, fptr);
		} else if (figure == '0' || figure == '1' || figure == ':') {
			findCode(figure, fptr);
		} else {
			fprintf(stderr, "unrecognized codebook format\n");
		}
		return;
	}
	if (figure == '\n') {
		if (!fread(&buffer, sizeof(unsigned char), 1, fptr)) {
            fprintf(stderr, "fread() failure\n");
        }
		if (buffer == ':') {
			findCode(figure, fptr);
		} else {
			fseek(fptr, -1, SEEK_CUR);
		}
	}
	return;
}

void tell(FILE * fptr)
{
	fprintf(stdout, "ftell() = %ld\n", ftell(fptr));
	return;
}

void writeLongs(FILE * outptr, long compressed_bytes, long tree_bytes, long uncompressed_bytes)
{
	fseek(outptr, 0, SEEK_SET);
	fwrite(&compressed_bytes, sizeof(long), 1, outptr);
	fwrite(&tree_bytes, sizeof(long), 1, outptr);
	fwrite(&uncompressed_bytes, sizeof(long), 1, outptr);
	return;
}
