// Version2: leemos 'una cadena' y la escribimos en la tuberia
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
  char c; // No se usa en este caso
  char s[300]; 
  int num; 
  printf("Entering routine to read character......\n Type a character: \n"); 
  fgets(s, sizeof(s), stdin); // Obtiene el la cadena del teclado
  while (s[0] != '0'){ 
    int len = strlen(s); // Obtiene la longitud de la cadena
    if ((num = write(filedes[1], &s, len)) == -1){ 
      perror("write"); 
      exit(1); 
    } 
    else { 
      if (s[0] != '\n'){  //if s is not a new line character
        printf("Child: wrote character: %s\n",s); 
      }
    }
    fgets(s, sizeof(s), stdin);
  } 
  write(filedes[1], &s, strlen(s));  //write to pipe
} 
 
void check_hit() // Lector de la tuberia
{ 
  char c; // No se usa en este caso
  char s[300]; 
  int num; 
  printf("Entering routine to check hit.........\n"); 
  do { 
    
    //printf("Father: waiting\n"); 
    if ((num = read(filedes[0], &s, sizeof(s))) == -1) 
      perror("read"); 
    else { 
      if (s[0] != '\n')
        printf("Father: bytes %d read \"%s\"\nChild: Type a character: \n",num, s);
    }  
  } while (s[0] != '0'); 
} 
 
int main() 
{ 
  pipe(filedes); 
  int pid = fork(); 
  if (pid == -1) 
    exit(1); 
  if (pid == 0){ 
    //hijo 
    read_char(); 
  } 
  else{ 
    check_hit();
  } 
  exit(0); 
} 