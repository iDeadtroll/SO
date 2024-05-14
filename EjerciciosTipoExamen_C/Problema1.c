#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void crearArchivo(){
    FILE *fp;
    fp = fopen("archivo.txt", "r");
    if(fp == NULL){
    	fp = fopen("archivo.txt", "w")
    }else{
    	prinf("El archivo ya existe");
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

void mostrarPropiedades(int argc, char *argv[]) {
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

void copiarArchivo(int argc, char *argv[]) {
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

int main() {


	int opt;
	printf("Seleccione opcion:");
	scanf("%d",&opt);
	printf("1. Crear un archivo en blanco");
	printf("2. Comparar el contenido de dos archivos");
	printf("3. Mostrar las proiedades de un archivo");
	printf("4. Copiar archivo");
	
	switch (opt){
		case 1:
			crearArchivo();
			printf("Archivo creado\n");
		break;
		case 2:
			compararArchivos();
		break;
		case 3:
			mostrarPropiedades(argc, argv);
		break;
		case 4:
			copiarArchivo(argc, argv);
		break;
			
	}
	return 0;
}
