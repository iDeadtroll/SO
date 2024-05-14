#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Error: %s ingrese origen y destino\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    FILE *source = fopen(argv[1], "rb");
    if (source == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    FILE *destination = fopen(argv[2], "wb");
    if (destination == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    int c;
    while ((c = fgetc(source)) != EOF) {
        fputc(c, destination);
    }
    fclose(source);
    fclose(destination);
    return 0;
}

