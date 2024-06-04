#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <dirent.h>
#include <string.h>

int crearArchivo(char *archivo){
    FILE *fp;
    fp = fopen(archivo, "r");
    if(fp == NULL){
        fp = fopen(archivo, "w");
        printf("Archivo creado\n");
    }else{
        printf("El archivo ya existe\n");
        return 1;
    }
    fclose(fp);
    return 0;
}

int archivoExiste(char *archivo){
    FILE *file;
    if ((file = fopen(archivo, "r"))) {
        fclose(file);
        return (1);
    } else {
        return 0;
    }
}

void compararArchivos(char *archivo1, char *archivo2){
    FILE *fp1, *fp2;
    int ch1, ch2;

    fp1 = fopen(archivo1, "r");
    fp2 = fopen(archivo2, "r");

    ch1 = getc(fp1);
    ch2 = getc(fp2);

    while ((ch1 != EOF) && (ch2 != EOF) && (ch1 == ch2)) {
        ch1 = getc(fp1);
        ch2 = getc(fp2);
    }

    if (ch1 == ch2)
        printf("Los archivos son iguales\n");
    else if (ch1 != ch2)
        printf("Los archivos son diferentes\n");

    fclose(fp1);
    fclose(fp2);
}

void mostrarPropiedades(char *archivo) {
    struct stat sb;
    if (stat(archivo, &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }
    printf("Archivo: %s\n", archivo);
    printf("Tamanio: %lld bytes\n", (long long) sb.st_size);
    printf("Permisos: %o\n", sb.st_mode & 0777);
    printf("Ultimo acceso: %s", ctime(&sb.st_atime));
    printf("Ultima modificacion: %s", ctime(&sb.st_mtime));
}

void copiarArchivo(char *origen, char *destino) {
    FILE *source = fopen(origen, "rb");
    if (source == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    FILE *destination = fopen(destino, "wb");
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
}


void eliminarArchivo(char *archivo) {
    if (remove(archivo) != 0)
        perror("remove");
}

void cambiarNombreArchivo(char *antiguoNombre, char *nuevoNombre) {
    if (rename(antiguoNombre, nuevoNombre) == 0)
        printf("El archivo ha sido renombrado\n");
    else
        perror("rename");
}

int directorioExiste(const char *path) {
   struct stat info;

   if(stat(path, &info) != 0)
       return 0;
   else if(info.st_mode & S_IFDIR)
       return 1;
   else
       return 0;
}

void moverArchivo(char *origen, char *destino) {
    char directorioDestino[256];
    strncpy(directorioDestino, destino, strrchr(destino, '/') - (destino));
    directorioDestino[strrchr(destino, '/') - (destino)] = '\0';

    if (directorioExiste(directorioDestino)) {
        copiarArchivo(origen, destino);
        eliminarArchivo(origen);
    } else {
        printf("El directorio de destino no existe\n");
    }
}

void listarDirectorioActual() {
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    }
}

void obtenerNombresArchivos(char *origen, char *destino, char *mensaje1, char *mensaje2) {
    printf("%s", mensaje1);
    scanf("%s", origen);
    // if (!archivoExiste(origen)) {
    //     printf("El archivo %s no existe\n", origen);
    //     exit(1);
    // }
    printf("%s", mensaje2);
    scanf("%s", destino);
    // if (archivoExiste(destino)) {
    //     printf("El archivo %s ya existe\n", destino);
    //     exit(1);
    // }
}

int main() {
    int opt;
    char archivo[100];
    char origen[100], destino[100];
    printf("1. Crear un archivo en blanco\n");
    printf("2. Comparar el contenido de dos archivos\n");
    printf("3. Mostrar las propiedades de un archivo\n");
    printf("4. Copiar archivo\n");
    printf("5. Eliminar archivo\n");
    printf("6. Cambiar nombre de archivo\n");
    printf("7. Mover archivo\n");
    printf("8. Listar directorio actual\n");
    printf("Seleccione opcion: ");
    scanf("%d",&opt);
    
    switch (opt){
        case 1:
            printf("Introduce el nombre del archivo: ");
            scanf("%s", archivo);
            if (archivoExiste(archivo)) {
                printf("El archivo ya existe\n");
                break;
            }
            crearArchivo(archivo);
        break;
        case 2:
            obtenerNombresArchivos(origen, destino, "Introduce el nombre del primer archivo: ", "Introduce el nombre del segundo archivo: ");
            compararArchivos(origen, destino);
        break;
        case 3:
            printf("Introduce el nombre del archivo: ");
            scanf("%s", archivo);
            mostrarPropiedades(archivo);
        break;
        case 4:
            obtenerNombresArchivos(origen, destino, "Introduce el archivo origen: ", "Introduce el archivo destino: ");
            copiarArchivo(origen, destino);
            break;
        case 5:
            printf("Introduce el nombre del archivo: ");
            scanf("%s", archivo);
            eliminarArchivo(archivo);
            break;
        case 6:
            obtenerNombresArchivos(origen, destino, "Introduce el nombre del archivo: ", "Introduce el nuevo nombre: ");
            cambiarNombreArchivo(origen, destino);
            break;
        case 7: 
            obtenerNombresArchivos(origen, destino, "Introduce el archivo origen: ", "Introduce el archivo destino: ");
            moverArchivo(origen, destino);
            break;
        case 8: 
            listarDirectorioActual();
            break;
        default:
            printf("Opcion no valida\n");
            break;
    }
    return 0;
}
