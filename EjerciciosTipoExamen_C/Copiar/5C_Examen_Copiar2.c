#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main() {
    char nombre_origen[100];
    char nombre_destino[100];
    
    printf("Introduce el nombre del archivo de origen: ");
    fgets(nombre_origen, 100, stdin);
    nombre_origen[strcspn(nombre_origen, "\n")] = 0;
    
    printf("Introduce el nombre del archivo de destino: ");
    fgets(nombre_destino, 100, stdin);
    nombre_destino[strcspn(nombre_destino, "\n")] = 0;
    
    FILE *source = fopen(nombre_origen, "rb");
    if (source == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    
    FILE *destination = fopen(nombre_destino, "wb");
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

