#include <stdio.h>
#include <string.h>

int main(){
    FILE *fp;
    char fname[100];
    printf("Introduzca el nombre del archivo: ");
    fgets(fname,100,stdin);
    fname[strcspn(fname, "\n")]=0;
    
    fp = fopen(fname, "r");
    if(fp == NULL){
    	fp = fopen(fname, "w");
    }else{
    	printf("El archivo ya existe\n");
    	return 1;
    }
    fclose(fp);
    return 0;
}
