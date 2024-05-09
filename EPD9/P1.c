#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>

char * permOfFile(mode_t);

int main(int argc,char *argv[]) {

    int fd, size;
    struct stat info;

    if((fd=open(argv[1],O_RDWR))==-1){
        perror("open");
        exit(-1);
    }

    stat(argv[1],&info); 
    size = info.st_size;
    
    printf("numero nodo-i %d, size %d \n",(int)(info.st_ino), size);
    printf("Modification time is %s \n", ctime(&info.st_mtime));
    printf("Permission Bits:     %04o \n", info.st_mode & 07777);
    printf("Inode Number:       %u\n", info.st_ino);
    printf("Owner User-Id:      %d\n", info.st_uid);
    printf("Owner Group-Id:     %d\n", info.st_gid);
    printf("Link Count:         %d\n", info.st_nlink);
    
    close(fd);

    return 0;

}

char * permOfFile(mode_t mode) {

    int i;
    char *p;
    static char perms[10];

    p = perms;
    strcpy(perms, "---------");

    /*
     * The permission bits are three sets of three
     * bits: user read/write/exec, group read/write/exec,
     * other read/write/exec.  We deal with each set
     * of three bits in one pass through the loop.
     */
    for (i=0; i < 3; i++) {
        if (mode & (S_IREAD >> i*3))
            *p = 'r';
        p++;

        if (mode & (S_IWRITE >> i*3))
            *p = 'w';
        p++;

        if (mode & (S_IEXEC >> i*3))
            *p = 'x';
        p++;
    }

    /*
     * Put special codes in for set-user-id, set-group-id,
     * and the sticky bit.  (This part is incomplete; "ls"
     * uses some other letters as well for cases such as
     * set-user-id bit without execute bit, and so forth.)
     */
    if ((mode & S_ISUID) != 0)
        perms[2] = 's';

    if ((mode & S_ISGID) != 0)
        perms[5] = 's';

    if ((mode & S_ISVTX) != 0)
        perms[8] = 't';

    return(perms);
}
