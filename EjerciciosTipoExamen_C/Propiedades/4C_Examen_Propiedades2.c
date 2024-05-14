#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

int main(){
	char archivoP[100];
	printf("Introduce el nombre del archivo: ");
    fgets(archivoP, 100, stdin);
    archivoP[strcspn(archivoP, "\n")] = 0;

    struct stat sb;
    if (stat(archivoP, &sb) == -1) {
        perror("stat");
        return 1;
    }
    printf("Archivo: %s\n", archivoP);
    printf("Tamanio: %lld bytes\n", (long long) sb.st_size);
    printf("Permisos: %o\n", sb.st_mode & 0777);
    printf("Ultimo acceso: %s", ctime(&sb.st_atime));
    printf("Ultima modificacion: %s", ctime(&sb.st_mtime));
    return 0;
}
