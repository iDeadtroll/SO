#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

// Las tiberias van en una sola direccion
// '0' para leer y '1' para escribir
// Las funciones read y write son bloqueantes(es decir incorporan semaforos)
// Si queremos comunicar dos procesos en un mismo archivo usamos tuberias para comunicar dos procesos
// En caso de que queramos comunicar dos procesos en dos archivos diferentes usamos FIFO

#define FIFO_NAME "practica9"

void main (void){

    char s[300];
    int num, fd;

    
    /* don't forget to error check this stuff!! */
    mknod(FIFO_NAME, S_IFIFO | 0666, 0);
    
    printf("waiting for writers...\n");
    
    fd = open(FIFO_NAME, O_RDONLY);
    
    printf("got a writer:\n");
    
    do {
      
        if ((num = read(fd, s, 300)) == -1)
            perror("read errorrr");

        else {
            int i;
            // Convertir la cadena a minúsculas
             printf("readbytes: \"%d\"\n", strlen(s));
            for (i = 0; i < strlen(s); i++){
                s[i] = tolower(s[i]);
            }
                
            s[num-1] = '\0';
            printf("tick111: read %d bytes: \"%s\"\n", num, s);
        
        }

    } while (num >0);

}
