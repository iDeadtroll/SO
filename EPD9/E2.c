#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define STDOUT 1
#define SIZE 512

int main(int argc, char *argv[]) {

  int fd,r;
  char buffer[SIZE];
  
  if( (fd=open(argv[1],O_RDWR)) == -1){
    perror( "open" );
    exit(-1);
  }
  
  r = read(fd,buffer,SIZE);

  write(STDOUT,buffer,r);

  close(fd);

  return 0;

}
