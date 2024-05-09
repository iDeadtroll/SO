#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main( int argc, char *argv[] ) {

	int fd;

	// O_RDWR:
   	// Open for reading and writing. 
   	// The result is undefined if this flag is applied to a FIFO.
   
    if( (fd = open(argv[1], O_RDWR)) == -1 ){
    	perror("open");
		exit(-1);
   	}
   	
   	printf("El archivo abierto tiene el descriptor %d.\n", fd );
   	
   	close(fd);
    
    return 0;

}
