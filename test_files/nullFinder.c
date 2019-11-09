#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
    if (argc < 2) {
        fprintf(stdout, "need arguments\n");
        return EXIT_FAILURE;
    }
    FILE * fptr = fopen(argv[1], "r");
    unsigned char figure;
    int line = 0;
    while (fread(&figure, sizeof(char), 1, fptr)) {
        if (figure == '\n') {
            line++;
        }
        if (!figure) {
            fprintf(stdout, "line %d\n", line);
        }
    }
    return EXIT_SUCCESS;
}
