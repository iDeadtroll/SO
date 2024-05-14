#include <stdio.h>
#include <string.h>

int main() {
    FILE *f;
    char nombreArchivo[100];
    char palabra[100];
    char linea[100];
    int encontrado = 0;

    printf("Ingrese el nombre del archivo: ");
    scanf("%s", nombreArchivo);
    printf("Ingrese una palabra: ");
    scanf("%s", palabra);

    f = fopen(nombreArchivo, "r");
    if (f == NULL) {
        printf("Error al abrir el archivo\n");
        return -1;
    }

    while (fgets(linea, 100, f) != NULL) {
        if (strstr(linea, palabra) != NULL) {
            printf("%s", linea);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("Palabra prohibida\n");
        
    }
    else{
    	printf("Palabra aceptada");
    }

    fclose(f);

    return 0;
}
