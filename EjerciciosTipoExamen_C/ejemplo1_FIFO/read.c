// read.c Lee de un FIFO y muestra el contenido en la salida estándar.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int fd1;
    char * myfifo = "myfifo.txt";

    char str1[80];

    // Abrir el FIFO en modo de lectura
    fd1 = open(myfifo, O_RDONLY);

    while (1) {
        // Leer del FIFO
        if (read(fd1, str1, sizeof(str1)) > 0) {
            printf("%s\n", str1);
            close(fd1);
        }
    }

    

    return 0;
}