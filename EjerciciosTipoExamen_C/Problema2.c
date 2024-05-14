#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int fd1[2], fd2[2];
    pid_t pid;
    char buf;
    char *numbers[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    char traduccion[10];
    if (pipe(fd1) == -1 || pipe(fd2) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) { // proceso hijo
        close(fd1[1]);
        close(fd2[0]); 
        read(fd1[0], &buf, 1);
        int num = buf - '0';
        if (num >= 1 && num <= 9) {
            strcpy(traduccion, numbers[num-1]);
            write(fd2[1], traduccion, strlen(traduccion)+1);
        }
        close(fd1[0]);
        close(fd2[1]);
        exit(EXIT_SUCCESS);
    } else { // proceso padre
        close(fd1[0]); 
        close(fd2[1]);
        printf("Introduzca un numero del 1 al 9: ");
        scanf("%c", &buf);
        write(fd1[1], &buf, 1);
        read(fd2[0], traduccion, sizeof(traduccion));
        printf("Ingrese un numero: %c\nTraduccion: %s\n", buf, traduccion);
        close(fd1[1]);
        close(fd2[0]);
        wait(NULL);
        exit(EXIT_SUCCESS);
    }
}
