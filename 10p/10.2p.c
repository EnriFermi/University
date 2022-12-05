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
#include <signal.h>
#define varSize 4
#define MAXLEN 100
int p0;
int p1;
int volatile end;
void handler(int){

}
void handler_e(int){
    end++;
}
int main(int argc, char **argv)
{
    int file = open(argv[1], O_RDONLY, 0666);
    signal(SIGALRM, handler_e);
    signal(SIGUSR1, handler);
    p0=getpid();
    end = 0;
    char *str = malloc(MAXLEN);
    alarm(1);
    p1 = fork();
    if(p1 == -1) return -1;
    if(p1){
        pause();
    } else {
        kill(0, SIGUSR1);
    }
    while(1){
        if (p1){
            int i = 0, flag = 0;
            char c;
            while (read(file, &c, 1)) {
                flag = 1;
                if (c == '\n') {
                    break;
                }
                str[i] = c;
                i++;
            }
            str[i] = '\0';
            if(flag != 0){
                printf("Father %s\n", str);
            } else {
                end = 1;
            }
            kill(p1, SIGUSR1);
            pause();
            if(end){
                kill(p1, SIGTERM);
                break;
            }
            
        } else {
            pause();
            int i = 0, flag = 0;
            char c;
            while (read(file, &c, 1)) {
                flag = 1;
                if (c == '\n') {
                    break;
                }
                str[i] = c;
                i++;
            }
            str[i] = '\0';
            if(flag != 0){
                printf("Son %s\n", str);
            } else {
                end = 1;
            }
            kill(0, SIGUSR1);
        }
    }
}