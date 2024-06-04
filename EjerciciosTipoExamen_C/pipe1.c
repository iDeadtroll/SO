#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int fd[2];
    pid_t pid;

    // Crear la tubería
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Crear el proceso hijo
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Proceso hijo
        // Redirigir la salida estándar al extremo de escritura de la tubería
        dup2(fd[1], STDOUT_FILENO);
        // Cerrar el extremo de lectura de la tubería
        close(fd[0]);
        // Ejecutar el comando "ls"
        execlp("ls", "ls", NULL);
        // Si execlp retorna, hubo un error
        perror("execlp");
        exit(EXIT_FAILURE);
    } else { // Proceso padre
        // Redirigir la entrada estándar desde el extremo de lectura de la tubería
        dup2(fd[0], STDIN_FILENO);
        // Cerrar el extremo de escritura de la tubería
        close(fd[1]);
        // Ejecutar el comando "grep .c"
        execlp("grep", "grep", ".c", NULL);
        // Si execlp retorna, hubo un error
        perror("execlp");
        exit(EXIT_FAILURE);
    }
}