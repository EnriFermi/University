#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h>
#include <fcntl.h>
int main(int argc, char **argv)
{
    if(argc < 3){
        return 0;
    }
    int fd[2];
    pipe(fd);
    int p1 = fork();
    if(p1 == -1) return -1;
    if(p1 == 0){
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);
        execl(argv[1], argv[1], NULL);
        return 1;
    }

    int p2 = fork();
    if(p2 == -1) return -1;
    if(p2 == 0){
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
        execl(argv[2], argv[2], NULL);
        return 2;
    }
    close(fd[1]);
    int status, p;
    int end_p = wait(&status);
    if(end_p == p1){
        wait(0);
    } else {
        char *buf = malloc(4);
        while (read(fd[0], buf, 4) != 0)
        {
            write(1, buf, 4);
        }
        wait(0);
    }
    close(fd[0]);
}