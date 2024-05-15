// Crear un FIFO con nombre y escribir en él
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int fd;
    char * myfifo = "myfifo.txt";

    mkfifo(myfifo, 0666);

    char arr1[80];
    while (1) {
        fd = open(myfifo, O_WRONLY);
        fgets(arr1, 80, stdin);
        write(fd, arr1, strlen(arr1)+1);
        close(fd);
    }
    return 0;
}