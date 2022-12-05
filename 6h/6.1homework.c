#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define varSize 4
int main(int argc, char **argv)
{
    if(argc < 3){
        return 0;
    }
    int N;
    if((N = atoi(argv[2])) == 0){
        return 0;
    }
    int file 
    if(file = open(argv[1], O_RDONLY) == -1){
        return 0;
    }
	struct stat statistic;
    fstat(file, &statistic);
    int fsize = statistic.st_size;
    if(fsize < 1024){
        char *buffer = malloc(N);
        int bfile = open("___tmp___.txt", O_RDWR|O_CREAT|O_TRUNC|O_NONBLOCK, S_IRWXU);
        int readCount = read(file, buffer, N);
        while(readCount == N){
            write(bfile, buffer, readCount);
            write(bfile, buffer, readCount);
            readCount = read(file, buffer, N);
        }
        if(readCount > 0){
            write(bfile, buffer, readCount);
            write(bfile, buffer, readCount);
        }
        close(bfile);
        close(file);
        remove(argv[1]);
        rename("___tmp___.txt", argv[1]);
        return 0;
    }
    close(file);
    return 0;
}
