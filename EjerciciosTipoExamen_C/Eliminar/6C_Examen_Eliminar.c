#include <stdio.h>
#include <string.h>

int main() {
    char nombre_archivo[100];
    printf("Introduce el nombre del archivo que quieres eliminar: ");
    fgets(nombre_archivo, 100, stdin);
    nombre_archivo[strcspn(nombre_archivo, "\n")] = 0;
    if (remove(nombre_archivo) == 0) {
        printf("Archivo eliminado con éxito\n");
    } else {
        perror("Error al eliminar el archivo");
    }
    return 0;
}
