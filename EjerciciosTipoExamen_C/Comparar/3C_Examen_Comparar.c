#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE *fp1, *fp2;
    int ch1, ch2;
    char fname1[40], fname2[40];

    printf("Ingrese el nombre del primer archivo :");
    fgets(fname1,40,stdin);
    fname1[strcspn(fname1, "\n")]=0;
    printf("Ingrese el nombre del segundo archivo:");
    fgets(fname2,40,stdin);
    fname2[strcspn(fname2, "\n")]=0;

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
