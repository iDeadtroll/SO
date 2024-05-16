// Version1: donde leemos 'un caracter' y lo escribimos en la tuberia
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <pthread.h> 
#include <ctype.h> 
#include <string.h> 
int filedes[2]; 
void read_char() // Escritor de la tuberia
{ 
  char c;  
  char s[300]; // No se usa en este caso
  int num; 
  printf("Entering routine to read character......\n Type a character: \n"); 
  c = getchar(); // Obtiene el caracter del teclado
  while (c != '0'){ 
    if ((num = write(filedes[1], &c, 1)) == -1){ 
      perror("write"); 
      exit(1); 
    } 
    else { 
      if (c != '\n'){  //if c is not a new line character
        printf("Child: wrote character: %c\n",c); 
      }
    }
    c = getchar(); // Obtiene el siguiente caracter
  } 
  write(filedes[1], &c, 1);  //write to pipe
} 
 
void check_hit() // Lector de la tuberia
{ 
  char c; 
  char s[300]; // No se usa en este caso
  int num; 
  printf("Entering routine to check hit.........\n"); 
  do { 
    if ((num = read(filedes[0], &c, 1)) == -1) 
      perror("read"); 
    else { 
      if (c != '\n')
        printf("Father: bytes %d read \"%c\"\nChild: Type a character: \n",num, c);
    }  
  } while (c != '0'); 
} 
 
int main() 
{ // No usamos hilos
  pipe(filedes); 
  int pid = fork(); // Usamos fork para crear un proceso hijo
  if (pid == -1) 
    exit(1); 
  if (pid == 0){ 
    // Hijo escribe en la tuberia
    read_char(); 
  } 
  else{ // Padre lee de la tuberia
    check_hit();
  } 
  exit(0); 
} 