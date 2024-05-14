#include <stdio.h>
#include <string.h>

int main() {
    FILE *fp;
    char texto[100];
    char filename[100];
    
    printf("Indique el nombre del archivo: ");
    fgets(filename,100,stdin);
    filename[strcspn(filename, "\n")]=0;
    
    fp = fopen(filename, "r");
    if( fp == NULL){
    	printf("El archivo no existe o no se pudo leer!\n");
    	return 1;
    }
    while (fgets(texto, 100, fp) != NULL) {
        printf("%s", texto);
    }
    fclose(fp);
    return 0;
}
