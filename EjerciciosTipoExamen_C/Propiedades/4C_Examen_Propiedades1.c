#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[]){
    if (argc != 2) {
        fprintf(stderr, "Error: %s el archivo no existe\n", argv[0]);
        return 1;
    }
    struct stat sb;
    if (stat(argv[1], &sb) == -1) {
        perror("stat");
        return 1;
    }
    printf("Archivo: %s\n", argv[1]);
    printf("Tamanio: %lld bytes\n", (long long) sb.st_size);
    printf("Permisos: %o\n", sb.st_mode & 0777);
    printf("Ultimo acceso: %s", ctime(&sb.st_atime));
    printf("Ultima modificacion: %s", ctime(&sb.st_mtime));
    return 0;
}
