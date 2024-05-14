#include <stdio.h>

int main() {
    FILE *fp;
    char texto[100];
    printf("Introduce el texto que quieres escribir en el archivo: ");
    fgets(texto, 100, stdin);
    fp = fopen("ejemplo.txt", "w");
    fprintf(fp, "%s", texto);
    fclose(fp);
    return 0;
}
