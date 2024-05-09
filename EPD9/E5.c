#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

static void lookup(const char *arg) {

    DIR *dirp;
    struct dirent *dp;
    int errno;

    if ((dirp = opendir(".")) == NULL) {
        perror("couldn't open '.'");
        return;
    }

    do {

        errno = 0;
        
        if ((dp=readdir(dirp))!=NULL) {

            if (strcmp(dp->d_name, arg) == 0){

                printf("found %s\n", arg);
                closedir(dirp);
                return;
            }
        }

    } while(dp!=NULL);

    if (errno!=0)
        perror("error reading directory");
    else
        printf("failed to find %s\n", arg);
    
    closedir(dirp);
    
    return;
}

int main(int argc, char *argv[]) {

    int i;
    
    for (i=1;i<argc;i++)
        lookup(argv[i]);
    
    return 0;

}
