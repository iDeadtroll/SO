#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

int crearArchivo(){
    FILE *fp;
    char archivo[100];
    printf("Ingrese el nombre del archivo: ");
    scanf("%s",archivo);
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

void archivoExiste(){
    FILE *file;
    if (file = fopen("archivo.txt", "r")) {
        fclose(file);
        printf("el archivo ya existe\n");
    } else {
    	crearArchivo();
        printf("el archivo no exite\n");
    }
}

void compararArchivos(){
    FILE *fp1, *fp2;
    int ch1, ch2;
    char fname1[40], fname2[40];

    printf("Ingrese el nombre del primer archivo :");
    scanf("%s",fname1);

    printf("Ingrese el nombre del segundo archivo:");
    scanf("%s",fname2);

    fp1 = fopen(fname1, "r");
    fp2 = fopen(fname2, "r");

    if (fp1 == NULL) {
        printf("No se puede abrir %s para leer\n", fname1);
        exit(1);
    } else if (fp2 == NULL) {
        printf("No se puede abrir %s para leer\n", fname2);
        exit(1);
    } else {
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

int main(int argc, char *argv[]) {
    int opt;
    char archivo[100];
    char origen[100], destino[100];
    printf("1. Crear un archivo en blanco\n");
    printf("2. Comparar el contenido de dos archivos\n");
    printf("3. Mostrar las proiedades de un archivo\n");
    printf("4. Copiar archivo\n");
    printf("Seleccione opcion:");
    scanf("%d",&opt);
    
    switch (opt){
        case 1:
            crearArchivo();
        break;
        case 2:
            compararArchivos();
        break;
        case 3:
            printf("Introduce el nombre del archivo: ");
            scanf("%s", archivo);
            mostrarPropiedades(archivo);
            break;
        break;
        case 4:
        //Se podria comprobar si el archivo existe
            printf("Introduce el archivo origen: ");
            scanf("%s", origen);
            //archivoExiste();
            printf("Introduce el archivo destino: ");
            scanf("%s", destino);
            //archivoExiste();
            copiarArchivo(origen, destino);
            break;
        default:
            printf("Opcion no valida\n");
            break;
    }
    return 0;
}
